/******************************************************************************
 * File:    dckwatchdog_cmds.h
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.QPF.DckWatchDog
 *
 * Last update:  2.0
 *
 * Date:    2015/11/20
 *
 * Author:   J C Gonzalez
 *
 * Copyright (C) 2015-2018 Euclid SOC Team @ ESAC
 *_____________________________________________________________________________
 *
 * Topic: General Information
 *
 * Purpose:
 *   Declare DckWatchDog commands
 *
 * Created by:
 *   J C Gonzalez
 *
 * Status:
 *   Prototype
 *
 * Dependencies:
 *   CommNode
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

#ifndef DCKWATCHDOG_CMDS_H
#define DCKWATCHDOG_CMDS_H

//============================================================
// Group: External Dependencies
//============================================================

//------------------------------------------------------------
// Topic: System headers
//   none
//------------------------------------------------------------

//------------------------------------------------------------
// Topic: External packages
//   none
//------------------------------------------------------------

//------------------------------------------------------------
// Topic: Project headers
//   none
//------------------------------------------------------------

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
//namespace QPF {

#ifdef T
#    undef T
#endif

#define T_LIST_OF_WATCHDOG_COMMANDS \
    T(ADD, add), \
    T(REMOVE, rm), \
    T(ARM, arm), \
    T(DUMP, dump), \
    T(CLEAR, clear), \
    T(QUIT, quit) 

#define T(a,b) a
enum DckWatchDogCmd { T_LIST_OF_WATCHDOG_COMMANDS };
#undef T

#define T(a,b) DWD_CMD_ ## a
extern std::string T_LIST_OF_WATCHDOG_COMMANDS;
#undef T

extern std::string DckWatchDogCmdName[];

extern const int DckWatchDogExitCode;

//}

#endif  /* DCKWATCHDOG_CMDS_H */
