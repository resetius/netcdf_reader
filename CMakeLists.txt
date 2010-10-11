cmake_minimum_required(VERSION 2.8.0)
project(netcdf_reader CXX C)

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
find_package(BISON)
find_package(NETCDF)

if (NOT NETCDF_FOUND)
	message(FATAL "netcdf not found!")
endif ()

if (NOT BISON_FOUND)
	message(FATAL "bison not found")
endif()

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")

include_directories(".")
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${NETCDF_INCLUDE_DIR})

set (netcdf_source netcdf_reader.cpp)
bison_target(netcdf_parser netcdf_cmd.ypp ${CMAKE_CURRENT_BINARY_DIR}/netcdf_cmd.cpp)
add_executable(netcdf_reader ${BISON_netcdf_parser_OUTPUTS} ${netcdf_source})
target_link_libraries(netcdf_reader ${NETCDF_LIBRARIES})

