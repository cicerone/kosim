

#include "program_options.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////


#define SLEEP_TIME_PER_FRAME                       1    // ms
#define SLOTMACHINE_HS_TIME_LOW                 1000    // ms
#define SLOTMACHINE_HS_TIME_HIGH                1000    // ms

/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
ProgramOptions* ProgramOptions::mp_instance = 0;
int             ProgramOptions::m_argc      = 0;
char**          ProgramOptions::mp_argv     = 0;


/////////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////////
ProgramOptions::ProgramOptions(int ac_, char* p_av_[]) : 
    m_dbg_level                       (0                              ),
// options from configuration file
    m_driver_type                     ("NOT_INITIALIZED!"             ),
    m_sleep_time_per_frame            (SLEEP_TIME_PER_FRAME           ),
    m_sm_high_speed_time_lowest_value (SLOTMACHINE_HS_TIME_LOW        ),
    m_sm_high_speed_time_highest_value(SLOTMACHINE_HS_TIME_HIGH       ),
    m_cmd_line_arg1                   (77                             ),
// END options from configuration file
   m_config_file         ("NOT_INITIALIZED!"),

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

   InitConfiguration(ac_, p_av_);
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
void ProgramOptions::InitConfiguration(int ac_, char* p_av_[])
{
    mp_generic_options->add_options()
        ("version, v", "print version string")
        ("help, h", "produce help message")    
        ("cfg", po::value<std::string>(&m_config_file)->default_value("kosim.cfg"), "config file") 
        ;

    mp_config_options->add_options()
///////////  OPTIONS from configuraton file  ////////////////////////////////////
        ("DriverType"        , po::value<std::string>(&m_driver_type)->default_value("SOFTWARE"), "driver type")
        ("SleepTimePerFrame" , po::value<int32_t>(&m_sleep_time_per_frame)->default_value(SLEEP_TIME_PER_FRAME), "Sleep time for each frame [ms]")
        ("SpinHighSpeedTime.LowestValue", po::value<int32_t>(&m_sm_high_speed_time_lowest_value)->default_value(SLOTMACHINE_HS_TIME_LOW ), "Lowest value of the duration of high speed spin")
        ("SpinHighSpeedTime.HighestValue", po::value<int32_t>(&m_sm_high_speed_time_highest_value)->default_value(SLOTMACHINE_HS_TIME_HIGH ), "Highest value of the duration of high speed spin")
        ;

    mp_cmdline_options->add_options()
///////////  OPTIONS from command line   ////////////////////////////////////
        ("cmd_line_arg1"        , po::value<int32_t>(&m_cmd_line_arg1)->default_value(77), "first command line argument")
        ;

    mp_hidden_options->add_options()
        ("debug_level", po::value<int>(&m_dbg_level)->default_value(0), "debugging level")
        ;

    (*mp_cmdline_options).add(*mp_generic_options);
    (*mp_config_file_options).add(*mp_config_options);
    (*mp_visible_options).add(*mp_cmdline_options).add(*mp_config_options);

//     mp_positional_options->add("cfg"   , 1);

//parse command line
//    store(po::command_line_parser(ac_, p_av_).options(*mp_cmdline_options).positional(*mp_positional_options).run(), *mp_variable_map);
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
        m_argc  = ac_  ;
        mp_argv = p_av_; 
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
        cout << "m_driver_type                        : " <<  m_driver_type                         << endl;
        return 0;
}

