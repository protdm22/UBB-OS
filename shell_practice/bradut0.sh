#!/bin/bash

user_ct=0
file_ct=0
other_ct=0

while $1; do
    read -p "Enter string: " str
    if [ "$str" = "stop" ]; then
        break
    fi

    if grep -q "^$str:" /etc/passwd; then
        user_ct=$((user_ct+1))
        home=`grep "^$str:" /etc/passwd | awk -F: '{print $6}'`
        echo Number of text files: `find "$home" -type f -name "*.txt" | wc -l`
    
    elif [ -f "$str" ]; then
        file_ct=$((file_ct+1))
        tmp=`grep -E -i -v "ana" "$str"`
        echo "$tmp" > "$str"
    
    else
        other_ct=$((other_ct+1))
        echo The string given is neither a user or a file
    fi
done

sum=$((user_ct + $file_ct + $other_ct))

p1=$(($user_ct*100/$sum))
p2=$(($file_ct*100/$sum))
p3=$(($other_ct*100/$sum))

echo Users: "$p1"%
echo Files: "$p2"%
echo Other: "$p3"%
