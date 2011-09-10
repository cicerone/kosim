
#ifndef __Vi2c_master_test_h
#define __Vi2c_master_test_h

#include <systemc.h>

//#include "simple_bus_master_blocking.h"

SC_MODULE(Vi2c_master_test)
{
  // channels
  sc_clock C1;

  // module instances
  //simple_bus_master_blocking     *master_b;

  // constructor
  SC_CTOR(Vi2c_master_test)
    : C1("C1")
  {
      std::cout << "Hello Verilator!" << std::endl;
    // create instances
    //master_b = new simple_bus_master_blocking("master_b", 4, 0x4c, false, 300);

    // connect instances
    //master_d->clock(C1);
  }

  // destructor
  ~Vi2c_master_test()
  {
    //if (arbiter) {delete arbiter; arbiter = 0;}
  }

}; // end class simple_bus_test

//void run_sim();

/////////////////////////////////////////////////////////////////////////////////////////////////
// Entry point if the program is loaded as a module to python  
// IN: 
// OUT: 
// RET: 
void run_sim()
{
    cout << "=======================================================" << endl;
   // cout << ProgramOptions::GetInstance()->get_test_name() << endl;
    cout << "=======================================================" << endl;


//    Top top("top");
    Vi2c_master_test i2c_master("i2c_master");
    sc_start(100, SC_NS);
    sc_stop();
}



#endif
