#!/bin/bash
PROJECT_ROOT=Goni
MODULE_NAME=dt
cd ${PROJECT_ROOT}
BUILD_COV_INSTRUMENT=False make clean-gtst${MODULE_NAME}service clean-lib${MODULE_NAME}service -j4
BUILD_COV_INSTRUMENT=True  make gtst${MODULE_NAME}service lib${MODULE_NAME}service -j4

