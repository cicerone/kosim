#!/bin/sh

# Change these variables to point to the actual location of
# the SystemC, SCV, and TLM installation.
INSTALL_PREFIX="/usr/local"
SYSTEMC_ROOT="$INSTALL_PREFIX/systemc-2.2.0"
SCV_ROOT="$INSTALL_PREFIX/scv-1.0p2-sysc2.2"
TLM_ROOT="$INSTALL_PREFIX/TLM-2009-07-15"

# Include paths:
export PYTHON_INCLUDE="/usr/include/python`python --version 2>&1 | cut -d ' ' -f2 | cut -d '.' -f1-2`"
export SYSTEMC_INCLUDE="$SYSTEMC_ROOT/include"
export SCV_INCLUDE="$SCV_ROOT/include"
export TLM_INCLUDE="$TLM_ROOT/include/tlm"

# Library paths:
LIB_DIR="lib-linux"
if test "`uname -m`" == "x86_64"; then LIB_DIR="lib-linux64"; fi
export SYSTEMC_LIB="$SYSTEMC_ROOT/$LIB_DIR"
export SCV_LIB="$SCV_ROOT/$LIB_DIR"

echo "PYTHON_INCLUDE  = $PYTHON_INCLUDE "
echo "SYSTEMC_INCLUDE = $SYSTEMC_INCLUDE"
echo "SCV_INCLUDE     = $SCV_INCLUDE    "
echo "TLM_INCLUDE     = $TLM_INCLUDE    "
echo "SYSTEMC_LIB     = $SYSTEMC_LIB    "
echo "SCV_LIB         = $SCV_LIB        "

python main/generic_cpu/build_program_options_links.py

make clean 
cmake clean .
cmake .
make
