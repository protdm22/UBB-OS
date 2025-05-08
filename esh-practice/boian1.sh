#!/bin/bash


tmp=$(mktemp)
cat who.fake > "$tmp"

line=""

while read -r line; do
    user=`echo "$line" | cut -d ' ' -f 1`
    echo "$user" `cat ps.fake | grep -E "^$user" | wc -l`
done < "$tmp"
