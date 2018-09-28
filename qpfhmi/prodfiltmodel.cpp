/******************************************************************************
 * File:    prodfiltmodel.cpp
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.libQPF.prodfiltmodel
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
 *   Provides object implementation for class ProductsFiltModel
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

#include "prodfiltmodel.h"
#include <iostream>
namespace QPF {

ProductsFilterModel::ProductsFilterModel(QString qry)
{
    defineHeaders({"Product Id", //"ID", "URL", "FITS_File",
                   "Type", "Start", "CCD[Q]",
                   "Diagnostic", "Info", "Values"});
    changeQuery(qry);
}

void ProductsFilterModel::changeQuery(QString qry)
{
    QString selectFields("SELECT product_id, "
                         //"id, url, fits_file, "
                         "product_type, "
                         "start_time, ccd, diag, values, value");
    qry.replace("SELECT *", selectFields);
    std::cerr << "FILTER >>>>>>>>>>> " + qry.toStdString() + "\n";
    defineQuery("refresh materialized view products_info_filter; " + qry);

    //skipColumns(4);

    refresh();
}

}
