#!/bin/bash
#usage:
#	./init_env.sh USER_NAME

#1.install software
install_software(){
	sudo apt-get install git-core gnupg flex bison gperf build-essential \
	zip curl libc6-dev libncurses5-dev:i386 x11proto-core-dev \
	libx11-dev:i386 libreadline6-dev:i386 libgl1-mesa-glx:i386 \
	libgl1-mesa-dev mingw-w64 tofrodos \
	python-markdown libxml2-utils xsltproc zlib1g-dev:i386 u-boot-tools openssh-client libswitch-perl \
	cksfv uuid-dev:i386 liblzo2-dev:i386 lzop \
	android-tools-adb lcov \
	gcc gcc-multilib g++ g++-multilib
}
#gcc-4.4-multilib g++-4.4-multilib gcc-4.4 g++-4.4 
#2.config git
config_git(){
	git config --global user.name $1
	git config --global user.email $1@iauto.com
	git config --global core.autocrlf input
	git config --global core.safecrlf true
	git config --global color.ui true
}

#3.get repo tool
get_repo_tool(){
	if [ -d repo ]; then
		rm -rf repo
	fi
	git clone ssh://192.168.8.74:29418/tools/repo.git
	cd repo
	git checkout stable
	sudo cp repo /usr/bin
	sudo chmod a+x /usr/bin/repo
	cd ..
	rm -rf repo
}

#4.get project code
get_project_code(){
	if [ ! -d $1 ];then
		mkdir $1
		cd $1
		repo init -u ssh://192.168.8.74:29418/Src/$1/platform/manifest -b $2
		cd -
	fi

	cd $1
	repo sync
	repo start $2 --all
	cd -
}

#5.compile project
compile_project(){
	cd $1
	source build/envsetup.sh
	lunch full-eng
	make -j4
	ls out/targe/product/generic/system
}

#####################################################################
#The main progress
#
#
#####################################################################
PROJECT_NAME=Goni
BRANCH_NAME=Goni/Func/UT_lateVE
USER_NAME=$1

install_software
config_git ${USER_NAME}
if [ ! -e /usr/bin/repo ];then
	echo get_repo_tool
	get_repo_tool
fi
get_project_code ${PROJECT_NAME} ${BRANCH_NAME}
compile_project ${PROJECT_NAME}

