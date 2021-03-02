set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_FIND_ROOT_PATH /home/yuanjing/tmp/gcc-arm-none-eabi-10-2020-q4-major /home/yuanjing/tmp/gcc-arm-none-eabi-10-2020-q4-major/arm-none-eabi)
set(CMAKE_C_COMPILER /home/yuanjing/tmp/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER /home/yuanjing/tmp/gcc-arm-none-eabi-10-2020-q4-major/bin/arm-none-eabi-g++)
set(CMAKE_C_COMPILER_FORCED true)
set(CMAKE_CXX_COMPILER_FORCED true)

set(CMAKE_EXE_LINKER_FLAGS --specs=nosys.specs)

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

