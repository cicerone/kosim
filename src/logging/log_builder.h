/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_L_LOG_BUILDER_H
#define KOSIM_L_LOG_BUILDER_H

#include <stdint.h>

#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

//#include <boost/regex.hpp>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/log/common.hpp>
#include <boost/log/filters.hpp>
#include <boost/log/formatters.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/utility/empty_deleter.hpp>
#include <boost/log/utility/scoped_attribute.hpp>
#include <boost/log/sources/severity_feature.hpp>
#include <boost/log/sources/channel_feature.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>

namespace logging = boost::log;
namespace fmt = boost::log::formatters;
namespace flt = boost::log::filters;
namespace sinks = boost::log::sinks;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;


// Here we define our application severity levels.
enum severity_level
{
    info5,
    info4,
    info3,
    info2,
    info1,
    normal,
    warning,
    error
};

// The formatting logic for the severity level
template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
    std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
{
    static const char* const str[] =
    {
        "info5",
        "info4",
        "info3",
        "info2",
        "info1",
        "", // normal
        "WARNING!",
        "ERROR!"
    };
    if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
        strm << str[lvl];
    else
        strm << static_cast< int >(lvl);
    return strm;
}

typedef src::severity_channel_logger_mt<severity_level> LogSevChannel;

class LogBuilder : boost::noncopyable
{
public:
    static     LogBuilder* GetInstance();     
    ~LogBuilder();
    LogSevChannel& GetLogger(const std::string& name_); 
    void    EnableLoggers(const severity_level severity_, const std::string& name_ = "" );
    void    EnableLog(const bool enable_log_);
    void    SetLogFile(const std::string& name_);
    
private:
    static LogBuilder* mp_instance;
    LogBuilder();
    std::map<std::string, LogSevChannel*> m_logger_map;
    typedef sinks::synchronous_sink< sinks::text_ostream_backend > TextSink;// TODO move to not multithreading
    boost::shared_ptr< TextSink > mp_sink;
};

#endif // KOSIM_L_LOG_BUILDER_H
