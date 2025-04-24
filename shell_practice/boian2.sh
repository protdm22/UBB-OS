#!/bin/bash

tmp=$(mktemp)
find dir | grep -E "\.c$" >> "$tmp"

nr_files=0

while read -r line; do
    if [ `cat $line | wc -l` -gt 500 ]; then
        echo $line
        #nr_files=$((nr_files+1))
        nr_files=`expr $nr_files + 1`
    fi

    if [ $nr_files -eq 2 ]; then
        break
    fi
done < "$tmp"

