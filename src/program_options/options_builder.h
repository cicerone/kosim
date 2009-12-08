/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     Support: kosym@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_PO_OPTIONS_BUILDER_H
#define KOSIM_PO_OPTIONS_BUILDER_H

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class OptionsBuilder
{
  public:
      OptionsBuilder();
     ~OptionsBuilder();
     void   SetArgument(const char* p_arg_);
     void   BuildArgv();
     void   InitProgramOptions();
  private:
      vector<string> m_argv; // container of the arguments   
      char** mp_argv;
};



#endif // KOSIM_PO_OPTIONS_BUILDER_H
