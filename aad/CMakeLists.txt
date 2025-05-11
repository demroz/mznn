cmake_minimum_required(VERSION 3.30.8)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

set(THIS aad)
project(${THIS} C CXX)
set(CMAKE_CXX_STANDARD 20)

enable_testing()

include_directories(include)
include_directories(../external/include/)
include_directories(../logging/)
include_directories(../external/eigen/)

message(${CMAKE_SOURCE_DIR})

link_directories(${CMAKE_SOURCE_DIR}/../external/lib64/)
link_directories(${CMAKE_SOURCE_DIR}/../logging/lib/)

set(HEADERS
  ${CMAKE_SOURCE_DIR}/include/globals.hpp
  ${CMAKE_SOURCE_DIR}/include/mempool.hpp
  ${CMAKE_SOURCE_DIR}/include/node.hpp
	${CMAKE_SOURCE_DIR}/include/scalar.hpp
	${CMAKE_SOURCE_DIR}/include/ops/op_declarations.hpp
	${CMAKE_SOURCE_DIR}/include/ops/op_definitions.hpp
	${CMAKE_SOURCE_DIR}/include/ops/op_declarations/BinaryArithmeticOpDeclarations.hpp
	${CMAKE_SOURCE_DIR}/include/ops/op_definitions/BinaryArithmeticOverloads.hpp
	${CMAKE_SOURCE_DIR}/include/ops/op_definitions/UnaryOperatorOverloads.hpp
)

set(SOURCES
  ${CMAKE_SOURCE_DIR}/source/addutils.cpp
  ${CMAKE_SOURCE_DIR}/source/autodiff.cpp
)

add_library(${THIS} STATIC ${SOURCES} ${HEADERS}
 include/ops/op_declarations/OpsRequiredByEigenDeclarations.hpp
 include/ops/op_definitions/OpsRequiredByEigenOverloads.hpp
 include/EigenSupport.hpp)
target_link_libraries(${THIS} PUBLIC logmanager)

add_subdirectory(tests)

# add_test(MEMPOOL_TEST, "${CMAKE_BUILD_RPATH}/test/tests")
