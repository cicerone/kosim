#Create a shared library called "first_class" which includes the source file "first_class.cpp".
#include dirs
#include_directories (${KOSIM_SOURCE_DIR}/examples/sc/simple_fifo)

# The extension is already found. Any number of sources could be listed here.
add_library (tlm2_getting_started_2 SHARED tlm2_getting_started_2.cpp)
#add_library (simple_fifo simple_fifo.cpp)


