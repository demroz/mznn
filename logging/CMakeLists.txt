cmake_minimum_required(VERSION 3.30.8)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
set(THIS logmanager)

include_directories(../external/include/)
link_directories(../external/lib64)

set(HEADRS
  LogManager.hpp
  log.hpp
)

set(SOURCES
  LogManager.cpp
)

set(PUBLIC_HEADER log.hpp)
add_library(${THIS} STATIC ${SOURCES} ${HEADERS})
install(FILES
   ${PUBLIC_HEADER}
   DESTINATION ${CMAKE_SOURCE_DIR}/include/
)
install(TARGETS ${THIS}
  DESTINATION ${CMAKE_SOURCE_DIR}/lib/
)
