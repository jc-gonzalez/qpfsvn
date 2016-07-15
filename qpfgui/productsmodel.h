/******************************************************************************
 * File:    productsmodel.h
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.libQPF.productsmodel
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
 *   Declaration of several dataproductsmodel for QPF HMI
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
#ifndef PRODUCTSMODEL_H
#define PRODUCTSMODEL_H

#include "dbtreemodel.h"

namespace QPF {

class ProductsModel : public DBTreeModel {

    Q_OBJECT

public:
    explicit ProductsModel();
};

}

#endif // PRODUCTSMODEL_H