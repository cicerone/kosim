#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                     Support: kosim@kotys.biz 
#==============================================================================================

include_directories ($ENV{BOOST_ROOT}/include)
include_directories ($ENV{BOOST_ROOT}/boost/thread)
include_directories (${KOSIM_SOURCE_DIR}/generic_cpu)
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
link_directories (/usr/lib/)

#some debugging messages
#MESSAGE( "Your program_options lib is in: $ENV{BOOST_ROOT}/bin.v2/libs/program_options/build/gcc-4.1.2/release/link-static/threading-multi.")

# Add shared library called "kosim" that is built from the source files
#add_library (kosim_generic_cpu SHARED wrap_generic_cpu.cpp program_options.cpp program_options_base.cpp options_builder.cpp)
# Link the executable to the used libraries.
#target_link_libraries (kosim_generic_cpu generic_cpu hierarchy_scanner memory_map libboost_program_options.so libboost_python.so libscv.so libsystemc.a)


#Generate executable
add_executable (kosim_generic_cpu  program_options.cpp program_options_base.cpp options_builder.cpp)
# Link the executable to the used libraries.
target_link_libraries (kosim_generic_cpu generic_cpu hierarchy_scanner memory_map libboost_program_options.so libscv.so libsystemc.a)
