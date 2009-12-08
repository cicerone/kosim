#Create a shared library called "pythagoras"
#include dirs
#include_directories (${KOSIM_SOURCE_DIR}/examples/scv/pythagoras)

# The extension is already found. Any number of sources could be listed here.
add_library (pythagoras SHARED pythagoras.cpp)


