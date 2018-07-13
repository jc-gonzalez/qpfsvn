#!/bin/bash
##############################################################################
# File       : pgsql_initdb.sh - PostgreSQL Database initialisation
# Domain     : QPF.scripts
# Version    : 2.0
# Date       : 2016/09/01
# Copyright (C) 2015-2018 J C Gonzalez
#_____________________________________________________________________________
# Purpose    : PostgreSQL Database initialisation
# Created by : J C Gonzalez
# Status     : Prototype
# History    : See <Changelog>
###############################################################################

rm -rf /home/eucops/opt/pgsql/data 
mkdir -p  /home/eucops/opt/pgsql/data
pg_ctl -D /home/eucops/opt/pgsql/data -l /home/eucops/opt/pgsql/logfile initdb

 
