#!/bin/bash

act=$1

BINPATH=${HOME}/qpf/bin
CURDIR=$(pwd)

case $act in
    qdt)
        for i in VIS NISP; do
            proc=QLA_${i}_Processor
            cd ${BINPATH}/${proc}
            rm driver.py
            ln ../QDT/driver.py .
            for j in common config tools HKTM_qla NISP_qla VIS_qla ; do
                ln -sf ../QDT/$j .
            done
        done
        ;;
    qdtfake)
        for i in VIS NISP; do
            proc=QLA_${i}_Processor
            cd ${BINPATH}/${proc}
            rm driver.py
            ln -s driver-${i}-fake.py driver.py
        done
        ;;
    *)
        ;;
esac

cd ${CURDIR}

