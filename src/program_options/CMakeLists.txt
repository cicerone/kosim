#Create a shared library called "program_options" which includes the source file "program_options.cpp".
#include dirs
include_directories ($KOSIM_SOURCE_DIR}/program_options)

# The extension is already found. Any number of sources could be listed here.
add_library (program_options SHARED options_builder.cpp program_options.cpp)


