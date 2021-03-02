set(CMAKE_SYSTEM_NAME QNX)
set(CMAKE_SYSTEM_VERSION 1)

set(CMAKE_FIND_ROOT_PATH "$ENV{QNX_HOST}" "$ENV{QNX_TARGET}/aarch64le")
set(CMAKE_C_COMPILER "$ENV{QNX_HOST}/usr/bin/qcc")
set(CMAKE_CXX_COMPILER "$ENV{QNX_HOST}/usr/bin/qcc")
set(CMAKE_C_FLAGS "$ENV{CMAKE_C_FLAGS} -Wall -g -fPIC -fmessage-length=0 -fno-builtin -O0")
set(CMAKE_CXX_FLAGS "$ENV{CMAKE_CXX_FLAGS} -Wall -g -std=c++11 -fPIC -D_GLIBCXX_USE_CXX11_ABI=0 -U__STRICT_ANSI__ -lang-c++")
set(CMAKE_LINKER "${QNX_HOST}/usr/bin/ntoaarch64le-ld" CACHE PATH "QNX linker program" FORCE)

message(STATUS "CMAKE_C_COMPILER ${CMAKE_C_COMPILER}")
message(STATUS "CMAKE_CXX_COMPILER ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_C_FLAGS ${CMAKE_C_FLAGS}")
message(STATUS "CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS}")
message(STATUS "CMAKE_LINKER ${CMAKE_LINKER}")

# search for programs in the build host directories
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)