#  Copyright Joel de Guzman 2002-2007. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Hello World Example from the tutorial

import sys
import kosim_generic_cpu 

#print len(sys.argv)
#for arg in sys.argv:
#    print "arg(%s)\n" % (arg)

opt_builder = kosim_generic_cpu.OptionsBuilder()

for arg in sys.argv:
    opt_builder.SetArgument(arg)
 
opt_builder.BuildArgv()
opt_builder.InitProgramOptions()
kosim_generic_cpu.run_sim()
print "--- Test DONE ---"


