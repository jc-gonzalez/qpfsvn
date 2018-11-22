/******************************************************************************
 * File:    dckwatchdog.cpp
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.QPF.DckWatchDog
 *
 * Version:  2.0
 *
 * Date:    2015/07/01
 *
 * Author:   J C Gonzalez
 *
 * Copyright (C) 2015-2018 Euclid SOC Team @ ESAC
 *_____________________________________________________________________________
 *
 * Topic: General Information
 *
 * Purpose:
 *   Implement DckWatchDog class
 *
 * Created by:
 *   J C Gonzalez
 *
 * Status:
 *   Prototype
 *
 * Dependencies:
 *   none
 *
 * Files read / modified:
 *   none
 *
 * History:
 *   See <Changelog>
 *
 * About: License Conditions
 *   See <License>
 *
 ******************************************************************************/

#include "dckwatchdog.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>  
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>
#include <vector>

#define TRACE_MSGS
#ifdef TRACE_MSGS
#    define TRC(s) std::cerr << "[[WD]] " << s << '\n';
#else
#    define TRC(s) 
#endif

#include "dckwatchdog_cmds.h"

#define T(a,b) DWD_CMD_ ## a ( #b )
std::string T_LIST_OF_WATCHDOG_COMMANDS;
#undef T

#define T(a,b) #b
std::string DckWatchDogCmdName[] = { T_LIST_OF_WATCHDOG_COMMANDS };
#undef T

const int DckWatchDogExitCode(32);

bool startsWith(std::string & s, std::string & ss) {
    return ((ss.size() <= s.size()) &&
            (strncmp(ss.c_str(), s.c_str(), ss.length()) == 0));
}

void DckWatchDog::notArmedAction() 
{
    // do whatever the watchdog must do if the parent failed to arm it
    TRC("GUAU!");

    // Create Container manager
    DockerMng * dckMng = new ContainerMng;
    getAdditionalContainers(dckMng);

    std::vector<std::string> args { "--force" };

    {
        std::lock_guard<std::mutex> lock(setOfIDsMutex);

        for (auto id : setOfIDs) {
            TRC("Cleaning up id " << id);
            dckMng->runCmd("rm", args, id);
        }
        
        setOfIDs.clear();
    }

    cleanUpAndExit();
}

void DckWatchDog::run() 
{
    // This watchdog receives a set of commands via pipe
    // The commands accepted are:
    // add <id> : add the docker container <id> to the list of running containers
    // rm <id>  : remove the docker container <id> form the list of running containers
    // clear : clears the list of docker containers
    // asm : Re-arms the watchdog
    // quit : Quit the watchdog

    std::vector<std::string> msgList;
    char message[256];
    size_t pos;

    TRC("WATCHDOG IS RUNNING");
    {
        std::lock_guard<std::mutex> lock(armedMutex);
        armed = true;
    }

    while (true) { // forever 
        memset(message, 0, sizeof(message));
        int len = read(readPipeEnd, message, sizeof(message));
        if (len < 1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;       
        }
        std::string msg(message);
        TRC("Received: '" << msg << "'");
        // Split into single messages
        msgList.clear();
        while ((pos = msg.find(";")) != std::string::npos) {
            msgList.push_back(msg.substr(0, pos));
            msg.erase(0, pos + 1);
        }

        // Parse and execute messages
        for (auto & m : msgList) {
            TRC("  Processing '" << m << "'");
            if (m == DWD_CMD_QUIT) {
                // Quit watchdog
                TRC("Quitting watchdog . . .");
                return;
            } else if (m == DWD_CMD_CLEAR) {
                // Re-arm watchdog
                TRC("Clearing list . . .");
                std::lock_guard<std::mutex> lock(setOfIDsMutex);
                setOfIDs.clear();
            } else if (m == DWD_CMD_DUMP) {
                // Re-arm watchdog
                TRC("List of IDs:");
                std::lock_guard<std::mutex> lock(setOfIDsMutex);
                for (auto & id : setOfIDs) {
                    TRC("    - " << id);
                }
            } else if (m == DWD_CMD_ARM) {
                // Re-arm watchdog
                arm();
                TRC("Re-arming watchdog");
            } else {
                pos = m.find(" ");
                std::string token = m.substr(0, pos);
                m.erase(0, pos + 1);
                if (token == DWD_CMD_ADD) {
                    // Add <id> to list
                    std::lock_guard<std::mutex> lock(setOfIDsMutex);
                    setOfIDs.insert(m);
                } else if (token == DWD_CMD_REMOVE) {
                    // Remove <id> form list
                    std::lock_guard<std::mutex> lock(setOfIDsMutex);
                    setOfIDs.erase(m);
                } else {
                    TRC("Unknown message: '" << message << "'");
                }
            }
        }
    } // forever (until exited)
}   

void DckWatchDog::getAdditionalContainers(DockerMng * dckMng)
{
    static const char Separator[] = "|";
    static const std::string StatusExited("exited");
    static const std::string StatusCreated("created");
    static const long SuccessExitCode(0);

    // Get list of containers
    std::vector<std::string> contList;
    dckMng->getContainerList(contList);

    std::string qpfRun("/qpf/run/");

    // Iterate for each container, get working dir, then status, then exit code
    for (auto & id : contList) {
        std::string info("{{.Config.WorkingDir}}|"
                         "{{.State.Status}}|"
                         "{{.State.ExitCode}}");
        if (!dckMng->getInfo(id, info)) {
            std::cerr << "[[WD]] ERROR getting info from container " << id << '\n';
        }

        TRC("    For " << id << ": " << info);
        
        std::string start(info.substr(1, qpfRun.length()));
        if (start != qpfRun) { continue; }

        // Its a QPF container, get the next data elements
        size_t pos = info.find(Separator);
        std::string workDir = info.substr(0, pos);
        info.erase(0, pos + 1);
        pos = info.find(Separator);
        std::string status = info.substr(0, pos);
        TRC("       status = " << status);

        if ((status == StatusExited) || (status == StatusCreated)) {
            info.erase(0, pos + 1);
            long code = std::strtol(info.c_str(), nullptr, 10);
            TRC("       code = " << code);
            if (code == SuccessExitCode) { 
                // Correctly finished QPF task, still in cont.list => remove it
                std::lock_guard<std::mutex> lock(setOfIDsMutex);
                setOfIDs.insert(id);
            }
        }
    }
}
    
void DckWatchDog::cleanUpAndExit()
{
    exit(DckWatchDogExitCode);
}
