#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                     Support: kosim@kotys.biz 
#==============================================================================================

include_directories (${KOSIM_SOURCE_DIR}/verilator/i2c_opencores)
include_directories (${KOSIM_SOURCE_DIR}/hierarchy_scanner)
include_directories (${KOSIM_SOURCE_DIR}/program_options)
include_directories ($ENV{PYTHON_INCLUDE}/)

#some debugging messages
#MESSAGE( "Your Unix home directory is $ENV{HOME}." )

#SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_RELEASE        "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_DEBUG          "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")

# Make sure the linker can find the library once it is built.
#link_directories (/usr/local/lib/)
link_directories (${KOSIM_SOURCE_DIR}/verilator/i2c_opencores)
link_directories (/home/roni/verilator/test_c/obj_dir)

# Add shared library called "kosim" that is built from the source files
add_library (kosim_i2c_opencores SHARED wrap_i2c_opencores.cpp)

# Link the executable to the used libraries.
target_link_libraries (kosim_i2c_opencores libVi2c_master_top.so hierarchy_scanner libboost_python.so libscv.so libsystemc.a)

