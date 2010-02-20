#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                     
#  Support: kosim@kotys.biz 
#==============================================================================================

#Create a shared library called "memory_map_builder"
#include dirs
include_directories (${KOSIM_SOURCE_DIR}/)
include_directories (${KOSIM_SOURCE_DIR}/logging/)


##Example of HOWTO make an executable in one dir
add_executable (test_log  main.cpp)
## Link the executable to the used libraries.
target_link_libraries (test_log logging libboost_log.so libboost_date_time.so libboost_regex.so libboost_filesystem.so libboost_system.so libboost_thread.so)
 
