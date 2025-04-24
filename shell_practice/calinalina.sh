#!/bin/bash

if [ $# -ne 2 ]; then
    echo Wrong number of parameters
    exit 1
fi

F=$1
U=`grep "$2" /etc/passwd | awk -F: '{print $1}'`

if [ ! -f "$F" ]; then
    echo First arg is not a file
    break
fi

if [ -z "$U" ]; then
    echo Second arg is not a user
    break
fi

ct=0

while true; do
    if [ $ct -eq 3 ]; then
        break
    fi

    read -p "Enter string: " str

    if [ -d "$str" ]; then
        sizes=`du -b "$str" | awk '{print $1}'`
        total_size=0
        for size in $sizes; do
            total_size=$(($total_size + $size))
        done
        echo Size: $total_size bytes

        all_files=`find "$str" | tail -n +2`
        for file in $all_files; do
            fn=`echo "$file" | awk -F/ '{print $NF}'`
            if [ "$fn" = "$F" ]; then
                echo File is in the directory
                ct=$((ct+1))
            fi
        done
    
    elif [ -f "$str" ]; then
        perm=`ls -l "$str" | cut -c3`
        owner=`ls -l "$str" | awk '{print $3}'`
        echo "$owner" "$U"
        if [ "$perm" = "w" ]; then
            echo It has write permissions
        fi
        if [ "$owner" = "$U" ]; then
            echo The user is the owner of the file
        fi
    
    else
        echo "$str" >> strings.txt
    fi
done
