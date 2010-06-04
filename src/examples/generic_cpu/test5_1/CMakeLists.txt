#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                     
#  Support: kosim@kotys.biz 
#==============================================================================================

#Create a shared library called "sim_accel_test1"
#include dirs
include_directories (${KOSIM_SOURCE_DIR}/)
include_directories (${KOSIM_SOURCE_DIR}/memory_map/)
include_directories (${KOSIM_SOURCE_DIR}/main/generic_cpu/test5_1)
include_directories (${KOSIM_SOURCE_DIR}/generic_cpu/)

# The extension is already found. Any number of sources could be listed here.
add_library (generic_cpu_test5_1 SHARED generic_cpu.cpp gc_test_target.cpp gc_main.cpp gen_from_sysrdl.cpp)

##Example of HOWTO make an executable in one dir
#add_executable (generic_cpu gc_main.cpp gc_memory.cpp generic_cpu.cpp)
## Link the executable to the used libraries.
#target_link_libraries (generic_cpu program_options memory_map libscv.so libsystemc.a) 
 
