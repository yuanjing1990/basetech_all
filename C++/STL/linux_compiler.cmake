set(CMAKE_SYSTEM_NAME arm)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_FIND_ROOT_PATH /home/yuanjing/tmp/gcc-arm-none-eabi-10-2020-q4-major)
set(CMAKE_C_COMPILER_FORCED true)
set(CMAKE_C_COMPILER ${CMAKE_FIND_ROOT_PATH}/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER_FORCED true)
set(CMAKE_CXX_COMPILER ${CMAKE_FIND_ROOT_PATH}/bin/arm-none-eabi-g++)

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

