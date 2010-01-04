/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "program_options.h"

using namespace std;


/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
ProgramOptions* ProgramOptions::mp_instance = 0;


/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
ProgramOptions::ProgramOptions(int ac_, char* p_av_[]) : 
    m_dbg_level                 (0                   ),
// options from configuration file
    m_test_name                 ("NOT_INITIALIZED!"  ),
    m_addr_width_int_resources  (8                   ),
    m_mem0_lowest_value         (0                   ),
    m_mem0_highest_value        (0                   ),
    m_cmd_line_arg1             (77                  ),
// END options from configuration file
   m_config_file                ("NOT_INITIALIZED!"),

   mp_generic_options    (0),
   mp_config_options     (0),
   mp_hidden_options     (0), 
   mp_cmdline_options    (0),
   mp_config_file_options(0),
   mp_visible_options    (0),
   mp_variable_map       (0),
   mp_positional_options (0)
{
   mp_generic_options     = new po::options_description("Generic options");
   mp_config_options      = new po::options_description("Configuration");
   mp_hidden_options      = new po::options_description("Hidden options");
   mp_cmdline_options     = new po::options_description("Command Line options");
   mp_config_file_options = new po::options_description("Configuration File options");
   mp_visible_options     = new po::options_description("Visible options");
   mp_variable_map        = new po::variables_map;
   mp_positional_options  = new po::positional_options_description;

}

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
ProgramOptions::~ProgramOptions()  
{
    if (mp_generic_options     != 0 ) delete mp_generic_options  ;
    if (mp_config_options      != 0 ) delete mp_config_options   ;
    if (mp_hidden_options      != 0 ) delete mp_hidden_options   ;
    if (mp_cmdline_options     != 0 ) delete mp_cmdline_options     ;
    if (mp_config_file_options != 0 ) delete mp_config_file_options ;
    if (mp_visible_options     != 0 ) delete mp_visible_options     ;
    if (mp_variable_map        != 0 ) delete mp_variable_map      ;
    if (mp_positional_options  != 0 ) delete mp_positional_options; 
    if (mp_instance            != 0 ) delete mp_instance         ;

}

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
void ProgramOptions::InitConfiguration()
{
    mp_generic_options->add_options()
        ("version, v", "print version string")
        ("help, h", "produce help message")    
        ("cfg", po::value<std::string>(&m_config_file)->default_value("kosim.cfg"), "config file") 
        ;

    mp_config_options->add_options()
///////////  OPTIONS from configuraton file  ////////////////////////////////////
        ("TestName"        , po::value<std::string>(&m_test_name)->default_value("test_x"), "test_name")
        ("AddressWidthInternalResources" , po::value<int32_t>(&m_addr_width_int_resources)->default_value(8), "address width for the internal resources of a peripheral [bits]")
        ("Mem0.LowestValue", po::value<int32_t>(&m_mem0_lowest_value)->default_value  (0 ), "Lowest value of the address 0 value")
        ("Mem0.HighestValue", po::value<int32_t>(&m_mem0_highest_value)->default_value(0 ), "Highest value of the address 0 value")
        ;

    mp_cmdline_options->add_options()
///////////  OPTIONS from command line   ////////////////////////////////////
        ("cmd_line_arg1"        , po::value<int32_t>(&m_cmd_line_arg1)->default_value(77), "first command line argument")
        ;

    mp_hidden_options->add_options()
        ("debug_level", po::value<int>(&m_dbg_level)->default_value(0), "debugging level")
        ;
}
/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
void ProgramOptions::RegisterConfiguration(int ac_, char* p_av_[])
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
ProgramOptions* ProgramOptions::GetInstance(int ac_, char* p_av_[])
{
    if (mp_instance == 0) {
        mp_instance = new ProgramOptions(ac_, p_av_);

        mp_instance->InitConfiguration();
        mp_instance->RegisterConfiguration(ac_, p_av_);
    }
    return mp_instance;  
} 
/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
ProgramOptions* ProgramOptions::GetInstance()
{
    if (mp_instance == 0) {
        cerr << "ERROR! Wrong call of GetInstance()! GetInstance(argc, argv) must be called first!" << endl;
        exit(1);
    }
    return mp_instance;  
} 

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
void ProgramOptions::Help()
{
    if (mp_variable_map->count("help")) {
        cout << *mp_visible_options << "\n";
        exit(0);;
    }
    
    if (mp_variable_map->count("version")) {
        cout << "VSM version 0.1\n";
        exit(0);;
    }
}

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
int ProgramOptions::Dump()
{

        if (mp_variable_map->count("cfg")) {
            cout << "Input files are: " << m_config_file << "\n";
        }

        cout << "///// OPTIONS from pattern configuration file  //////// " << endl;
        cout << "m_test_name                        : " <<  m_test_name                         << endl;
        return 0;
}

