#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                
#  Support: kosim@kotys.biz 
#==============================================================================================

# The name of our project is "VSM". CMakeLists files in this project can
# refer to the root source directory of the project as ${KOSIM_SOURCE_DIR} and
# to the root binary directory of the project as ${VSM_BINARY_DIR}.
cmake_minimum_required (VERSION 2.6)
project (KOSIM)

#SET(CMAKE_BUILD_TYPE RelWithDebInfo)
#SET(CMAKE_BUILD_TYPE Release)
SET(CMAKE_BUILD_TYPE Debug)

SET(CMAKE_CXX_FLAGS_DEBUG          "-D SC_INCLUDE_DYNAMIC_PROCESSES")
#SET(CMAKE_CXX_FLAGS_RELEASE        "-D SC_INCLUDE_DYNAMIC_PROCESSES")
#SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-D SC_INCLUDE_DYNAMIC_PROCESSES")


#SET(CMAKE_CXX_FLAGS_DEBUG          "-fpermissive")

#SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_RELEASE        "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_DEBUG          "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_DEBUG          "-pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_DEBUG          "-Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")

include_directories   ($ENV{BOOST_INCLUDE}/)
link_directories      ($ENV{BOOST_LIB}/)

#SystemC libs
link_directories    ($ENV{SYSTEMC_LIB}/)
link_directories    ($ENV{SCV_LIB}/)

include_directories ($ENV{SYSTEMC_INCLUDE}/)
include_directories ($ENV{SCV_INCLUDE}/)
include_directories ($ENV{TLM_INCLUDE}/)


# Recurse into the subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.

add_subdirectory (hierarchy_scanner)
#add_subdirectory (memory_map)

add_subdirectory (verilator/i2c_opencores)
add_subdirectory (main/verilator/i2c_opencores)

#add_subdirectory (program_options) NOTE: this dir must never be added, the needed files are symbolically linked where needed

# tests to run 
# execute "make test" to run the following tests
enable_testing()

add_test(test_simple_fifo       python main/sc/simple_fifo/simple_fifo.py     )
add_test(test_simple_bus        python main/sc/simple_bus/simple_bus.py       )
#pythagoras test takes too long. Uncomment if you want to run the test.
#add_test(test_pythagoras       python main/scv/pythagoras/pythagoras.py      )
add_test(test_doulos_tutorial1  python main/tlm/doulos_tutorial1/doulos_tutorial1.py)
add_test(test_doulos_tutorial2  python main/tlm/doulos_tutorial2/doulos_tutorial2.py)
add_test(test_doulos_tutorial3  python main/tlm/doulos_tutorial3/doulos_tutorial3.py)
add_test(test_doulos_tutorial4  python main/tlm/doulos_tutorial4/doulos_tutorial4.py)
add_test(test_doulos_tutorial5  python main/tlm/doulos_tutorial5/doulos_tutorial5.py)
add_test(test_doulos_tutorial6  python main/tlm/doulos_tutorial6/doulos_tutorial6.py)
add_test(test_doulos_tutorial7  python main/tlm/doulos_tutorial7/doulos_tutorial7.py)
add_test(test_generic_cpu_test1 python main/generic_cpu/test1/generic_cpu.py        )
add_test(test_generic_cpu_test2 python main/generic_cpu/test2/generic_cpu.py        )

#pythagoras test takes too long. Uncomment if you want to run the test.
#set_tests_properties(test_simple_fifo test_simple_bus test_pythagoras test_doulos_tutorial1 test_doulos_tutorial2 test_doulos_tutorial3 test_doulos_tutorial4 test_doulos_tutorial5 test_doulos_tutorial6 test_doulos_tutorial7 PROPERTIES PASS_REGULAR_EXPRESSION "PASSED")
#set_tests_properties(test_simple_fifo test_simple_bus test_pythagoras test_doulos_tutorial1 test_doulos_tutorial2 test_doulos_tutorial3 test_doulos_tutorial4 test_doulos_tutorial5 test_doulos_tutorial6 test_doulos_tutorial7 PROPERTIES FAIL_REGULAR_EXPRESSION "ERROR")

set_tests_properties(test_simple_fifo test_simple_bus test_doulos_tutorial1 test_doulos_tutorial2 test_doulos_tutorial3 test_doulos_tutorial4 test_doulos_tutorial5 test_doulos_tutorial6 test_doulos_tutorial7 PROPERTIES PASS_REGULAR_EXPRESSION "PASSED")
set_tests_properties(test_simple_fifo test_simple_bus test_doulos_tutorial1 test_doulos_tutorial2 test_doulos_tutorial3 test_doulos_tutorial4 test_doulos_tutorial5 test_doulos_tutorial6 test_doulos_tutorial7 PROPERTIES FAIL_REGULAR_EXPRESSION "ERROR")
