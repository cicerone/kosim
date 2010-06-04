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
    std::string& get_test_name                       () { return m_test_name      ; }
    uint32_t     get_transfer_size                   () { return m_transfer_size  ; }
    uint32_t     get_memory_size                     () { return m_memory_size    ; }
    uint32_t     get_nr_ops_per_xfer                 () { return m_nr_ops_per_xfer; }
    uint32_t     get_nr_xfers                        () { return m_nr_xfers       ; }

    int32_t      get_mem_lowest_value               () { return m_mem_lowest_value ; }
    int32_t      get_mem_highest_value              () { return m_mem_highest_value; }

///////////  END OPTIONS from configuration file  ////////////////////////////////////
    int32_t     get_cmd_line_arg1                    () { return m_cmd_line_arg1     ;}                ;

    int  Dump();

    ~ProgramOptions();
private:
    static ProgramOptions* mp_instance;
    void InitConfiguration();

    ProgramOptions(int ac_, char* p_av_[]);
    int         m_dbg_level                       ; // debug level
///////////  OPTIONS from configuraton file  ////////////////////////////////////
    std::string m_test_name                ;
    uint32_t     m_transfer_size ;
    uint32_t     m_memory_size   ;
    uint32_t     m_nr_ops_per_xfer ;
    uint32_t     m_nr_xfers      ;
    int32_t      m_mem_lowest_value ; 
    int32_t      m_mem_highest_value; 
///////////  END OPTIONS from configuration file  ////////////////////////////////////
///////////  OPTIONS from command line  ////////////////////////////////////
    int32_t      m_cmd_line_arg1                   ;
///////////  END OPTIONS from command line  ////////////////////////////////////

};

#endif // KOSIM_PO_PROGRAM_OPTIONS_H
