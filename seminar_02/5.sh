#!/bin/bash
# Order files received as arguments based on their size in bytes in reverse order

touch rezult.temp

for myfile in $@; do
	if [ -f $myfile ]	
	then 
		du -b $myfile >> rezult.temp
	fi
done

sort -nr rezult.temp
rm rezult.temp
