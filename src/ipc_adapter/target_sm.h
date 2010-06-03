/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/


#ifndef KOSIM_IPCA_TARGET_SM_H
#define KOSIM_IPCA_TARGET_SM_H

#include <stdint.h>

#include "tlm.h"

#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
//#include <iostream>
//#include <cstdio>

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>


class TargetSharedMemory 
{
private: 
public:

    TargetSharedMemory();
    ~TargetSharedMemory();

    static const uint32_t BUFF_SIZE = 1024;

    uint32_t irq_vector;      // the location in shared memory where the interrupt vector is stored
    bool     is_irq_consumed; // true if the Target Adapter did not consume the irq_vector that was sent by the Initiator Adapter
    boost::interprocess::interprocess_condition  cond_irq_consumed;  //Condition to wait until the IRQ is consumed on Target Adapter side 
    boost::interprocess::interprocess_mutex      mutex_irq; //Mutex to protect access to the irq_vector 

    tlm::tlm_generic_payload tlm_payload_rd; //tlm2 payload used for reading
    uint32_t buff_rd[BUFF_SIZE]; // the buffer used to exchange the read data between processes 
    bool     is_buff_rd_empty;   // true if no data was sent from Initiator Adapter to Target Adapter
    boost::interprocess::interprocess_condition  cond_buff_rd_full;  //Condition to wait until Initiator Adapter sends the read data to Target Adapter
    boost::interprocess::interprocess_mutex      mutex_rd; //Mutex to protect access to the read data 

    tlm::tlm_generic_payload tlm_payload_wr; // tlm2 payyload used for writing
    uint32_t buff_wr[BUFF_SIZE]; // the buffer used to exchange the write data between processes
    bool     is_buff_wr_full; // true if data was sent from the Target Adapter to the Initiator Adapter
    boost::interprocess::interprocess_condition  cond_buff_wr_empty;  //Condition to wait until the Initiator Adapter consumes the write data 
    boost::interprocess::interprocess_mutex      mutex_wr; //Mutex to protect access to the write data 

};


#endif // KOSIM_IPCA_TARGET_SM_H
