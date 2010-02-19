/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include <algorithm>
#include "log_builder.h"

using namespace std;
using boost::shared_ptr;


/////////////////////////////////////////////////////////////////////////////////////
LogBuilder* LogBuilder::mp_instance = 0;
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
LogBuilder::LogBuilder() :
    mp_sink(new TextSink)
{
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
LogBuilder::~LogBuilder()  
{
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
LogBuilder* LogBuilder::GetInstance()
{
    if (mp_instance == 0) {
        mp_instance = new LogBuilder();
    }
    return mp_instance;  
} 

/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
LogSevChannel& LogBuilder::GetLogger(const std::string& name_)
{
    std::map<std::string, LogSevChannel*>::iterator pos;
    pos = m_logger_map.find(name_);
    if (pos == m_logger_map.end()) m_logger_map[name_] = new LogSevChannel(keywords::severity = normal, keywords::channel = name_.c_str());
    
    return *m_logger_map[name_];
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void    LogBuilder::EnableLoggers(const std::string& name_, const severity_level severity_)
{
    logging::core::get()->reset_filter();
    
//   logging::core::get()->set_filter(
//       flt::attr< severity_level >("Severity", std::nothrow) >= severity_ &&
//       flt::attr< std::string >("Channel", std::nothrow) ==  name_.c_str());    

   logging::core::get()->set_filter(
       flt::attr< severity_level >("Severity", std::nothrow) >= severity_ &&
       flt::attr< std::string >("Channel", std::nothrow).contains(name_.c_str()));    
    
// mp_sink->set_filter(
//     flt::attr< severity_level >("Severity", std::nothrow) >= severity_ || // Write all records with "warning" severity or higher
//     flt::attr< std::string >("Channel", std::nothrow) ==  name_.c_str());    
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void    LogBuilder::EnableLog(const bool enable_log_)
{
    logging::core::get()->set_logging_enabled(enable_log_);
}
/////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void    LogBuilder::SetLogFile(const std::string& name_)
{
        TextSink::locked_backend_ptr p_backend = mp_sink->locked_backend();

        shared_ptr< std::ostream > p_stream_cout(&std::clog, logging::empty_deleter());
        p_backend->add_stream(p_stream_cout);
        // We can add more than one stream to the sink backend
        shared_ptr< std::ofstream > p_stream(new std::ofstream(name_.c_str()));
        assert(p_stream->is_open());
        p_backend->add_stream(p_stream);
        logging::core::get()->add_sink(mp_sink);
        
        mp_sink->locked_backend()->set_formatter(fmt::stream
           << "[" // then this delimiter separates it from the rest of the line
           << fmt::named_scope("Scope", keywords::iteration = fmt::reverse) << "] "
           << fmt::message()); // here goes the log record text

        boost::shared_ptr< logging::attribute > pNamedScope(new attrs::named_scope());
        logging::core::get()->add_thread_attribute("Scope", pNamedScope);
}

void foo1()
{
    BOOST_LOG_FUNCTION();
    LogSevChannel& log_1 = LogBuilder::GetInstance()->GetLogger("zzz_1");
    BOOST_LOG_SEV(log_1, error) << "error from zzz_1";
}

void foo2()
{
    BOOST_LOG_FUNCTION();
    LogSevChannel& log_2 = LogBuilder::GetInstance()->GetLogger("zzz_2");
    BOOST_LOG_SEV(log_2, notification) << "notification from zzz_2";
    foo1();
}

int main(int argc, char* argv[])
{
    LogBuilder* p_lb = LogBuilder::GetInstance();
    p_lb->SetLogFile("first.log");

    LogSevChannel& log_1 = p_lb->GetLogger("zzz_1");
    p_lb->EnableLoggers("zzz", normal);

    p_lb->EnableLog(true);

    BOOST_LOG_FUNCTION();
    BOOST_LOG_SEV(log_1, warning) << "warning from zzz_1";
//    p_lb->EnableLog(true);
    foo1();
    foo2();
}

