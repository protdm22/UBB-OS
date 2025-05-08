#!/bin/bash

tmp=$(mktemp)
cat df.fake | tail -n +2 | sed -E "s/[ ]+/ /g" | cut -d ' ' -f4,5,6 > "$tmp"

while read -r line; do
    size=`echo "$line" | cut -d ' ' -f1 | sed 's/M//'`
    usage=`echo "$line" | cut -d ' ' -f2 | sed 's/%//'`
    if [ $size -lt 1024 ] || [ $usage -gt 80 ]; then
        mfs=`echo "$line" | cut -d ' ' -f3`
        echo $mfs
    fi
done < "$tmp"
