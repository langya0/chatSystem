#!/bin/bash

proc=$0
function usage()
{
	printf "%s %s\n" "Usage: " "$proc:[start(-s)|stop(-t)]"
}



if [ $# -ne 1 ];then
	usage
	exit 1
fi

case $1 in
	'start' | '-s')
	# echo "start"
	start_client
	;;
	'stop' | '-t')
	echo "stop"
	;;
	* )
	echo "default"
	;;
esac