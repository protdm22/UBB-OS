#!/bin/bash
# Read the console input until the user provides a filename that exists and can be read

rem=`expr $# % 2`

if [ $rem -eq ] ; then
	echo "Can't print arguments two by two because $# is odd"
	exit 1
fi

while [  ] ; do
	echo $1 and $2
	shift 2
done

F=""
while [ -z $F ] || ! [ -f $F ] || ! [ -r $F ] ; do
	read -p "Give a valid file name: "
done
