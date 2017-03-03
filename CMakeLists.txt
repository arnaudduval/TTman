cmake_minimum_required(VERSION 3.0)

project(TTman CXX)

# Use of decent C++ version
macro(use_cxx14)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "--std=c++14 ${CMAKE_CXX_FLAGS}")
    endif()
  else()
    set (CMAKE_CXX_STANDARD 14)
  endif()
endmacro(use_cxx14)

# Use pkg-config
find_package(PkgConfig REQUIRED)

# Configure libxml++ 2.6
pkg_check_modules(LibXML++ libxml++-2.6 REQUIRED)


include_directories(${LibXML++_INCLUDE_DIRS})
link_directories(${LibXML++_LIBRARIES})



use_cxx14()
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

include_directories(include)
file(GLOB_RECURSE source_files src/*)

add_executable(circuit ${source_files} )
target_link_libraries(circuit ${LibXML++_LIBRARIES})

