#!/bin/bash
#usage:
#	./push_test_program.sh MUDULE_NAME
PROJECT_ROOT=Goni
MODULE_NAME=$1
adb push ${PROJECT_ROOT}/out/target/product/generic/symbols/system/bin/gtst${MODULE_NAME}service /data/bin/gtst${MODULE_NAME}service
adb push ${PROJECT_ROOT}/out/target/product/generic/symbols/system/lib/lib${MODULE_NAME}service.so /data/lib/lib${MODULE_NAME}service.so
adb push ${PROJECT_ROOT}/out/target/product/generic/symbols/system/lib/lib${MODULE_NAME}stub.so /data/lib/lib${MODULE_NAME}stub.so

adb push runtest_on_emulator.sh /tmp/

