#!/bin/bash

ROOT_PATH=$(pwd)
BIN=$ROOT_PATH/udp_client
CONF=$ROOT_PATH/conf/conf

proc=$0

function usage()
{
	printf "%s %s\n" "Usage:$proc [start(-s) | stop(-t)]"
}

function is_server_exist()
{
	fun=$(basename $BIN)
	ret=$(pidof $fun)

	if [ -z "$ret" ];then
		return 1
	else
		return 0
	fi
}

function start_client()
{
	IP=$(grep -E 'PEER_IP' $CONF | awk -F: '{print $NF}')
	PORT=$(grep -E 'PEER_PORT' $CONF | awk -F: '{print $NF}')
	$BIN $IP $PORT
}

function stop_client()
{
	fun=$(basename $BIN)
	if [[ is_server_exist ]]; then
		pid=$(pidof $fun)
		kill -9 $pid
		#statements
	else
		echo "server is not  exist!"
	fi
}


if [ $# -ne 1 ];then
	usage
	exit 1
fi

case $1 in
	'start' | '-s' )
	start_client
	;;
	'stop' | '-t' )
	stop_client
	;;
	* )
	usage
	exit 2
	;;
esac

function start_client()
{
	IP=$(grep -E 'PEER_IP' $CONF |awk -F: '{print $NF}')
	PORT=$(grep -E 'PEER_PORT' $CONF |awk -F: '{print $NF}')
	$BIN $IP $PORT
}

function stop_client()
{
	fun=$(basename $BIN)
	if [[ is_server_exist ]]; then
		pid=$(pidof $fun)
		kill -9 $pid
		#statements
	else
		echo "server is not  exist!"
	fi
}
