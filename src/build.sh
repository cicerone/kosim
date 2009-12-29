#!/bin/sh

export PYTHON_INCLUDE=/usr/include/python2.5
export SYSTEMC_INCLUDE=/usr/local/systemc-2.2.0/include
export SCV_INCLUDE=/usr/local/scv-1.0p2-sysc2.2/include
export TLM_INCLUDE=/usr/local/TLM-2009-07-15/include/tlm

export SYSTEMC_LIB=/usr/local/systemc-2.2.0/lib-linux
export SCV_LIB=/usr/local/scv-1.0p2-sysc2.2/lib-linux

python main/generic_cpu/build_program_options_links.py

make clean 
cmake clean .
cmake .
make
