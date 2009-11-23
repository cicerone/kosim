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

    def("run_sim", run_sim); //

}


