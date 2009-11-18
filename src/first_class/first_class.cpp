
#include "first_class.h"


#include <string>
#include <iostream>


hello::hello(const std::string& country) { this->country = country; }
std::string hello::greet() const { return "Hello from " + country; }

// A function taking a hello object as an argument.
std::string invite(const hello& w) {
    return w.greet() + "! Please come soon!";
}

