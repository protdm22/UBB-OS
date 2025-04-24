#!/bin/bash

echo $# is the number of arguments
echo $@ is the list of arguments

if test $# -lt 1; then
	echo  We need one argument
	exit 1
fi

if | grep -E -q "$1" /etc/passwd
then
	echo First argument is not a valid username on this system
	exit 1
fi

nr=`ps -ef | grep -E -c "^$1"` 
echo Username $1 is currently running $nr processes.#`
