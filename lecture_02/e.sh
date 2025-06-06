#!/bin/bash

for A in $@; do
	if test -f $A; then
		echo $A is a file
	elif test -d $A
	then
		echo $A is a directory
	elif echo $A | grep -E -q "^[0-9]+$"; then
		echo $A is a number
		if test $A -gt 5; then
			echo $A is a number greater than 5
		fi
	else
		echo Not sure what $A is
	fi
done
