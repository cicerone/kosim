#!/usr/bin/python

import os

current_path = os.getcwd()
cmd = 'ls'
print "===================" 
print current_path
print "===================" 
cmd = 'ln -s ' +  current_path + '/program_options/options_builder.h '        + current_path + '/main/generic_cpu/test2/options_builder.h'
os.system(cmd)
cmd = 'ln -s ' +  current_path + '/program_options/options_builder.cpp '      + current_path + '/main/generic_cpu/test2/options_builder.cpp'
os.system(cmd)
cmd = 'ln -s ' +  current_path + '/program_options/program_options_base.h '   + current_path + '/main/generic_cpu/test2/program_options_base.h'
os.system(cmd)
cmd = 'ln -s ' +  current_path + '/program_options/program_options_base.cpp ' + current_path + '/main/generic_cpu/test2/program_options_base.cpp'
os.system(cmd)

