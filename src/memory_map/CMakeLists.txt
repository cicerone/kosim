#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                     
#  Support: kosim@kotys.biz 
#==============================================================================================

#Create a shared library called "memory_map_builder"
#include dirs
include_directories (${KOSIM_SOURCE_DIR}/)

# The extension is already found. Any number of sources could be listed here.
add_library (memory_map_builder SHARED memory_map_builder.cpp memory_map.cpp)

##Example of HOWTO make an executable in one dir
#add_executable (memory_map_builder mmb_main.cpp memory_map_builder.cpp)
## Link the executable to the used libraries.
#target_link_libraries (memory_map_builder libscv.so libsystemc.a) 
 
