#  Copyright Joel de Guzman 2002-2007. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt
#  or copy at http://www.boost.org/LICENSE_1_0.txt)
#  Hello World Example from the tutorial

import sys
import kosim 

print kosim.greet()
hi = kosim.hello('California')
print hi.greet()
print kosim.invite(hi)
print hi.invite()
kosim.init_sim()
print "And now print_hierarchy()"
kosim.print_hierarchy()
print "Some ports"
kosim.print_ports("Top1.Consumer1")
print "Some modules"
kosim.print_modules("Top1")
print "Some threads"
kosim.print_threads("Top1.Producer1")
kosim.start_sim()
print "=================="
print len(sys.argv)
for arg in sys.argv:
    print "arg(%s)\n" % (arg)

opt_builder = kosim.OptionsBuilder()

print "------------------"
for arg in sys.argv:
    opt_builder.SetArgument(arg)
 
opt_builder.BuildArgv()
opt_builder.InitProgramOptions()



