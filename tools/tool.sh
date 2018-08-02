#!/bin/bash
# https://www.jb51.net/article/48057.htm

usage() {
	if [ $1 -eq "clear_dir" ]; then
		echo "usage: clear_dir DIR"
	fi
}

#delete all file in dir
#usage:
#	clear_dir DIR
# 目录中大量文件删除：ls | xargs rm
clear_dir() {
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

#cat file exclude lines leading with "#"
#usage:
#	cat_bash FILE
# 查看文件排除以#开关和空白行，适合查看配置文件
#	egrep -v "^#|^$" filename
#	sed '/#.*$/d; /^ *$/d' filename
cat_bash() {
	if [ ! -f $1 ]; then
		echo "error parameter:need a FILE path"
		return 1
	fi
	egrep -v "^#|^$" $1
}

#delete space in file
#usage:
#	delete_space filename
# 删除空格和空行
#	sed 's/ //g' filename
#	sed 's/[[:space:]]//g' filename
delete_space() {
	if [ ! -f $1 ]; then
		echo "error parameter:need a FILE path"
		return 1
	fi
	sed 's/ //g' $1
}

