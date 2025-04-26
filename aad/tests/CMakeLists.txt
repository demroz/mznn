cmake_minimum_required(VERSION 3.30.8)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(this tests)
project(${this} C CXX)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

include_directories(../include/)
include_directories(${CMAKE_SOURCE_DIR}/../external/include/)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../external/lib64/)


set(SOURCES
  test_MemPool.cpp
  test_Tape.cpp
)

add_executable(${this} ${SOURCES})

target_link_libraries(
  ${this} PUBLIC
  gtest
  gtest_main
  aad
)

add_test(
  NAME ${this}
  COMMAND ${this}
)
