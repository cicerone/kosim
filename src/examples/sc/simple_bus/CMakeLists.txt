#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                     Support: kosim@kotys.biz 
#==============================================================================================

#Create a shared library called "simple_bus_types"
#include dirs
#include_directories (${KOSIM_SOURCE_DIR}/examples/sc/simple_bus)

# The extension is already found. Any number of sources could be listed here.
add_library (simple_bus SHARED simple_bus_arbiter.cpp simple_bus.cpp simple_bus_main.cpp simple_bus_master_blocking.cpp simple_bus_master_direct.cpp simple_bus_master_non_blocking.cpp simple_bus_tools.cpp simple_bus_types.cpp)



