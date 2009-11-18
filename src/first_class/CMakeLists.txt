#Create a shared library called "first_class" which includes the source file "first_class.cpp".
#include dirs
include_directories ($KOSIM_SOURCE_DIR}/first_class)

# The extension is already found. Any number of sources could be listed here.
add_library (first_class SHARED first_class.cpp)

