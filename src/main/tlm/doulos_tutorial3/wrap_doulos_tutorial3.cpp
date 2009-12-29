//  Copyright Joel de Guzman 2002-2004. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//  Hello World Example from the tutorial
//  [Joel de Guzman 10/9/2002]

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp> 

#include "systemc.h"
 
#include "hierarchy_scanner.h"
#include "options_builder.h"

#include "tlm2_getting_started_3.h"


using namespace boost::python;

BOOST_PYTHON_MODULE(libkosim_doulos_tutorial3)
{

    def("run_sim", run_sim); // entru point in SystemC program                           

    def("print_hierarchy", ko_sc::print_hierarchy);
    def("print_ports", ko_sc::print_ports);
    def("print_modules", ko_sc::print_modules);
    def("print_threads", ko_sc::print_threads);
    def("parse_args", ko_sc::parse_args);

}


