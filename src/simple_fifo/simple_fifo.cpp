/*****************************************************************************

  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2006 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 2.4 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************

  simple_fifo.cpp -- Simple SystemC 2.0 producer/consumer example.

                     From "An Introduction to System Level Modeling in
                     SystemC 2.0". By Stuart Swan, Cadence Design Systems.
                     Available at www.systemc.org

  Original Author: Stuart Swan, Cadence Design Systems, 2001-06-18

 *****************************************************************************/

/*****************************************************************************

  MODIFICATION LOG - modifiers, enter your name, affiliation, date and
  changes you are making here.

      Name, Affiliation, Date:
  Description of Modification:

 *****************************************************************************/


#include <systemc.h>
#include "simple_fifo.h"



//////////////////////////////////////////////////////////////
fifo::fifo(sc_module_name name) : 
    sc_channel(name), 
    num_elements(0), 
    first(0) 
{
}

//////////////////////////////////////////////////////////////
void fifo::write(char c) 
{
  if (num_elements == max)
    wait(read_event);

  data[(first + num_elements) % max] = c;
  ++ num_elements;
  write_event.notify();
}

//////////////////////////////////////////////////////////////
void fifo::read(char &c)
{
  if (num_elements == 0)
    wait(write_event);

  c = data[first];
  -- num_elements;
  first = (first + 1) % max;
  read_event.notify();
}

//////////////////////////////////////////////////////////////
void fifo::reset() 
{ 
    num_elements = first = 0; 
}

int fifo::num_available() 
{ 
    return num_elements;
}

//////////////////////////////////////////////////////////////
producer::producer(sc_module_name name) : sc_module(name)
{
  SC_THREAD(main);
}

//////////////////////////////////////////////////////////////
void producer::main()
{
  const char *str =
    "Visit www.systemc.org and see what SystemC can do for you today!\n";

  while (*str)
    out->write(*str++);
}


//////////////////////////////////////////////////////////////
consumer::consumer(sc_module_name name) : sc_module(name)
{
  SC_THREAD(main);
}

//////////////////////////////////////////////////////////////
void consumer::main()
{
  char c;
  cout << endl << endl;

  while (true) {
    in->read(c);
    cout << c << flush;

    if (in->num_available() == 1)
      cout << "<1>" << flush;
    if (in->num_available() == 9)
      cout << "<9>" << flush;
  }
}

//////////////////////////////////////////////////////////////
top::top(sc_module_name name) : sc_module(name)
{
  fifo_inst = new fifo("Fifo1");

  prod_inst = new producer("Producer1");
  prod_inst->out(*fifo_inst);

  cons_inst = new consumer("Consumer1");
  cons_inst->in(*fifo_inst);
}

//////////////////////////////////////////////////////////////
int sc_main (int argc , char *argv[]) {
   top top1("Top1");
   sc_start();
   return 0;
}

void run_sim()
{
   top top1("Top1");
   sc_start();
}
