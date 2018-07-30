#!/bin/bash
PROJECT_ROOT=${PWD}/Goni
MODULE_NAME=dt

adb pull /data/test-result-gtst${MODULE_NAME}service.xml test_result/application_dtservice/test-result-gtst${MODULE_NAME}service.xml

adb pull /data/local/tmp/profile/out/target/product/generic/obj/SHARED_LIBRARIES/lib${MODULE_NAME}service_intermediates ${PROJECT_ROOT}/out/target/product/generic/obj/SHARED_LIBRARIES/lib${MODULE_NAME}service_intermediates

adb pull /data/local/tmp/profile/out/target/product/generic/obj/EXECUTABLES/gtst${MODULE_NAME}service_intermediates ${PROJECT_ROOT}/out/target/product/generic/obj/EXECUTABLES/gtst${MODULE_NAME}service_intermediates

cp -r ${PROJECT_ROOT}/out/target/product/generic/obj/SHARED_LIBRARIES/lib${MODULE_NAME}service_intermediates/. ${PROJECT_ROOT}/platform/service/${MODULE_NAME}service/${MODULE_NAME}service/
cp -r ${PROJECT_ROOT}/out/target/product/generic/obj/EXECUTABLES/gtst${MODULE_NAME}service_intermediates/. ${PROJECT_ROOT}/platform/service/${MODULE_NAME}service/tests/

lcov --gcov-tool=${PROJECT_ROOT}/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-gcov -c -d ${PROJECT_ROOT}/platform/service/${MODULE_NAME}service/tests -t gtst{MODULE_NAME}service --rc lcov_branch_coverage=1 -o test-lcov-gtst${MODULE_NAME}service.info
genhtml -q test-lcov-gtst${MODULE_NAME}service.info  --legend --highlight --no-function-coverage --branch-coverage -o test-lcov-gtst${MODULE_NAME}service_result_${DATE}_branch

lcov --gcov-tool=${PROJECT_ROOT}/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-gcov -c -d ${PROJECT_ROOT}/platform/service/${MODULE_NAME}service/${MODULE_NAME}service -t lib{MODULE_NAME}service --rc lcov_branch_coverage=1 -o test-lcov-lib${MODULE_NAME}service.info
genhtml -q test-lcov-lib${MODULE_NAME}service.info  --legend --highlight --no-function-coverage --branch-coverage -o test-lcov-lib${MODULE_NAME}service_result_${DATE}_branch

lcov --gcov-tool=${PROJECT_ROOT}/prebuilts/gcc/linux-x86/arm/arm-linux-androideabi-4.6/bin/arm-linux-androideabi-gcov -c -d ${PROJECT_ROOT}/platform/service/${MODULE_NAME}service/${MODULE_NAME}service -t lib{MODULE_NAME}service -o test-lcov-lib${MODULE_NAME}service.info
genhtml -q test-lcov-lib${MODULE_NAME}service.info  --legend --highlight --no-function-coverage -o test-lcov-lib${MODULE_NAME}service_result_${DATE}_line


