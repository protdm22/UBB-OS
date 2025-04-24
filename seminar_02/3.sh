#!/bin/bash

echo $# is the number of arguments
echo $0 is the name of the script

for arg in $@
do
	if test -f $arg
	then
		echo $arg is a filename
	elif test -d $arg
	then
		echo $arg is a directory
	fi
done
