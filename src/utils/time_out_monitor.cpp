/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#include "time_out_monitor.h"
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
TimeOutMonitor::TimeOutMonitor() :
    m_start_time(0, SC_NS)
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
TimeOutMonitor::~TimeOutMonitor() 
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN: 
// OUT: 
// RET: 
void TimeOutMonitor::update_start_time()
{
    m_start_time = sc_time_stamp();
}
/////////////////////////////////////////////////////////////////////////////////////////////////
//
// IN:  time_out_ - the timeout to be checked 
// OUT: 
// RET: true if timeout passed  
bool TimeOutMonitor::is_time_out(const sc_time& time_out_)
{
    if ((m_start_time + time_out_) < sc_time_stamp()) return true;
    else                                              return false;
}
