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
    m_transfer_size             (8                   ),
    m_memory_size               (8                   ),
    m_nr_ops_per_xfer           (8                   ),
    m_nr_xfers                  (8                   ),
    m_mem_lowest_value          (0                   ),
    m_mem_highest_value         (0                   ),
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
        ("TransferSize" , po::value<uint32_t>(&m_transfer_size)->default_value(8), "the TLM transfer size in 32 bit words from CPU to periferic and back")
        ("MemorySize" , po::value<uint32_t>(&m_memory_size)->default_value(8), "the memory size of the peripheric in 32 bit words")
        ("NumberOpsPerTransfer" , po::value<uint32_t>(&m_nr_ops_per_xfer)->default_value(8), "the number of operations per data xfer")
        ("NumberTransfers" , po::value<uint32_t>(&m_nr_xfers)->default_value(8), "the number of data xfers")
        ("Mem.LowestValue", po::value<int32_t>(&m_mem_lowest_value)->default_value  (0 ), "Lowest value of  the memory data")
        ("Mem.HighestValue", po::value<int32_t>(&m_mem_highest_value)->default_value(0 ), "Highest value of the memory data")
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

