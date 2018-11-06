#!/bin/bash

#使用gitlab api自动创建项目
projects="pro1 \
pro2 \
pro3 "

 
my_private_token=

for project in $projects
do
    info="name=$project&path=$project&wiki_enabled=no&public_jobs=true&public=true&namespace_id=3&default_branch=master"

    curl --header "PRIVATE-TOKEN:$my_private_token" -d $info "http://192.168.94.81/api/v4/projects"
done

#推送本地项目到服务器
dir_name="$PWD"
all=`ls ${dir_name}`

for i in $all
do
	if [ -d $i ] then
		echo "[$i]"
		cd $i
		
		git push --mirror git@192.168.94.81:git/$i
		cd ..
	fi
done 
