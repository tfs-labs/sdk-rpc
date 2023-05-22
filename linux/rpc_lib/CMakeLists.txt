cmake_minimum_required(VERSION 3.0 )

project(don_rpc.0.0.1)

execute_process(COMMAND sh dep.sh
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

link_directories(${CMAKE_SOURCE_DIR}/lib/lib)
link_directories(${CMAKE_SOURCE_DIR}/lib/lib64)
add_compile_options(-gdwarf-2 -std=c++17 --shared )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/lib/include)
include_directories(${CMAKE_SOURCE_DIR}/envelop)
include_directories(${CMAKE_SOURCE_DIR}/sig)
include_directories(${CMAKE_SOURCE_DIR}/proto)
include_directories(${CMAKE_SOURCE_DIR}/api)



file(GLOB SOURCE_CODE  "envelop/*.cpp" "sig/*.cpp" "proto/*.cc" "api/*.cpp")




add_library(${PROJECT_NAME} SHARED ${SOURCE_CODE})

target_link_libraries(${PROJECT_NAME} libssl.a)
target_link_libraries(${PROJECT_NAME} libcrypto.a)
target_link_libraries(${PROJECT_NAME} protobuf)

#add_executable(main main.cpp)
#target_link_libraries(main  ${PROJECT_NAME})