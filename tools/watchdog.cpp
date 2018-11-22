/******************************************************************************
 * File:    watchdog.cpp
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.QPF.WatchDog
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
 *   Implement WatchDog class
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

#include "watchdog.h"

#include "timer.h"

//----------------------------------------------------------------------
// Method: start
//----------------------------------------------------------------------
void WatchDog::start() 
{ 
    Timer * timer = new Timer(msWdArmPeriod, true, &WatchDog::trigger, this);
    run();
}

//----------------------------------------------------------------------
// Method: arm
// (Re)Arms the watchdog
//----------------------------------------------------------------------
void WatchDog::arm() 
{ 
    std::lock_guard<std::mutex> lock(armedMutex);
    armed = true;
}

//----------------------------------------------------------------------
// Method: isArmed
// Accessor to see if the watchdog is armed
//----------------------------------------------------------------------
bool WatchDog::isArmed() 
{ 
    return armed; 
}

//----------------------------------------------------------------------
// Method: trigger
// Trigger the watchdog - checks if armed or not
//----------------------------------------------------------------------
void WatchDog::trigger() 
{
    bool armedFlag;
    {
	std::lock_guard<std::mutex> lock(armedMutex);
	armedFlag = armed;
    }

    if (! armedFlag) {
        notArmedAction();
    } else {
	std::lock_guard<std::mutex> lock(armedMutex);
        armed = false;
        Timer * timer = new Timer(msWdArmPeriod, true, &WatchDog::trigger, this);
    }
}
