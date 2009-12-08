#Create a shared library called "hierarchy_scanner"
#include dirs
include_directories ($KOSIM_SOURCE_DIR}/hierarchy_scanner)

# The extension is already found. Any number of sources could be listed here.
add_library (hierarchy_scanner SHARED hierarchy_scanner.cpp)

