#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Incorrect number of arguments"
fi

N=0
while read -p "Enter N: " N; do
    if [ "$N" = "0" ]; then
        break
    fi

    if echo "$N" | grep -E -q "^[^0-9]*$" ; then
        echo N must be an integer
        continue
    fi

    for file in $@; do
        if file "$file" | grep -q "ASCII text"; then
            echo Filename: "$file"
            echo Number of lines: `cat "$file" | wc -l`
            linect=1
            tmp=$(mktemp)
            while read -r line; do
                count=0
                countN=0
                for item in $line; do
                    if echo "$item" | grep -E -q "[0-9]+"; then
                        count=`expr $count + 1`
                        if echo "$item" | grep -E -q "[0-9]{$N}"; then
                            countN=$((countN + 1))
                        fi
                    fi
                done
                echo Line "$linect" has "$countN" numbers with "$N" digits
                if [ $((count%2)) -eq 1 ]; then
                    digits=$(("$N" - 1))
                    sed -E "s/([0-9]{$digits})/$N\1/" >> $tmp
                else
                    echo "$line" >> $tmp
                fi
                linect=$((linect + 1))
            done < "$file"
            cat "$tmp" > $file
        fi

    done
done
