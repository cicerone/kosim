/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "program_options_base.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
ProgramOptionsBase::ProgramOptionsBase() : 
   mp_generic_options    (0),
   mp_config_options     (0),
   mp_hidden_options     (0), 
   mp_cmdline_options    (0),
   mp_config_file_options(0),
   mp_visible_options    (0),
   mp_variable_map       (0),
   mp_positional_options (0),
   m_config_file         ("NOT_INITIALIZED!")

{
   mp_generic_options     = new po::options_description("Generic options");
   mp_config_options      = new po::options_description("Configuration");
   mp_hidden_options      = new po::options_description("Hidden options");
   mp_cmdline_options     = new po::options_description("Command Line options");
   mp_config_file_options = new po::options_description("Configuration File options");
   mp_visible_options     = new po::options_description("Visible options");
   mp_variable_map        = new po::variables_map;
   mp_positional_options  = new po::positional_options_description;

};

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
ProgramOptionsBase::~ProgramOptionsBase()  
{
    if (mp_generic_options     != 0 ) delete mp_generic_options  ;
    if (mp_config_options      != 0 ) delete mp_config_options   ;
    if (mp_hidden_options      != 0 ) delete mp_hidden_options   ;
    if (mp_cmdline_options     != 0 ) delete mp_cmdline_options     ;
    if (mp_config_file_options != 0 ) delete mp_config_file_options ;
    if (mp_visible_options     != 0 ) delete mp_visible_options     ;
    if (mp_variable_map        != 0 ) delete mp_variable_map      ;
    if (mp_positional_options  != 0 ) delete mp_positional_options; 

};

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
void ProgramOptionsBase::RegisterConfiguration(int ac_, char* p_av_[])
{
    (*mp_cmdline_options).add(*mp_generic_options);
    (*mp_config_file_options).add(*mp_config_options);
    (*mp_visible_options).add(*mp_cmdline_options).add(*mp_config_options);

//parse command line
    store(po::command_line_parser(ac_, p_av_).options(*mp_cmdline_options).run(), *mp_variable_map);
    notify(*mp_variable_map);

//parse config file        
    std::ifstream ifs(m_config_file.c_str());
    store(po::parse_config_file(ifs, *mp_config_file_options), *mp_variable_map);
    notify(*mp_variable_map);
}
/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
void ProgramOptionsBase::Help()
{
    if (mp_variable_map->count("help")) {
        cout << *mp_visible_options << "\n";
        exit(0);;
    }
    
    if (mp_variable_map->count("version")) {
        cout << "Kosim version 0.1\n";
        exit(0);;
    }
}

