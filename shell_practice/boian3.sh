#!/bin/bash

touch lines
find dir -type f -name "*.log" > lines

while read -r file_path; do
    tmp=$(mktemp)
    cat "$file_path" | sort > $tmp
    mv "$tmp" "$file_path"
done < lines

rm lines
