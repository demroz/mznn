cmake_minimum_required(VERSION 3.30.8)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(this tests)
project(${this} C CXX)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

include_directories(../)
include_directories(${CMAKE_SOURCE_DIR}/../external/include/)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/../external/lib64/)

set(SOURCES
  test_csv_parse.cpp
	test_linear_regression.cpp
)

add_executable(${this} ${SOURCES}
 test_linear_regression.cpp)

target_link_libraries(
  ${this} PUBLIC
	gtest
	gtest_main
	aad
	aadlinearregression
)
get_filename_component(CSV_DATA_DIR "${CMAKE_SOURCE_DIR}/../datasets/" ABSOLUTE)
target_compile_definitions(${this} PRIVATE CSV_DATA_PATH="${CSV_DATA_DIR}")
add_test(
  NAME ${this}
	COMMAND ${this}
)
