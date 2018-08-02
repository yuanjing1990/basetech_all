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

#delete file which size is zero
#usage:
#	delete_0file DIR
# 删除空文件
#	find / -type f -size 0 -exec rm -rf {} \;
delete_0file() {
	if [ ! -d $1 ]; then
		echo "error parameter:need a DIR path"
		return 1
	fi
	find $1 -type f -size 0 -exec rm {} \;
}

#kill process with NAME
#usage:
#	killp NAME
# 查找进程pid并kill
#	pgrep nginx|xargs kill
#	pidof nginx|xargs kill
killp() {
	if [ $# -lt 1 ]; then
		echo "error:Need a process name"
		return 1
	fi
	pgrep $1|xargs kill
}

#get ip address with NET_NAME device
#usage:
#	get_ip NET_NAME
# 获取当前IP地址
#	ifconfig |awk -F"[ ]+|[:]" 'NR==2 {print $4}'
get_ip() {
	if [ $# -lt 1 ]; then
		echo "error:Need a net device name"
		return 1
	fi
	ifconfig $1|awk -F"[ ]+|[:]" 'NR==2 {print $4}'
}

#sort process with memory usage
#usage:
#	ps_ex
# 以内存大小排序列出进程
#	ps aux --sort=rss |sort -k 6 -rn
ps_ex() {
	ps aux --sort=rss |sort -k 6 -rn
}

#start a web server on port 8000
#usage:
#	webserver
# 简单web server列出当前目录文件，端口8000
#	python -m SimpleHTTPServer
webserver() {
	python -m SimpleHTTPServer
}

mkcd() {
	mkdir $1
	cd $1
}

tmpstr() {
	cat /dev/urandom | tr -dc 'a-zA-Z0-9' | fold -w 32 | head -n 1
}

wget_site() {
	wget -r -p -np -k $1
}