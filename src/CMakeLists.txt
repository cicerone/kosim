#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                
#  Support: kosim@kotys.biz 
#==============================================================================================

# The name of our project is "VSM". CMakeLists files in this project can
# refer to the root source directory of the project as ${KOSIM_SOURCE_DIR} and
# to the root binary directory of the project as ${VSM_BINARY_DIR}.
cmake_minimum_required (VERSION 2.6)
project (KOSIM)

#SET(CMAKE_BUILD_TYPE RelWithDebInfo)
#SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_BUILD_TYPE Debug)

#SET(CMAKE_CXX_FLAGS_DEBUG          "-fpermissive")

#SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_RELEASE        "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_DEBUG          "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_DEBUG          "-pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_DEBUG          "-Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")

# search for Boost version 1.37
find_package( Boost 1.37 COMPONENTS program_options)

link_directories      ( ${Boost_LIBRARY_DIRS} )
include_directories   ( ${Boost_INCLUDE_DIRS} )
target_link_libraries ( ${Boost_LIBRARIES})


#SystemC libs
link_directories    ($ENV{SYSTEMC_LIB}/)
link_directories    ($ENV{SCV_LIB}/)

include_directories ($ENV{SYSTEMC_INCLUDE}/)
include_directories ($ENV{SCV_INCLUDE}/)
include_directories ($ENV{TLM_INCLUDE}/)


# Recurse into the subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.

add_subdirectory (main/generic_cpu)
add_subdirectory (examples/generic_cpu/test1)
add_subdirectory (hierarchy_scanner)
#add_subdirectory (program_options)
add_subdirectory (generic_cpu)
add_subdirectory (memory_map)

# tests to run 
# execute "make test" to run the following tests
enable_testing()

add_test(test_generic_cpu      python main/generic_cpu/generic_cpu.py        )


