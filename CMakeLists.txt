project(  actorlr )
cmake_minimum_required( VERSION 2.8 )
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")
# remove compiler checks if you are using VS2010, it supports
#   1. auto
#   2. lambda
#   3. const iterator
# and, sadly, it doesn't support `for(item, cotainer)'
#  BOOST_ROOT_DIR=/usr/local/Cellar/boost/1.63.0/
include( CheckCXXCompilerFlag )
check_cxx_compiler_flag( "-std=c++11"   COMPILER_SUPPORTS_CXX11 )
check_cxx_compiler_flag( "-std=c++0x"   COMPILER_SUPPORTS_CXX0X )
if( COMPILER_SUPPORTS_CXX11 )
    if( CMAKE_COMPILER_IS_GNUCXX )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11" )
    else()
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
    endif()
elseif( COMPILER_SUPPORTS_CXX0X)
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
else()
    # MSVC, On by default (if available)
endif()
#ADD_SUBDIRECTORY(ext/actor-framework) # Change `ext/curlcpp` to a directory according to your setup
#include("cmake/Modules/FindCAF.cmake")  
find_package(CAF REQUIRED core)
include_directories(${CAF_INCLUDE_DIRS})
MESSAGE( STATUS  "CAF" ${CAF_INCLUDE_DIRS} )

#include("cmake/Modules/FindGlog.cmake")  
#include_directories(${GLOG_INCLUDE_DIRS})

add_executable( ${PROJECT_NAME} main.cpp )

#target_link_libraries(${PROJECT_NAME} curlcpp)
target_link_libraries(${PROJECT_NAME} ${CAF_LIBRARIES})



