/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     Support: kosym@kotys.biz 
===============================================================================================*/
#include "first_class.h"


#include <string>
#include <iostream>


hello::hello(const std::string& country) { this->country = country; }
std::string hello::greet() const { return "Hello from " + country; }

// A function taking a hello object as an argument.
std::string invite(const hello& w) {
    return w.greet() + "! Please come soon!";
}

