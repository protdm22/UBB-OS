#!/bin/bash

tmp=$(mktemp)
find dir -type f > "$tmp"

while read -r file; do
    perm=`ls -l "$file" | cut -c9`
    if [ "$perm" = "w" ]; then
        ls -l "$file"
        chmod o-w "$file"
        ls -l "$file"
    fi
done < "$tmp"
