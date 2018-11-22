/******************************************************************************
 * File:    dckwatchdog.h
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
 *   Declare DckWatchDog class
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

#ifndef DCKWATCHDOG_H
#define DCKWATCHDOG_H

//============================================================
// Group: External Dependencies
//============================================================

//------------------------------------------------------------
// Topic: System headers
//   - set
//------------------------------------------------------------
#include <set>

//------------------------------------------------------------
// Topic: External packages
//   none
//------------------------------------------------------------

//------------------------------------------------------------
// Topic: Project headers
//   - watchdog
//------------------------------------------------------------
#include "watchdog.h"
#include "cntrmng.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
//namespace QPF {

//==========================================================================
// Class: DckWatchDog
//==========================================================================
class DckWatchDog : public WatchDog {

public:
    //----------------------------------------------------------------------
    // Constructor: DckWatchDog
    //----------------------------------------------------------------------
    DckWatchDog(int per = 1000, int rdPipe = 0) 
        : WatchDog(per, rdPipe) {}

protected:
    //----------------------------------------------------------------------
    // Method: notArmedAction
    // Actions executed when the dckwatchdog timer expires and is not armed
    //----------------------------------------------------------------------
    virtual void notArmedAction();

    //----------------------------------------------------------------------
    // Method: run
    // Launches the dckwatchdog loop
    //----------------------------------------------------------------------
   virtual void run();   

private:
    //----------------------------------------------------------------------
    // Method: clean
    // Additional actions before exiting
    //----------------------------------------------------------------------
    void getAdditionalContainers(DockerMng * dckMng);   
    
    //----------------------------------------------------------------------
    // Method: cleanUpAndExit
    // Additional actions before exiting
    //----------------------------------------------------------------------
    void cleanUpAndExit();   
    
private:
    std::set<std::string> setOfIDs;
    std::mutex setOfIDsMutex;
};

//}

#endif  /* DCKWATCHDOG_H */
