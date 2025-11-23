cmake_minimum_required(VERSION 3.28)

project(BFInterpreter)

option(USE_NATIVE_INSTRUCTIONS "Optimize for host CPU, at the cost of portability !!!" OFF)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

file(GLOB_RECURSE SOURCES src/**.cpp)
file(GLOB_RECURSE HEADERS include/**.hpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

if(USE_NATIVE_INSTRUCTIONS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()
