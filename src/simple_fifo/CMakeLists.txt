#Create a shared library called "first_class" which includes the source file "first_class.cpp".
#include dirs
include_directories ($KOSIM_SOURCE_DIR}/simple_fifo)

# The extension is already found. Any number of sources could be listed here.
add_library (simple_fifo SHARED simple_fifo.cpp)
#add_library (simple_fifo simple_fifo.cpp)




# #Example of HOWTO make an executable in one dir
# add_executable (simple_fifo simple_fifo.cpp)
# # Link the executable to the used libraries.
# target_link_libraries (simple_fifo libscv.so libsystemc.a) 

