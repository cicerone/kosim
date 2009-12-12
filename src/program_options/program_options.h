/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosym@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_PO_PROGRAM_OPTIONS_H
#define KOSIM_PO_PROGRAM_OPTIONS_H

#include <string>
#include <iostream>
#include <fstream>
#include <stdint.h>

#include <boost/utility.hpp>
#include <boost/program_options.hpp>

namespace po = boost::program_options;


class ProgramOptions : boost::noncopyable
{
public:
    static ProgramOptions* GetInstance(int ac_, char* p_av_[]); // NOTE: must be called first time
    static ProgramOptions* GetInstance();                       // NOTE: can be called any time after 
    int    get_dbg_level() { return m_dbg_level              ;}
///////////  OPTIONS from configuraton file  ////////////////////////////////////
    std::string& get_driver_type                  () { return m_driver_type         ; }
    int32_t      get_sleep_time_per_frame         () { return m_sleep_time_per_frame; }
    int32_t      get_sm_high_speed_time_lowest_value () { return m_sm_high_speed_time_lowest_value ; }
    int32_t      get_sm_high_speed_time_highest_value() { return m_sm_high_speed_time_highest_value; }

///////////  END OPTIONS from configuration file  ////////////////////////////////////
    void Help();
    int  Dump();

    ~ProgramOptions();
private:
    void InitConfiguration(int ac_, char* p_av_[]);
    static ProgramOptions* mp_instance;
    static int             m_argc     ;
    static char**          mp_argv    ;

    ProgramOptions(int ac_, char* p_av_[]);
    int         m_dbg_level                       ; // debug level
///////////  OPTIONS from configuraton file  ////////////////////////////////////
    std::string m_driver_type                     ;
    int32_t     m_sleep_time_per_frame            ;
    int32_t     m_sm_high_speed_time_lowest_value ; 
    int32_t     m_sm_high_speed_time_highest_value; 
///////////  END OPTIONS from configuration file  ////////////////////////////////////
///////////  OPTIONS from command line  ////////////////////////////////////
    int32_t     m_cmd_line_arg1                   ;
///////////  END OPTIONS from command line  ////////////////////////////////////

    std::string m_config_file;    // configuration pattern file

    po::options_description* mp_generic_options    ;
    po::options_description* mp_config_options     ;
    po::options_description* mp_hidden_options     ;
    po::options_description* mp_cmdline_options    ;
    po::options_description* mp_config_file_options;
    po::options_description* mp_visible_options    ;
    po::variables_map*       mp_variable_map       ;
    po::positional_options_description* mp_positional_options;
};

#endif // KOSIM_PO_PROGRAM_OPTIONS_H
