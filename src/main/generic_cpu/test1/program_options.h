/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_PO_PROGRAM_OPTIONS_H
#define KOSIM_PO_PROGRAM_OPTIONS_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdint.h>

#include "program_options_base.h"


class ProgramOptions : public ProgramOptionsBase
{
public:
    static ProgramOptions* GetInstance(int ac_, char* p_av_[]); // NOTE: must be called first time
    static ProgramOptions* GetInstance();                       // NOTE: can be called any time after 
    int    get_dbg_level() { return m_dbg_level              ;}
///////////  OPTIONS from configuraton file  ////////////////////////////////////
    std::string& get_test_name                       () { return m_test_name           ; }
    int32_t      get_addr_width_int_resources        () { return m_addr_width_int_resources; }
    int32_t      get_mem0_lowest_value               () { return m_mem0_lowest_value ; }
    int32_t      get_mem0_highest_value              () { return m_mem0_highest_value; }

///////////  END OPTIONS from configuration file  ////////////////////////////////////
    int  Dump();

    ~ProgramOptions();
private:
    static ProgramOptions* mp_instance;
    void InitConfiguration();

    ProgramOptions(int ac_, char* p_av_[]);
    int         m_dbg_level                       ; // debug level
///////////  OPTIONS from configuraton file  ////////////////////////////////////
    std::string m_test_name                ;
    int32_t     m_addr_width_int_resources ;
    int32_t     m_mem0_lowest_value ; 
    int32_t     m_mem0_highest_value; 
///////////  END OPTIONS from configuration file  ////////////////////////////////////
///////////  OPTIONS from command line  ////////////////////////////////////
    int32_t     m_cmd_line_arg1                   ;
///////////  END OPTIONS from command line  ////////////////////////////////////

};

#endif // KOSIM_PO_PROGRAM_OPTIONS_H
