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
link_directories    (/usr/local/systemc-2.2.0/lib-linux)
link_directories    (/usr/local/scv-1.0p2-sysc2.2/lib-linux)
include_directories (/usr/local/systemc-2.2.0/include)
include_directories (/usr/local/scv-1.0p2-sysc2.2/include)
include_directories (/usr/local/TLM-2009-07-15/include/tlm)


# Recurse into the subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.

add_subdirectory (main/sc_simple_fifo)
add_subdirectory (main/sc_simple_bus)
add_subdirectory (main/scv_pythagoras)
add_subdirectory (main/tlm_blocking_transport)
add_subdirectory (first_class)
add_subdirectory (examples/sc/simple_fifo)
add_subdirectory (examples/sc/simple_bus)
add_subdirectory (examples/scv/pythagoras)
add_subdirectory (examples/tlm/doulos/tutorial1)
add_subdirectory (hierarchy_scanner)
add_subdirectory (program_options)

