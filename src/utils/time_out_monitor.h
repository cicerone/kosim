/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_UTILS_TIMEOUT_MONITOR_H
#define KOSIM_UTILS_TIMEOUT_MONITOR_H

#include "systemc.h"
/////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////


class TimeOutMonitor
{
public:
    TimeOutMonitor();
    ~TimeOutMonitor();
    void update_start_time();
    bool is_time_out(const sc_time& time_out_);
private:
    sc_time m_start_time;
};

#endif // KOSIM_UTILS_TIMEOUT_MONITOR_H

