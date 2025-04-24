#!/bin/bash

while $1; do
    bad_procs="dangerous boo hoo"
    for proc in $bad_procs; do
        line=`ps -ef | grep "$proc" | grep -v "grep"`
        id=`echo $line | cut -d ' ' -f2`
        if [ ! -z $id ]; then
            echo Process "$id" terminated
            kill $id
        fi
    done
   
    sleep 1
done
