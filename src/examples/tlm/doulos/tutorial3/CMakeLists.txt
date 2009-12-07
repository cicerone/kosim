#Create a shared library called "first_class" which includes the source file "first_class.cpp".
#include dirs
#include_directories (${KOSIM_SOURCE_DIR}/examples/sc/simple_fifo)

# The extension is already found. Any number of sources could be listed here.
add_library (doulos_tutorial3 SHARED tlm2_getting_started_3.cpp)


