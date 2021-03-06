#======================================================================
# CMakeLists.txt
# QPF - Prototype of QLA Processing Framework
# General Project File
#======================================================================
# Author: J C Gonzalez - 2015-2018
# Copyright (C) 2015-2018 Euclid SOC Team at ESAC
#======================================================================
include (../common.cmake)

project (tools)

set (libtools_hdr
  process.h
  propdef.h
  alert.h
  dwatcher.h
  filetools.h
  launcher.h
  metadatareader.h
  rwc.h
  scopeexit.h
  sm.h
  timer.h
  tools.h
  watchdog.h
  dckwatchdog.h
  dckwatchdog_cmds.h
)

set (libtools_src
  alert.cpp
  dwatcher.cpp
  filetools.cpp
  launcher.cpp
  rwc.cpp
  sm.cpp
  timer.cpp
  tools.cpp
  watchdog.cpp
  dckwatchdog.cpp
)

#find_package(CURL REQUIRED)

add_library(tools SHARED ${libtools_src})
target_include_directories (tools PUBLIC .
  ${CURLINCDIR}
  ${STR_ROOT_DIR}
  ${JSON_ROOT_DIR}
  ${FMK_ROOT_DIR}
  ${NNCOMM_ROOT_DIR}
  ${TOOLS_ROOT_DIR})
target_link_libraries (tools str json pthread)
set_target_properties (tools PROPERTIES LINKER_LANGUAGE CXX)
install (TARGETS tools
         RUNTIME DESTINATION bin
         ARCHIVE DESTINATION lib
         LIBRARY DESTINATION lib)
