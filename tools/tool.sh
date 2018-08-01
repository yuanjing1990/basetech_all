#!/bin/bash

usage() {
	if [ $1 -eq "clear_dir" ]; then
		echo "usage: clear_dir DIR"
	fi
}

#delete all file in dir
clear_dir() {
	echo $@
	if [ $# -lt 1 ]; then
		usage $0
		return 1
	fi
	if [ ! -d $1 ]; then
		echo "error parameter:need a DIR path"
		return 1
	fi
	cd $1 && ls|xargs rm && cd -
}
