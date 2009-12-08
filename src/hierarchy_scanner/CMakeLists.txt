#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                     Support: kosym@kotys.biz 
#==============================================================================================

#Create a shared library called "hierarchy_scanner"
#include dirs
include_directories ($KOSIM_SOURCE_DIR}/hierarchy_scanner)

# The extension is already found. Any number of sources could be listed here.
add_library (hierarchy_scanner SHARED hierarchy_scanner.cpp)

