#!/bin/bash

#echo $#
#echo #@

while [ $# -gt 0 ] && ! echo "$1" | grep -q "^-"; do
    echo File "$1"
    shift 1
done

ct=1
if [ $1 = "-s" ] || [ $1 = "--session session-id" ]; then
    shift 1
    while [ $# -gt 0 ]; do
        echo Param"$ct" "$1"
        ct=$((ct+1))
        shift 1
    done
fi
