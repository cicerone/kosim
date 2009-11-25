
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
