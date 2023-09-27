cmake_minimum_required(VERSION 3.0 )

project(rpc.0.0.1)



if(CMAKE_HOST_UNIX)
    link_directories(${CMAKE_SOURCE_DIR}/lib/linux)
elseif(CMAKE_HOST_WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/lib/windows)
else()
    message("unkown platform")
endif()


add_compile_options(-gdwarf-2 -std=c++17 --shared )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_HOST_UNIX)
message("include linux")
    include_directories(${CMAKE_SOURCE_DIR}/lib/linux/include)
elseif(CMAKE_HOST_WIN32)
message("include windows")
    include_directories(${CMAKE_SOURCE_DIR}/lib/windows/include)
else()
    message("unkown platform")
endif()

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