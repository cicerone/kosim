#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                     Support: kosim@kotys.biz 
#==============================================================================================

#Create a shared library called "simple_bus_types"
#include dirs
#include_directories (${KOSIM_SOURCE_DIR}/examples/sc/simple_bus)
include_directories (/home/roni/verilator/include)

# The extension is already found. Any number of sources could be listed here.
add_library (Vi2c_master_top SHARED Vi2c_master_top.cpp
Vi2c_master_top__Syms.cpp /home/roni/verilator/include/verilated.cpp)



