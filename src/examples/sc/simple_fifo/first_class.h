#include <string>
#include <iostream>


 class hello
  {
    public:
      hello(const std::string& country);
      std::string greet() const;
    private:
      std::string country;
  };

  // A function taking a hello object as an argument.
  std::string invite(const hello& w);


