#Create a shared library called "doulos_tutorial7"

#include dirs
#include_directories (${KOSIM_SOURCE_DIR}/examples)

# The extension is already found. Any number of sources could be listed here.
add_library (doulos_tutorial7 SHARED at_example.cpp)


