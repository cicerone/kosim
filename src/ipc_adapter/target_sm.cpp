/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/



#include "target_sm.h"

TargetSharedMemory::TargetSharedMemory() :
    irq_vector     (       0),
    is_irq_consumed(    true),
    is_buff_rd_empty(  false),
    is_buff_wr_full(    true)
{
    tlm_payload_rd.set_data_ptr(reinterpret_cast<uint8_t*>( &buff_rd[0] )); 
    tlm_payload_wr.set_data_ptr(reinterpret_cast<uint8_t*>( &buff_wr[0] ));
    // NOTE: extra code needed if byte_enable mechanism is used
}

TargetSharedMemory::~TargetSharedMemory()
{
}

