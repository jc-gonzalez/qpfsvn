/******************************************************************************
 * File:    watchdog.h
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.QPF.WatchDog
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
 *   Declare WatchDog class
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

#ifndef WATCHDOG_H
#define WATCHDOG_H

//============================================================
// Group: External Dependencies
//============================================================

//------------------------------------------------------------
// Topic: System headers
//   - chrono
//   - thread
//   - mutex
//------------------------------------------------------------
#include <chrono>
#include <thread>
#include <mutex>

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

//==========================================================================
// Class: WatchDog
//==========================================================================
class WatchDog {

public:
    //----------------------------------------------------------------------
    // Constructor: WatchDog
    //----------------------------------------------------------------------
    WatchDog(int per = 1000, int rdPipe = 0) 
        : msWdArmPeriod(per), readPipeEnd(rdPipe), armed(true) {}

    //----------------------------------------------------------------------
    // Method: start
    //----------------------------------------------------------------------
    void start();

    //----------------------------------------------------------------------
    // Method: arm
    // (Re)Arms the watchdog
    //----------------------------------------------------------------------
    void arm();

    //----------------------------------------------------------------------
    // Method: isArmed
    // Accessor to see if the watchdog is armed
    //----------------------------------------------------------------------
    bool isArmed();

protected:
    //----------------------------------------------------------------------
    // Method: trigger
    // Trigger the watchdog - checks if armed or not
    //----------------------------------------------------------------------
    void trigger();

    //----------------------------------------------------------------------
    // Method: notArmedAction
    // Actions executed when the watchdog timer expires and is not armed
    //----------------------------------------------------------------------
    virtual void notArmedAction()=0;

    //----------------------------------------------------------------------
    // Method: run
    // Launches the watchdog loop
    //----------------------------------------------------------------------
    virtual void run()=0;   

protected:
    int msWdArmPeriod;
    int readPipeEnd;

    bool armed;
    std::mutex armedMutex;
};

//}

#endif  /* WATCHDOG_H */
