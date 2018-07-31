#!/bin/bash
#usage:
#	./pull_test_result.sh MODULE_NAME MODULE_TYPE
PROJECT_ROOT=${PWD}/Goni
MODULE_NAME=$1
MODULE_TYPE=$2

adb pull /data/test-result-gtst${MODULE_NAME}service.xml test_result/application_${MODULE_NAME}service/test-result-gtst${MODULE_NAME}service.xml

adb pull /data/local/tmp/profile/out/target/product/generic/obj/SHARED_LIBRARIES/lib${MODULE_NAME}service_intermediates ${PROJECT_ROOT}/out/target/product/generic/obj/SHARED_LIBRARIES/lib${MODULE_NAME}service_intermediates

adb pull /data/local/tmp/profile/out/target/product/generic/obj/EXECUTABLES/gtst${MODULE_NAME}service_intermediates ${PROJECT_ROOT}/out/target/product/generic/obj/EXECUTABLES/gtst${MODULE_NAME}service_intermediates

cp -r ${PROJECT_ROOT}/out/target/product/generic/obj/SHARED_LIBRARIES/lib${MODULE_NAME}service_intermediates/. ${PROJECT_ROOT}/${MODULE_TYPE}/service/${MODULE_NAME}service/${MODULE_NAME}service/
cp -r ${PROJECT_ROOT}/out/target/product/generic/obj/EXECUTABLES/gtst${MODULE_NAME}service_intermediates/. ${PROJECT_ROOT}/${MODULE_TYPE}/service/${MODULE_NAME}service/tests/

lcov --gcov-tool=${PROJECT_ROOT}/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-gcov -c -d ${PROJECT_ROOT}/${MODULE_TYPE}/service/${MODULE_NAME}service/tests -t gtst{MODULE_NAME}service --rc lcov_branch_coverage=1 -o test-lcov-gtst${MODULE_NAME}service.info
genhtml -q test-lcov-gtst${MODULE_NAME}service.info  --legend --highlight --no-function-coverage --branch-coverage -o test-lcov-gtst${MODULE_NAME}service_result_${DATE}_branch

lcov --gcov-tool=${PROJECT_ROOT}/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-gcov -c -d ${PROJECT_ROOT}/${MODULE_TYPE}/service/${MODULE_NAME}service/${MODULE_NAME}service -t lib{MODULE_NAME}service --rc lcov_branch_coverage=1 -o test-lcov-lib${MODULE_NAME}service.info
genhtml -q test-lcov-lib${MODULE_NAME}service.info  --legend --highlight --no-function-coverage --branch-coverage -o test-lcov-lib${MODULE_NAME}service_result_${DATE}_branch

lcov --gcov-tool=${PROJECT_ROOT}/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-gcov -c -d ${PROJECT_ROOT}/${MODULE_TYPE}/service/${MODULE_NAME}service/${MODULE_NAME}service -t lib{MODULE_NAME}service -o test-lcov-lib${MODULE_NAME}service.info
genhtml -q test-lcov-lib${MODULE_NAME}service.info  --legend --highlight --no-function-coverage -o test-lcov-lib${MODULE_NAME}service_result_${DATE}_line


