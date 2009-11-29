#Create a shared library called "first_class" which includes the source file "first_class.cpp".
#include dirs
include_directories ($KOSIM_SOURCE_DIR}/examples/sc/simple_bus)

# The extension is already found. Any number of sources could be listed here.
add_library (simple_bus SHARED simple_bus_arbiter.cpp simple_bus.cpp simple_bus_main.cpp simple_bus_master_blocking.cpp simple_bus_master_direct.cpp simple_bus_master_non_blocking.cpp simple_bus_tools.cpp simple_bus_types.cpp)





