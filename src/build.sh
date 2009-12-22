#!/bin/sh

export PYTHON_INCLUDE=/usr/include/python2.5
export SYSTEMC_INCLUDE=/usr/local/systemc-2.2.0/include
export SCV_INCLUDE=/usr/local/scv-1.0p2-sysc2.2/include
export TLM_INCLUDE=/usr/local/TLM-2009-07-15/include/tlm

export SYSTEMC_LIB=/usr/local/systemc-2.2.0/lib-linux
export SCV_LIB=/usr/local/scv-1.0p2-sysc2.2/lib-linux

source main/generic_cpu/build_program_options_links.sh

make clean 
cmake clean .
cmake .
make
cp ./main/sc/simple_fifo/libkosim.so ./main/sc/simple_fifo/kosim.so
cp ./main/sc/simple_bus/libkosim_simple_bus.so ./main/sc/simple_bus/kosim_simple_bus.so
cp ./main/scv/pythagoras/libkosim_pythagoras.so ./main/scv/pythagoras/kosim_pythagoras.so
cp ./main/generic_cpu/libkosim_generic_cpu.so ./main/generic_cpu/kosim_generic_cpu.so
cp ./main/tlm/doulos_tutorial1/libkosim_doulos_tutorial1.so ./main/tlm/doulos_tutorial1/kosim_doulos_tutorial1.so
cp ./main/tlm/doulos_tutorial2/libkosim_doulos_tutorial2.so ./main/tlm/doulos_tutorial2/kosim_doulos_tutorial2.so
cp ./main/tlm/doulos_tutorial3/libkosim_doulos_tutorial3.so ./main/tlm/doulos_tutorial3/kosim_doulos_tutorial3.so
cp ./main/tlm/doulos_tutorial4/libkosim_doulos_tutorial4.so ./main/tlm/doulos_tutorial4/kosim_doulos_tutorial4.so
cp ./main/tlm/doulos_tutorial5/libkosim_doulos_tutorial5.so ./main/tlm/doulos_tutorial5/kosim_doulos_tutorial5.so
cp ./main/tlm/doulos_tutorial6/libkosim_doulos_tutorial6.so ./main/tlm/doulos_tutorial6/kosim_doulos_tutorial6.so
cp ./main/tlm/doulos_tutorial7/libkosim_doulos_tutorial7.so ./main/tlm/doulos_tutorial7/kosim_doulos_tutorial7.so
