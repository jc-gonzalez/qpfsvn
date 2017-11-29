/******************************************************************************
 * File:    voshdl.h
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.libQPF.voshdl
 *
 * Version:  1.2
 *
 * Date:    2015/07/01
 *
 * Author:   J C Gonzalez
 *
 * Copyright (C) 2015-2017 Euclid SOC Team @ ESAC
 *_____________________________________________________________________________
 *
 * Topic: General Information
 *
 * Purpose:
 *   Declaration of several datavoshdl for QPF HMI
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
#ifndef VOSPACEHANDLER_H
#define VOSPACEHANDLER_H

#include <QObject>

namespace QPF {

class VOSpaceHandler : public QObject {

    Q_OBJECT

public:
    explicit VOSpaceHandler(QObject *parent = 0);
    ~VOSpaceHandler();

signals:
    void activate();


private:
    int a;
};

}

#endif // VOSPACEHANDLER_H
