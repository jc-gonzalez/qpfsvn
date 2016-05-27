##############################################################################
# File       : BuildQPF.sh - QPF Compilation and Installation script
# Domain     : QPF.scripts
# Version    : 1.0
# Date       : 2016/04/01
# Copyright (C) 2015, 2016 J C Gonzalez
#_____________________________________________________________________________
# Purpose    : Compile and Install QPF binaries in target platform
# Created by : J C Gonzalez
# Status     : Prototype
# History    : See <Changelog>
###############################################################################

###### Script variables

#- This script path and name
SCRIPT_PATH="${BASH_SOURCE[0]}";
SCRIPT_NAME=$(basename "${SCRIPT_PATH}")
if [ -h "${SCRIPT_PATH}" ]; then
    while [ -h "${SCRIPT_PATH}" ]; do
        SCRIPT_PATH=$(readlink "${SCRIPT_PATH}")
    done
fi
pushd . > /dev/null
cd $(dirname ${SCRIPT_PATH}) > /dev/null
SCRIPT_PATH=$(pwd)
popd  > /dev/null

#- QPF source code paths
QPF_PATH=$(dirname "${SCRIPT_PATH}")
BUILD_PATH="${QPF_PATH}"/build
RUN_PATH="${QPF_PATH}"/run

QPF_WA_PKG="${RUN_PATH}/QPF-workarea.tgz"
QPF_SQ_SCPT="${RUN_PATH}/qpfdb.sql"
QPF_EXE="qpfhmi/qpfhmi"
QPF_LIBS="libcomm/liblibcomm infix/libinfix json/libjson sdc/libsdc src/libQPF"

#- Messages
_ONHDR="\e[1;49;93m"
_ONMSG="\e[1;49;92m"
_ONRUN="\e[0;49;32m"
_ONERR="\e[1;49;91m"
_OFF="\e[0m"
STEP=0

#- Options
COMPILE="no"
INSTALL="no"
FAKE="no"
REMOVE="no"
RECREATEDB="no"
WORK_AREA="${HOME}"
PSQL_HOST="localhost"
PSQL_PORT="5432"

MAKE_OPTS="-k -j4"

#- Other
DATE=$(date +"%Y%m%d%H%M%S")
LOG_FILE=./build_${DATE}.log
VERSION=$(cat "${QPF_PATH}/VERSION")
LDLIBS=$(echo $LD_LIBRARY_PATH | tr ':' ' ')

###### Handy functions

greetings () {
    say "${_ONHDR}==============================================================================="
    say "${_ONHDR} Euclid QLA Processing Framework"
    say "${_ONHDR} Version ${VERSION}"
    say "${_ONHDR} Compilation and Installation process"
    say "${_ONHDR} Build time-stamp: ${DATE}"
    say "${_ONHDR}==============================================================================="
    say ""
}

usage () {
    local opts="[ -h ] [ -c ] [ -i ] [ -n ] [ -r ] [ -b ]"
    opts="$opts [ -w <path> ] [ -H <host> ] [ -P <port> ]"
    say "Usage: ${SCRIPT_NAME} $opts"
    say "where:"
    say "  -h         Show this usage message"
    say "  -c         Compile the source code"
    say "  -i         Install libraries and binary"
    say "  -n         Show the actions without executing them"
    say "  -r         Clear previous build"
    say "  -b         Re-create PostsgreSQL system database"
    say "  -w <path>  Folder to locate QPF working area (default:HOME)"
    say "  -H <host>  Host where system database is located (default:${PSQL_HOST})"
    say "  -P <port>  Port to access the database (default:${PSQL_PORT})"
    say ""
    exit 1
}

say () {
    echo -e "$*${_OFF}"
    echo -e "$*" | sed -e 's#.\[[0-9];[0-9][0-9];[0-9][0-9]m##g' >> "${LOG_FILE}"
}

step () {
    say "${_ONMSG}## STEP ${STEP} - $*"
    STEP=$(($STEP + 1))
}

die () {
    say "${_ONERR}ERROR: $*"
    exit 1
}

perform () {
    if [ "${FAKE}" == "yes" ]; then
        say "${_ONRUN}: $*"
    else
        eval $* 2>&1 | tee -a "${LOG_FILE}"
    fi
}

checkapp () {
    local app=$1
    wapp=$(which ${app})
    [ -z "${wapp}" ] && die "Program '${app}' appear is either not installed or not available"
    eval ${app}_exe="${wapp}"
    say "  - Program '${app}' found!"
}

searchlib () {
    local lib=$1
    wlib=""
    for l in ${LDLIBS}; do
        if [ -z "$wlib" ]; then
            wlib=$(find $l \( -name "lib${lib}*.so" -o -name "lib${lib}.a" \) -print)
        fi
    done
    if [ -z "${wlib}" ]; then
        searchsyslib $lib
    fi
    say "  - Library '${lib}' found!"
}

searchsyslib () {
    local lib=$1
    wlib=$(ldconfig -p | fgrep lib${lib}.)
    [ -z "${wlib}" ] && die "Library '${lib}' appear is either not installed or not reachable"
    say "  - Library '${lib}' found!"
}

install_exe () {
    local exe=$1
    say "  - Installing executable $exe"
    perform cp "'${BUILD_PATH}/${exe}'" "'${WORK_AREA}/qpf/bin/'"
}

install_lib () {
    local lib=$1
    say "  - Installing library $lib"
    for l in  "${BUILD_PATH}/"${lib}* ; do
        perform cp -d "'$l'" "'${WORK_AREA}/qpf/lib/'"
    done
}

###### Start

## Parse command line
while getopts :hcinrbw:H:P: OPT; do
    case $OPT in
        h|+h) usage ;;
        c|+c) COMPILE="yes" ;;
        i|+i) INSTALL="yes" ;;
        n|+n) FAKE="yes" ;;
        r|+r) REMOVE="yes" ;;
        b|+b) RECREATEDB="yes" ;;
        w|+w) WORK_AREA="$OPTARG" ;;
        H|+H) PSQL_HOST="$OPTARG" ;;
        P|+P) PSQL_PORT="$OPTARG" ;;
        *)    usage ; exit 2
    esac
done
shift `expr $OPTIND - 1`
OPTIND=1

## Say hello
greetings

## Checking required applications and libraries are installed
step "Checking required applications and libraries are installed"

checkapp qmake
checkapp make
checkapp psql

searchlib Qt
searchlib zmq
searchlib pcre2
searchlib sodium
searchlib curl
searchlib pq

## Creating build folder
step "Creating build folder"

if [ "${REMOVE}" == "yes" ]; then
    perform rm -rf ${BUILD_PATH}
fi
perform mkdir -p "'${BUILD_PATH}'"

## Generating dependencies and setting makefiles
step "Generating dependencies and setting makefiles"

if [ "${COMPILE}" == "yes" ]; then
    perform cd "'${BUILD_PATH}'"
    perform $qmake_exe ../QPF.pro
fi

## Compiling source code
step "Compiling source code"

if [ "${COMPILE}" == "yes" ]; then
    perform make ${MAKE_OPTS}
fi

## Setting up Work Area in /tmp
step "Setting up Work Area in /tmp"

if [ ! -d "${WORK_AREA}" ]; then
    perform mkdir -p "'${WORK_AREA}'"
fi

perform tar xzCf "'${WORK_AREA}'" "'${QPF_WA_PKG}'"

## Installing QPF executable and libraries
step "Installing QPF executable and libraries"

install_exe ${QPF_EXE}

for l in ${QPF_LIBS}; do
    install_lib $l
done

## Creating QPFDB database
step "Setting up QPF database"

if [ "${RECREATEDB}" == "yes" ]; then
    QPF_DB_LOCATION="-h ${PSQL_HOST} -p ${PSQL_PORT}"
    perform psql postgres ${QPF_DB_LOCATION} -q -c "'DROP DATABASE qpfdb;'"
    perform psql postgres ${QPF_DB_LOCATION} -q -c "'CREATE DATABASE qpfdb OWNER eucops;'"
    perform psql qpfdb    ${QPF_DB_LOCATION} -q -f "'${QPF_SQ_SCPT}'" -o "'${LOG_FILE}.sqlout'"
fi

## Finishing
step "Final comments"

say "Compilation/Installation finished."
say ""
say "-------------------------------------------------------------------------------"
say "Please, do not forget to:"
say "  - include the directory ${WORK_AREA}/qpf/bin in the PATH variable, and"
say "  - include the directory ${WORK_AREA}/qpf/lib in the LD_LIBRARY_PATH variable."
say ""
say "In order to check that the QPF HMI executable and the libraries were correctly"
say "installed, you may run:"
say "  $ qpfhmi -h "
say "and see if the application shows a help message."
say ""
say "Initial configuration files (in JSON) are available at ${WORK_AREA}/qpf/cfg."
say "You may need to modify them before launching any processing task from the HMI."
say "(Runing qpfhmi without specifying a configuration file will mean reading"
say "last configuration used from internal database)."
say "-------------------------------------------------------------------------------"
say ""

exit 0