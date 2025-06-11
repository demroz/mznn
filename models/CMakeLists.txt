cmake_minimum_required(VERSION 3.30.8)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(THIS aadlinearregression)
project(${THIS} C CXX)
set(CMAKE_CXX_STANDARD 20)

enable_testing()
include_directories(
 ${CMAKE_CURRENT_SOURCE_DIR}/
 ${CMAKE_CURRENT_SOURCE_DIR}/../aad/include
 ${CMAKE_CURRENT_SOURCE_DIR}/../external/include
 ${CMAKE_CURRENT_SOURCE_DIR}/../logging/
 ${CMAKE_CURRENT_SOURCE_DIR}/../external/eigen/
 ${CMAKE_CURRENT_SOURCE_DIR}/../external/boost_1_88_0/
 ${CMAKE_CURRENT_SOURCE_DIR}/../logging/include
 ${CMAKE_CURRENT_SOURCE_DIR}/../optimizers/
 ${CMAKE_CURRENT_SOURCE_DIR}/../utilities/
 )


link_directories(
${CMAKE_CURRENT_SOURCE_DIR}/../aad/lib/
${CMAKE_SOURCE_DIR}/../external/lib64/
${CMAKE_SOURCE_DIR}/../logging/lib/
)

set(HEADERS
  LinearRegression.hpp
	ModelConfig.hpp
)

set(SOURCES
  sources/LinearRegression.cpp
	sources/ModelUtilityFunctions.cpp
)

add_library(${THIS} STATIC ${SOURCES} ${HEADERS})

target_link_libraries(${THIS} PUBLIC aad logmanager)
install(TARGETS ${THIS} DESTINATION ${CMAKE_SOURCE_DIR}/lib/)

add_subdirectory(tests)
