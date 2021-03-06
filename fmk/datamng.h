/******************************************************************************
 * File:    datamng.h
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.libQPF.DataManager
 *
 * Last update:  2.0
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
 *   Declare DataManager class
 *
 * Created by:
 *   J C Gonzalez
 *
 * Status:
 *   Prototype
 *
 * Dependencies:
 *   Component
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

#ifndef DATAMNG_H
#define DATAMNG_H

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
//   - component.h
//------------------------------------------------------------
#include "component.h"

//==========================================================================
// Class: DataManager
//==========================================================================
class DataMng : public Component {

public:
    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
    DataMng(const char * name, const char * addr = 0, Synchronizer * s = 0);

    //----------------------------------------------------------------------
    // Constructor
    //----------------------------------------------------------------------
    DataMng(std::string name, std::string addr = std::string(), Synchronizer * s = 0);

    //----------------------------------------------------------------------
    // Method: isProductAvailable
    // Returns TRUE if there is a product type like the requested in the DB
    //----------------------------------------------------------------------
    bool isProductAvailable(std::string prodType);

    //----------------------------------------------------------------------
    // Method: getProductLatest
    // Returns TRUE if there is a product type like the requested in the DB
    //----------------------------------------------------------------------
    bool getProductLatest(std::string prodType,
                          Json::Value & prodMetadata);

public:
    //----------------------------------------------------------------------
    // Method: processInDataMsg
    //----------------------------------------------------------------------
    void txInDataToLocalArch(ProductList & inData);

    //----------------------------------------------------------------------
    // Method: storeTskRegData
    //----------------------------------------------------------------------
    void storeTskRegData(json & tskRepData);

    //----------------------------------------------------------------------
    // Method: saveTaskToDB
    // Save the information on generated output products to the archive
    //----------------------------------------------------------------------
    void saveTaskToDB(TaskInfo & taskInfo, bool initialStore = false);

    //----------------------------------------------------------------------
    // Method: updateTaskStatusSpectra
    // Refresh the table with the status of all tasks in all task agents
    // (stored in the form of a materialized view)
    //----------------------------------------------------------------------
    void updateTaskStatusSpectra();

    //----------------------------------------------------------------------
    // Method: storeTaskStatusSpectra
    // Store task agent spectra in DB
    //----------------------------------------------------------------------
    void storeTaskStatusSpectra(json & fmkInfoValue);
    
    //----------------------------------------------------------------------
    // Method: retrieveTaskStatusSpectra
    // Retrieve task agent spectra from DB
    //----------------------------------------------------------------------
    void retrieveTaskStatusSpectra(TskStatTable & tssSet);

    //----------------------------------------------------------------------
    // Method: getRestartableTaskInputs
    // Returns the list of inputs that triggered the creation of new tasks,
    // for the tasks that appear as scheduled or running in the database,
    // at the start of the Core
    //----------------------------------------------------------------------
    bool getRestartableTaskInputs(ProductList & inputFiles);

protected:

    //----------------------------------------------------------------------
    // Method: initializeDB
    // Initialize the DB
    // (currently just an INI text file)
    //----------------------------------------------------------------------
    void initializeDB();

    //----------------------------------------------------------------------
    // Method: saveToDB
    // Save the information of a new (incoming) product to the DB
    // (currently just an INI text file)
    //----------------------------------------------------------------------
    void saveToDB(MessageString & msg);

    //----------------------------------------------------------------------
    // Method: saveTaskToDB
    // Save the information on generated output products to the archive
    //----------------------------------------------------------------------
    void saveTaskToDB(MessageString & msg, bool initialStore = false);

    //----------------------------------------------------------------------
    // Method: sanitizeProductVersions
    // Make sure that there is no product with the same signature (and version)
    // in local archive, changing the version if needed
    //----------------------------------------------------------------------
    void sanitizeProductVersions(ProductList & productList);

    //----------------------------------------------------------------------
    // Method: saveProductsToDB
    // Save the information of a new (incoming) product to the DB
    // (currently just an INI text file)
    //----------------------------------------------------------------------
    void saveProductsToDB(ProductList & productList); //Json::Value & prodMetadata);

    //----------------------------------------------------------------------
    // Method: archiveDSSnEAS
    // Sends the information to the area where the corresponding daemon is
    // looking for data to be sent to DSS/EAS
    //----------------------------------------------------------------------
    void archiveDSSnEAS(ProductList & productList);

private:
    std::string dbFileName;
};

#endif  /* DATAMNG_H */
