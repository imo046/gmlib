#
# Try to find ViennaCL library and include path.
# Once done this will define
#
# VIENNACL_FOUND
# VIENNACL_INCLUDE_DIRS
# VIENNACL_LIBRARIES
# 


IF (WIN32)
  find_package(OpenCL REQUIRED)
  
  set(VIENNACL_PATH_WIN32 $ENV{PROGRAMFILES}/ViennaCL CACHE PATH "ViennaCL root directory.")

  find_path(VIENNACL_INCLUDE_DIR viennacl/forwards.h
    PATHS ${VIENNACL_PATH_WIN32}/include
	DOC "The ViennaCL include path")
  
  if(VIENNACL_INCLUDE_DIR)
    mark_as_advanced(FORCE VIENNACL_PATH_WIN32)
  else(VIENNACL_INCLUDE_DIR)
    mark_as_advanced(CLEAR VIENNACL_PATH_WIN32)
  endif(VIENNACL_INCLUDE_DIR)

ELSEIF(APPLE)
#TODO
ELSE (WIN32) #Linux
#TODO
ENDIF (WIN32)

set(VIENNACL_INCLUDE_DIRS ${VIENNACL_INCLUDE_DIR} ${OPENCL_INCLUDE_DIRS})
set(VIENNACL_LIBRARIES ${OPENCL_LIBRARIES})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ViennaCL "ViennaCL not found!" VIENNACL_INCLUDE_DIR OPENCL_INCLUDE_DIRS OPENCL_LIBRARIES)

MARK_AS_ADVANCED( VIENNACL_INCLUDE_DIR )
