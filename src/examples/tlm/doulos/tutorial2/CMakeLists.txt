#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                     Support: kosim@kotys.biz 
#==============================================================================================

#Create a shared library called "doulos_tutorial2" 
#include dirs
#include_directories (${KOSIM_SOURCE_DIR}/examples/)

# The extension is already found. Any number of sources could be listed here.
add_library (doulos_tutorial2 SHARED tlm2_getting_started_2.cpp)


