#!/bin/sh
#usage:
#   ./runtest_on_emulator.sh MODULE_NAME
MODULE_NAME=$1
LD_LIBRARY_PATH=/data/lib:/lib:/system/lib:/usr/lib/qt/lib
PATH=/data/bin:/system/xbin:/sbin:/bin:/system/bin:/usr/sbin:/usr/lib/qt/bin

gtst${MODULE_NAME}service --gtest_output=xml:/data/test-result-gtst${MODULE_NAME}service.xml

