#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                     Support: kosim@kotys.biz 
#==============================================================================================

#some debugging messages
#MESSAGE( "Your Unix home directory is $ENV{HOME}." )

#Generate executable
add_executable (kosim_sm_scoped_lock_2 main.cpp)
# Link the executable to the used libraries.
target_link_libraries (kosim_sm_scoped_lock_2 libboost_date_time.so  )

