/*===============================================================================================
    Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    Author: Cicerone Mihalache                                     
    Support: kosim@kotys.biz 
===============================================================================================*/

#ifndef KOSIM_EX_GC_TEST4_GENERIC_CPU_H
#define KOSIM_EX_GC_TEST4_GENERIC_CPU_H

#include <stdint.h>
#include <vector>

//#define SC_INCLUDE_DYNAMIC_PROCESSES defined in CMakeList.txt defined in CMakeList.txt
#include "systemc.h"
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
#include "generic_cpu_base.h"

// GenericCPU module generating generic payload transactions

class GenericCPU : public GenericCPUBase
{
public:

  GenericCPU(sc_module_name name_, uint32_t id_ = 0);
  ~GenericCPU();
  SC_HAS_PROCESS(GenericCPU);
  
private:
  void STMain();
  virtual void InitSystem();
  void TreatPeripheral0();
  void TreatPeripheral1();
  void TreatPeripheral2();
  
  typedef  void (GenericCPU::*MethodPointer)(); 
  std::vector<MethodPointer> mv_program_peripheral;
};


#endif // KOSIM_EX_GC_TEST4_GENERIC_CPU_H

