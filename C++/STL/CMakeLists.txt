cmake_minimum_required(VERSION 2.8)

add_executable(ColorCode ColorCode.cpp)

include_directories(./search/)
add_executable(constructor constructor.cpp)

add_executable(memorycheck memorycheck.cpp)

add_executable(newhandler newhandler.cpp)

add_executable(overnew overnew.cpp)

add_executable(preprocess preprocess.cpp)

add_executable(rtti rtti.cpp)

add_executable(test_prog test.cpp)
target_link_libraries(test_prog boost_unit_test_framework boost_system)

add_subdirectory(example_boost)
add_subdirectory(exprtmp)
add_subdirectory(meta)
add_subdirectory(mystl)
add_subdirectory(parameter)
add_subdirectory(search)
add_subdirectory(traits)
add_subdirectory(types)