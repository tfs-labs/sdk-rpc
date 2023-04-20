cmake_minimum_required(VERSION 3.0 )

project(jni_cpp)


link_directories(${CMAKE_SOURCE_DIR}/lib)
add_compile_options(-gdwarf-2 -std=c++17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/JNI)
include_directories(${CMAKE_SOURCE_DIR}/lib/include)
include_directories(${CMAKE_SOURCE_DIR}/envelop)
include_directories(${CMAKE_SOURCE_DIR}/sig)
include_directories(${CMAKE_SOURCE_DIR}/proto)


file(GLOB SOURCE_CODE "JNI/*.cpp" "envelop/*.cpp" "sig/*.cpp" "proto/*.cc")




add_library(${PROJECT_NAME} SHARED ${SOURCE_CODE})

target_link_libraries(${PROJECT_NAME} libssl.lib)
target_link_libraries(${PROJECT_NAME} libcrypto.lib)
target_link_libraries(${PROJECT_NAME} protobuf)

#add_executable(main main.cpp)
#target_link_libraries(main  ${PROJECT_NAME})