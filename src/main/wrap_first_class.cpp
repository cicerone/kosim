#include <boost/python/module.hpp>
#include <boost/python/def.hpp>

#include "first_class.h"

#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(kosim)
{
    class_<World>("World", init<std::string>())
        .def("greet", &World::greet)
        .def("set", &World::set)
    ;
}


