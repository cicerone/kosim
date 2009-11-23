#Create a shared library called "first_class" which includes the source file "first_class.cpp".
#include dirs
include_directories ($KOSIM_SOURCE_DIR}/hierarchy_scanner)

# The extension is already found. Any number of sources could be listed here.
add_library (hierarchy_scanner SHARED hierarchy_scanner.cpp)

