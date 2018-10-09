/******************************************************************************
 * File:    launcher.cpp
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.Launcher
 *
 * Version:  1.0
 *
 * Date:    2017/12/01
 *
 * Author:   J C Gonzalez
 *
 * Copyright (C) 2015-2018 Euclid SOC Team @ ESAC
 *_____________________________________________________________________________
 *
 * Topic: General Information
 *
 * Purpose:
 *   Provides object implementation for class Launcher
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

#include "launcher.h"

#include "process.h"
#include <iostream>

//----------------------------------------------------------------------
// Method: create
// Defines a new app launcher
//----------------------------------------------------------------------
void Launcher::create(std::string prg, std::vector<std::string> arg)
{
    app = prg;
    args = arg;
    isDefined = true;
}

//------------------------------------------------------------
// Method: exec
// Executes the defined launcher
//------------------------------------------------------------
bool Launcher::exec()
{
    if (! isDefined) { return false; }
    
    procxx::process * appCmd = new procxx::process(app);
    for (auto & a : args) { appCmd->add_argument(a); }
    
    appCmd->exec();
}

//------------------------------------------------------------
// Constructor
// Generate a temporary file with unique file name in /tmp
//------------------------------------------------------------
IPythonLauncher::IPythonLauncher(std::string ipyApp, std::string ipyPath)
{
    std::vector<std::string> vargs {ipyApp, "-i", "-c", "'%cd " + ipyPath + "'"};
    char * termApp = getenv("COLORTERM");
    if (termApp == nullptr) { termApp = getenv("TERM"); }
    if (strncmp(termApp, "xterm", 5) == 0) {
        vargs.insert(vargs.begin(), "-e");
    } else {
        vargs.insert(vargs.begin(), "--");
    }
    if (termApp != nullptr) {
        try {
            std::cerr << "Launching " << ipyApp.c_str() << " with " << termApp << " . . .\n";
            create(termApp, vargs);
        } catch(...) {
            std::cerr << "Terminal application " << termApp << " not found.\n"
                      << "Please, set COLORTERM or TERM env. variables to an existing "
                      << "terminal application.\n";
        }
    }
}

//------------------------------------------------------------
// Constructor
// Generate a temporary file with unique file name in /tmp
//------------------------------------------------------------
JupyterLauncher::JupyterLauncher(std::string jpyApp, std::string jptAddr)
{
}
