/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/


#include "log_builder.h"


void foo1()
{
    BOOST_LOG_FUNCTION();
    LogSevChannel& log_z1 = LogBuilder::GetInstance()->GetLogger("zzz_1");
    BOOST_LOG_SEV(log_z1, error) << "error from zzz_1";
}

void foo2()
{
    BOOST_LOG_FUNCTION();
    LogSevChannel& log_z2 = LogBuilder::GetInstance()->GetLogger("zzz_2");
    BOOST_LOG_SEV(log_z2, info1) << "info1 from zzz_2";
    foo1();
}

void foo3()
{
    BOOST_LOG_FUNCTION();
    LogSevChannel& log_y1 = LogBuilder::GetInstance()->GetLogger("yyy_1");
    BOOST_LOG_SEV(log_y1, normal) << "normal from yyy_1";
    foo2();
}

int main(int argc, char* argv[])
{
    LogBuilder* p_lb = LogBuilder::GetInstance();
    p_lb->SetLogFile("first.log");

    LogSevChannel& log_z1 = p_lb->GetLogger("zzz_1");
    p_lb->EnableLoggers(info3, "");

    p_lb->EnableLog(true);

    BOOST_LOG_FUNCTION();
    BOOST_LOG_SEV(log_z1, info5) << "info5 from zzz_1";
//    p_lb->EnableLog(true);
    foo1();
    foo2();
    foo3();
}

