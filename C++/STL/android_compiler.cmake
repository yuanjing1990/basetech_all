# cmake -DCMAKE_TOOLCHAIN_PATH=android_compiler.cmake <CMakeLists_FilePath>
set(CMAKE_SYSTEM_NAME Android)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_FIND_ROOT_PATH /tmp/ndk-yuanjing/arm-linux-androideabi /usr/)
set(CMAKE_C_COMPILER ${CMAKE_FIND_ROOT_PATH}/bin/arm-linux-androideabi-gcc)
set(CMAKE_CXX_COMPILER ${CMAKE_FIND_ROOT_PATH}/bin/arm-linux-androideabi-g++)

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

