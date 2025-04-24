#!/bin/bash

s=""

while [ ! -n "$s" ] || [ "$s" != "stop" ]
do
    read -p "Enter a string: " s
    if grep -q "^$s:" /etc/passwd; then
        echo "$s is a user"
        awk -F: -v home=$s '$1 == home {print $6}' /etc/passwd | find -name "*.c" -type f | wc -l
        
    elif [ -f $s ]; then
        echo "$s is a file"
        sed -E '/ana/d' $s -i
    fi

done
