//  Copyright Joel de Guzman 2002-2004. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//  Hello World Example from the tutorial
//  [Joel de Guzman 10/9/2002]

#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/class.hpp> 

#include "systemc.h"
 
#include "hello.h"
#include "first_class.h"
#include "simple_fifo.h"
#include "hierarchy_scanner.h"
#include "options_builder.h"


using namespace boost::python;

BOOST_PYTHON_MODULE(kosim)
{
    def("greet", greet);


    // Create the Python type object for our extension class and define __init__ function.
    class_<hello>("hello", init<std::string>())
         .def("greet", &hello::greet)  // Add a regular member function.
         .def("invite", invite)  // Add invite() as a regular function to the module.
    ;
    
    def("invite", invite); // Even better, invite() can also be made a member of module!!!

    def("sc_main", sc_main); // entru point in SystemC program                           

    def("init_sim", init_sim); //
    def("print_hierarchy", ko_sc::print_hierarchy);
    def("print_ports", ko_sc::print_ports);
    def("print_modules", ko_sc::print_modules);
    def("print_threads", ko_sc::print_threads);
    def("parse_args", ko_sc::parse_args);
    def("start_sim", start_sim);

    class_<OptionsBuilder>("OptionsBuilder", init<>())
         .def("SetArgument", &OptionsBuilder::SetArgument) 
         .def("BuildArgv", &OptionsBuilder::BuildArgv) 
         .def("InitProgramOptions", &OptionsBuilder::InitProgramOptions) 
    ;
}


