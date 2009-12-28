#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                     Support: kosim@kotys.biz 
#==============================================================================================

#Create a shared library called "simple_fifo"
#include dirs
#include_directories (${KOSIM_SOURCE_DIR}/examples/sc/simple_fifo)

# The extension is already found. Any number of sources could be listed here.
add_library (simple_fifo SHARED simple_fifo.cpp first_class.cpp)

# #Example of HOWTO make an executable in one dir
# add_executable (simple_fifo simple_fifo.cpp)
# # Link the executable to the used libraries.
# target_link_libraries (simple_fifo libscv.so libsystemc.a) 

