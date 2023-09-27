cmake_minimum_required(VERSION 3.0 )

project(rpc.0.0.1)


add_compile_options(-g -std=c++17  -fPIC)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)



include_directories(${CMAKE_SOURCE_DIR}/envelop)
include_directories(${CMAKE_SOURCE_DIR}/sig)
include_directories(${CMAKE_SOURCE_DIR}/proto)
include_directories(${CMAKE_SOURCE_DIR}/api)
include_directories(${CMAKE_SOURCE_DIR}/evmone)



#file(GLOB SOURCE_CODE "JNI/*.cpp" "envelop/*.cpp" "sig/*.cpp" "proto/*.cc" "GO/*.cpp")
file(GLOB SOURCE_CODE  "envelop/*.cpp" "sig/*.cpp" "proto/*.cc" "api/*.cpp" "evmone/*.cpp")



add_library(${PROJECT_NAME} SHARED ${SOURCE_CODE})

add_executable(test "test/main.cpp")



if(CMAKE_HOST_UNIX)
message("link linux")
    target_link_libraries(${PROJECT_NAME} dl)
    target_link_libraries(${PROJECT_NAME} pthread)
    target_link_libraries(${PROJECT_NAME} libssl.a)
    target_link_libraries(${PROJECT_NAME} libcrypto.a)
    target_link_libraries(${PROJECT_NAME} libprotobuf.a)
elseif(CMAKE_HOST_WIN32)
message("link windows")
    target_link_libraries(${PROJECT_NAME} libssl.lib)
    target_link_libraries(${PROJECT_NAME} libcrypto.lib)
    target_link_libraries(${PROJECT_NAME} protobuf)
    target_link_libraries(${PROJECT_NAME} ws2_32.lib)
else()
    message("unkown platform")
endif()

#add_executable(main main.cpp)
target_link_libraries(test  ${PROJECT_NAME})
#target_link_libraries(test  ${PROJECT_NAME} pthread dl)