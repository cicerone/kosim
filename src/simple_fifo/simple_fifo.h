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

class write_if : virtual public sc_interface
{
   public:
     virtual void write(char) = 0;
     virtual void reset() = 0;
};

class read_if : virtual public sc_interface
{
   public:
     virtual void read(char &) = 0;
     virtual int num_available() = 0;
};

class fifo : public sc_channel, public write_if, public read_if
{
   public:
     fifo(sc_module_name name);

     void write(char c); 
     void read(char &c);

     void reset();
     int  num_available();

   private:
     enum e { max = 10 };
     char data[max];
     int num_elements, first;
     sc_event write_event, read_event;
};

class producer : public sc_module
{
   public:
     sc_port<write_if> out;

     SC_HAS_PROCESS(producer);

     producer(sc_module_name name);

     void main();
};

class consumer : public sc_module
{
   public:
     sc_port<read_if> in;

     SC_HAS_PROCESS(consumer);

     consumer(sc_module_name name);

     void main();
};

class top : public sc_module
{
   public:
     fifo *fifo_inst;
     producer *prod_inst;
     consumer *cons_inst;

     top(sc_module_name name);
};

void run_sim();
