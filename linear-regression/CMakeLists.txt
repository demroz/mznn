cmake_minimum_required(VERSION 3.30.8)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(THIS aadlinearregression)
project(${THIS} C CXX)
set(CMAKE_CXX_STANDARD 20)

enable_testing()
include_directories(
 ${CMAKE_CURRENT_SOURCE_DIR}/../aad/include
 ${CMAKE_CURRENT_SOURCE_DIR}/../external/include
 ${CMAKE_CURRENT_SOURCE_DIR}/../logging/
 ${CMAKE_CURRENT_SOURCE_DIR}/../external/eigen/
 ${CMAKE_CURRENT_SOURCE_DIR}/../logging/include/)


link_directories(
${CMAKE_CURRENT_SOURCE_DIR}/../aad/lib/
${CMAKE_SOURCE_DIR}/../external/lib64/
${CMAKE_SOURCE_DIR}/../logging/lib/
)

set(HEADERS
  linearRegression.hpp
)

set(SOURCES
  linearRegression.cpp
	linearRegressionMain.cpp
)

add_executable(${THIS} ${SOURCES} ${HEADERS})
target_link_libraries(${THIS} PUBLIC aad logmanager)
