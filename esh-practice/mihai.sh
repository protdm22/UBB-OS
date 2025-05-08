```
#!/bin/bash

if [ $# -lt 1 ]
then
	echo Please input at least one argument
	exit 1
fi

# Get the file contents
fileContents=""
while [ $# -gt 0 ] && ! echo "$1" | grep -Eq "^-"
do
	if [ ! -r "$1" ]
	then
		continue
	fi

	fileContents="$fileContents"$'\n'`cat "$1"`
	shift 1
done

while [ $# -gt 0 ]
do
	arg="$1"
	shift 1

	if [ "$arg" == "-s" ] || [ "$arg" == "--session" ]
	then
		# Treat the var as session id
		while [ $# -gt 0 ] && ! echo "$1" | grep -Eq "^-"
		do
			# Check if the ! is present
			args="-E"

			if echo "$1" | grep -Eq "^\!"
			then
				args="${args}v"
			fi

			echo "==== SESSION $1 ===="
			echo "$fileContents" | grep "$args" "$1"
			echo "===================="

			shift 1
		done

	elif [ "$arg" == "-u" ] || [ "$arg" == "--user" ]
	then
		# Treat the var as username
		while [ $# -gt 0 ] && ! echo "$1" | grep -Eq "^-"
		do
			# Check if the ! is present
			args="-E"

			if echo "$1" | grep -Eq "^\!"
			then
				args="${args}v"
			fi
			echo "==== USER $1 ===="
			echo "$fileContents" | grep $args "$1"
			echo "===================="

			shift 1
		done
	
	elif [ "$arg" == "-c" ] || [ "$arg" == "--client" ]
	then
		# Treat the var as ip
		while [ $# -gt 0 ] && ! echo "$1" | grep -Eq "^-"
		do
			# Check if the ! is present
			args="-E"

			if echo "$1" | grep -Eq "^\!"
			then
				args="${args}v"
			fi
			echo "==== CLIENT $1 ===="
			echo "$fileContents" | grep $args "$1"
			echo "===================="

			shift 1
		done
	
	elif [ "$arg" == "-d" ] || [ "$arg" == "--date" ]
	then
		# Treat the var as date (d/m/y)
		while [ $# -gt 0 ] && ! echo "$1" | grep -Eq "^-"
		do

			# Check if the ! is present
			args="-E"

			if echo "$1" | grep -Eq "^\!"
			then
				args="${args}v"
			fi
			# Check if it has a plus or - at the end
			
			day=`echo "$1" | cut -d/ -f1`
			month=`echo "$1" | cut -d/ -f2`
			year=`echo "$1" | cut -d/ -f3 | cut -d"+" -f1`

	
			if echo "$1" | grep -Eq "\+$"
			then
				
				

				echo "==== AFTER DATE $1 ===="
				# For each line check if it's after the given date
				while read line
				do
					#echo line: "$line"
					dat=`echo "$line" | cut -d, -f1`
					cmpyr=`echo "$dat" | cut -d/ -f3`
					cmpmn=`echo "$dat" | cut -d/ -f2`
					cmpd=`echo "$dat" | cut -d/ -f1 | cut -d"[" -f2`
					while_line=`echo "$line" | cut -d, -f2`
					
					
					if [ "$cmpyr" -gt "$year" ] || [ "$cmpyr" -le "$year" ] && [ "$cmpmn" -gt "$month" ] || [ "$cmpyr" -le "$year" ] && [ "$cmpmn" -le "$month" ] && [ "$cmpd" -gt "$day" ]; then
		echo "$while_line"
		fi

				done < <(echo "$fileContents" | awk '{print $1","$0}') 2> /dev/null
				echo "======================="


			else

				echo "==== DATE $1 ===="
				echo "$fileContents" | grep $args "$1"
				echo "===================="

			fi

			shift 1
		done
	fi
done

```
