
find_path(NETCDF_INCLUDE_DIR netcdf.hh 
	/usr/include/netcdf-3 
	/usr/include/netcdf-4 
	/usr/include/netcdf
	/usr/local/include 
	/usr/include)

find_library(NETCDF_LIB1 NAMES netcdf_c++ HINTS 
	/usr/lib 
	/usr/lib64
	/usr/local/lib
	/usr/local/lib64
)
find_library(NETCDF_LIB2 NAMES netcdf HINTS 
	/usr/lib 
	/usr/lib64
	/usr/local/lib
	/usr/local/lib64
)
set(NETCDF_LIBRARIES ${NETCDF_LIB1};${NETCDF_LIB2})
if (NETCDF_INCLUDE_DIR AND NETCDF_LIBRARIES)
set (NETCDF_FOUND 1)
message(STATUS "netcdf: ${NETCDF_LIBRARIES}")
endif (NETCDF_INCLUDE_DIR AND NETCDF_LIBRARIES)

