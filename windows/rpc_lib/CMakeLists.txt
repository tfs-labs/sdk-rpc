cmake_minimum_required(VERSION 3.0 )

project(rpc.0.0.1)


link_directories(${CMAKE_SOURCE_DIR}/lib)
add_compile_options(-gdwarf-2 -std=c++17 --shared)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/lib/include)
include_directories(${CMAKE_SOURCE_DIR}/envelop)
include_directories(${CMAKE_SOURCE_DIR}/sig)
include_directories(${CMAKE_SOURCE_DIR}/proto)
include_directories(${CMAKE_SOURCE_DIR}/GO)


file(GLOB SOURCE_CODE "envelop/*.cpp" "sig/*.cpp" "proto/*.cc" "api/*.cpp")




add_library(${PROJECT_NAME} STATIC ${SOURCE_CODE})

target_link_libraries(${PROJECT_NAME} libssl.lib)
target_link_libraries(${PROJECT_NAME} libcrypto.lib)
target_link_libraries(${PROJECT_NAME} protobuf)
