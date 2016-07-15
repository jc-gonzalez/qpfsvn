/******************************************************************************
 * File:    logwatcher.h
 *          This file is part of QLA Processing Framework
 *
 * Domain:  QPF.libQPF.logwatcher
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
 *   Declare LogWatcher class
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

#ifndef LOGWATCHER_H
#define LOGWATCHER_H

#include <QFileSystemWatcher>

#include "textview.h"

namespace QPF {

class LogWatcher : public QObject
{
  Q_OBJECT

public:
  LogWatcher(TextView * txtVw, int lines = 100);

  void setFile(QString s);
  QString getFile();
  
private slots:
  void updateLogView(const QString & path);

signals:
  void logUpdated();

private:
  TextView * textView;
  QFileSystemWatcher * fsWatcher;
  QString watchedFile;
  qint64 bytesRead;
  qint64 maxNumLines;
};

}

#endif