#Create a library called "Cost" which includes the source file "finalSuite.cc".
# The extension is already found. Any number of sources could be listed here.
include_directories ($KOSIM_SOURCE_DIR}/first_class)

add_library (first_class SHARED first_class.cpp)
