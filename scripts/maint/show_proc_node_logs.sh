#!/bin/bash

QPFSYSDIR=${HOME}/qpf
QPFRUNDIR=${QPFSYSDIR}/run

lastRunPath=$(ls -drt ${QPFRUNDIR}/2* | tail -1)

if [ "$1" == "-r" ]; then
    logDir=${lastRunPath}/rlog
else
    logDir=${lastRunPath}/log
fi

xpos=80
ypos=40
width=160
height=10
step=150

font=6x10

logFiles=$(ls ${logDir}/*.log)

for logFile in ${logFiles} ; do
    xterm -geometry ${width}x${height}+${xpos}+${ypos} -fn ${font} -e tail -f $logFile &
    ypos=$(($ypos + $step))
done
