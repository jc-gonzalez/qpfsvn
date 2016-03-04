/******************************************************************************
 * File:    dbhdlpostgre.h
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.libQPF.DBHdlPostgreSQL
 *
 * Version: 1.0
 *
 * Date:    2015/07/01
 *
 * Copyright (C) 2015 J C Gonzalez
 *_____________________________________________________________________________
 *
 * Topic: General Information
 *
 * Purpose:
 *   Declare MessageHandler class
 *
 * Created by:
 *   J C Gonzalez
 *
 * Status:
 *   Prototype
 *
 * Dependencies:
 *   DBHandler
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

#ifndef DBHDLPOSTGRE_H
#define DBHDLPOSTGRE_H

//============================================================
// Group: External Dependencies
//============================================================

//------------------------------------------------------------
// Topic: System headers
//   none
//------------------------------------------------------------

//------------------------------------------------------------
// Topic: External packages
//   - libpq-fe.h
//------------------------------------------------------------
#include <libpq-fe.h>

//------------------------------------------------------------
// Topic: Project headers
//   - dbhdl.h
//------------------------------------------------------------
#include "dbhdl.h"

////////////////////////////////////////////////////////////////////////////
// Namespace: QPF
// -----------------------
//
// Library namespace
////////////////////////////////////////////////////////////////////////////
namespace QPF {
  
//==========================================================================
// Class: DBHdlPostgreSQL
//==========================================================================
class DBHdlPostgreSQL : public DBHandler {

public:

    //----------------------------------------------------------------------
    // Constructor: DBHdlPostgreSQL
    //----------------------------------------------------------------------
    DBHdlPostgreSQL();

    //----------------------------------------------------------------------
    // Destructor: ~DBHdlPostgreSQL (virtual)
    //----------------------------------------------------------------------
    ~DBHdlPostgreSQL() {}

    //----------------------------------------------------------------------
    // Method: openConnection
    // Open a connection to the database
    //----------------------------------------------------------------------
    virtual bool openConnection(const char * data = 0);

    //----------------------------------------------------------------------
    // Method: closeConnection
    // Closes the connection to the database
    //----------------------------------------------------------------------
    virtual bool closeConnection(const char * data = 0);

    //----------------------------------------------------------------------
    // Method: storeProducts
    // Saves a set of products' metadata to the database
    //----------------------------------------------------------------------
    virtual int storeProducts(ProductCollection & prodList);

    //----------------------------------------------------------------------
    // Method: retrieveProducts
    // Retrieves a set of products from the database, according to
    // pre-defined criteria
    //----------------------------------------------------------------------
    virtual int retrieveProducts(ProductList & prodList,
                                 std::string criteria = std::string());

    //----------------------------------------------------------------------
    // Method: storeTask
    // Stores a task information to the database
    //----------------------------------------------------------------------
    virtual bool storeTask(TaskInfo & task);

    //----------------------------------------------------------------------
    // Method: checkTask
    // Returns true if an entry for a task exists in the DB
    //----------------------------------------------------------------------
    virtual bool checkTask(std::string taskId = std::string());

    //----------------------------------------------------------------------
    // Method: updateTask
    // Updates the information for a given task in the database
    //----------------------------------------------------------------------
    virtual bool updateTask(TaskInfo & task);

    //----------------------------------------------------------------------
    // Method: retrieveTask
    // Retrieves a task information from the database
    //----------------------------------------------------------------------
    virtual bool retrieveTask(TaskInfo & task);

    //----------------------------------------------------------------------
    // Method: storeMsg
    // Stores a message into the database
    //----------------------------------------------------------------------
    virtual bool storeMsg(std::string from,
                          Router2RouterPeer::PeerMessage & inPeerMsg,
                          bool isBroadcast);

    //----------------------------------------------------------------------
    // Method: retrieveMsgs
    // Retrieves a set of messages from the database, according to
    // pre-defined criteria
    //----------------------------------------------------------------------
    virtual bool retrieveMsgs(std::vector<std::pair<std::string,
                              Router2RouterPeer::PeerMessage> > & msgList,
                              std::string criteria = std::string());

    //----------------------------------------------------------------------
    // Method: getTable
    // Get the content (all the records) from a given table
    //----------------------------------------------------------------------
    virtual bool getTable(std::string tName,
                          std::vector< std::vector<std::string> > & table);

    //----------------------------------------------------------------------
    // Method: getQuery
    // Get the result (all the records) of a given query
    //----------------------------------------------------------------------
    virtual bool getQuery(std::string qry,
                          std::vector< std::vector<std::string> > & table);

    //----------------------------------------------------------------------
    // Method: getNumRowsInTable
    // Get the content (all the records) from a given table
    //----------------------------------------------------------------------
    virtual int getNumRowsInTable(std::string tName);

    //----------------------------------------------------------------------
    // Method: runCmd
    // Runs a SQL command
    //----------------------------------------------------------------------
    virtual bool runCmd(std::string cmd);

    //----------------------------------------------------------------------
    // Method: fillWithResult
    // Retrieves the content of the returned n-tuples (after and SQL command)
    // into the table parameter
    //----------------------------------------------------------------------
    virtual bool fillWithResult(std::vector< std::vector<std::string> > & table);

    //----------------------------------------------------------------------
    // Method: updateTable<T>
    // Template method to update a single field of a table
    //----------------------------------------------------------------------
    template<class T>
    bool updateTable(std::string table, std::string cond,
                             std::string field, T value);

private:
    //----------------------------------------------------------------------
    // Method: updTable
    // Update a single field in a given table
    //----------------------------------------------------------------------
    bool updTable(std::string table, std::string cond,
                  std::string field, std::string value);

private:
    PGconn     * conn;
    PGresult   * res;
};

}

#endif  /* DBHDLPOSTGRE_H */

