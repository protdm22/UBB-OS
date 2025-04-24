#!/bin/bash

tmp=$(mktemp)
find -L dir -type l > "$tmp"

while read -r symbolic_link; do
    if [ ! -e $symbolic_link ]; then
        echo "$symbolic_link"
    fi
done < "$tmp"


