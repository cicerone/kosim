#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                     
#  Support: kosim@kotys.biz 
#==============================================================================================

#Create a shared library called "program_options" which includes the source file "program_options.cpp".
#include dirs
include_directories ($KOSIM_SOURCE_DIR}/program_options)
include_directories ($KOSIM_SOURCE_DIR}/program_options)

# The extension is already found. Any number of sources could be listed here.
add_library (program_options SHARED options_builder.cpp program_options_base.cpp)


