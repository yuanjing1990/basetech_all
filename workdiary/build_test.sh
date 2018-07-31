#!/bin/bash
#usage:
#	./build_test.sh MODULE_NAME
PROJECT_ROOT=Goni
MODULE_NAME=$1
cd ${PROJECT_ROOT}
BUILD_COV_INSTRUMENT=False make clean-gtst${MODULE_NAME}service clean-lib${MODULE_NAME}service -j4
BUILD_COV_INSTRUMENT=True  make gtst${MODULE_NAME}service lib${MODULE_NAME}service -j4

