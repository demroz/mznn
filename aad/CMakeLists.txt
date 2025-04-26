cmake_minimum_required(VERSION 3.30.8)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(THIS aad)
project(${THIS} C CXX)
enable_testing()

include_directories(include)
include_directories(../external/include/)
include_directories(../logging/)

message(${CMAKE_SOURCE_DIR})

link_directories(${CMAKE_SOURCE_DIR}/../external/lib64/)
link_directories(${CMAKE_SOURCE_DIR}/../logging/lib/)

set(HEADERS
  ${CMAKE_SOURCE_DIR}/include/globals.hpp
  ${CMAKE_SOURCE_DIR}/include/mempool.hpp
)

set(SOURCES
  ${CMAKE_SOURCE_DIR}/source/globals.cpp
  ${CMAKE_SOURCE_DIR}/source/mempool.cpp
  ${CMAKE_SOURCE_DIR}/source/addutils.cpp
)

add_library(${THIS} STATIC ${SOURCES} ${HEADERS})
target_link_libraries(${THIS} PUBLIC logmanager)

add_subdirectory(tests)

# add_test(MEMPOOL_TEST, "${CMAKE_BUILD_RPATH}/test/tests")
