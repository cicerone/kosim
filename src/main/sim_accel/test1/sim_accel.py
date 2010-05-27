#!/usr/bin/env python
#==============================================================================================
#  Copyright (c) 2009 Kotys LLC. Distributed under the Boost Software License, Version 1.0. 
#  (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Author: Cicerone Mihalache                                
#  Support: kosim@kotys.biz 
#==============================================================================================

import sys
import libkosim_sim_accel_test1 as kosim_sim_accel

#print len(sys.argv)
#for arg in sys.argv:
#    print "arg(%s)\n" % (arg)

opt_builder = kosim_sim_accel.OptionsBuilder()

for arg in sys.argv:
    opt_builder.SetArgument(arg)
 
opt_builder.BuildArgv()
opt_builder.InitProgramOptions()
kosim_sim_accel.run_sim()
print "--- Test DONE ---"


