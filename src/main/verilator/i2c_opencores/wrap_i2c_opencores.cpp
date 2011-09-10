/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp> 

#include "systemc.h"
 
#include "hierarchy_scanner.h"
#include "options_builder.h"

#include "Vi2c_master_test.h"

using namespace boost::python;

BOOST_PYTHON_MODULE(libkosim_i2c_opencores)
{
    def("run_sim", run_sim); // entry point in SystemC program                           

    def("print_hierarchy", ko_sc::print_hierarchy);
    def("print_ports", ko_sc::print_ports);
    def("print_modules", ko_sc::print_modules);
    def("print_threads", ko_sc::print_threads);
    def("parse_args", ko_sc::parse_args);
}


