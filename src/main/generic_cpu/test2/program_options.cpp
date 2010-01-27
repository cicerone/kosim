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


/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
ProgramOptions::ProgramOptions(int ac_, char* p_av_[]) : 
    m_dbg_level                 (0                   ),
// options from configuration file
    m_test_name                 ("NOT_INITIALIZED!"  ),
    m_addr_width_int_resources  (8                   ),
    m_mem0_lowest_value         (0                   ),
    m_mem0_highest_value        (0                   ),
    m_cmd_line_arg1             (77                  )
// END options from configuration file
{

}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
ProgramOptions::~ProgramOptions()  
{
    if (mp_instance            != 0 ) delete mp_instance         ;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
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
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
ProgramOptions* ProgramOptions::GetInstance(int ac_, char* p_av_[])
{
    if (mp_instance == 0) {
        mp_instance = new ProgramOptions(ac_, p_av_);

        mp_instance->InitConfiguration();
        mp_instance->RegisterConfiguration(ac_, p_av_);
    }
    return mp_instance;  
} 
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
ProgramOptions* ProgramOptions::GetInstance()
{
    if (mp_instance == 0) {
        cerr << "ERROR! Wrong call of GetInstance()! GetInstance(argc, argv) must be called first!" << endl;
        exit(1);
    }
    return mp_instance;  
} 
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
int ProgramOptions::Dump()
{

        if (mp_variable_map->count("cfg")) {
            cout << "Input files are: " << m_config_file << "\n";
        }

        cout << "///// OPTIONS from pattern configuration file  //////// " << endl;
        cout << "m_test_name                        : " <<  m_test_name                         << endl;
        return 0;
}

