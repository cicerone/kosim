include_directories ($ENV{BOOST_ROOT}/include)
include_directories ($ENV{BOOST_ROOT}/boost/thread)
include_directories (${KOSIM_SOURCE_DIR}/examples/scv/pythagoras)
include_directories (${KOSIM_SOURCE_DIR}/hierarchy_scanner)
include_directories (${KOSIM_SOURCE_DIR}/program_options)
include_directories (/usr/include/python2.5)


#some debugging messages
MESSAGE( "Your Unix home directory is $ENV{HOME}." )

#SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_RELEASE        "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_DEBUG          "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")

# Make sure the linker can find the library once it is built.
#link_directories (/usr/local/lib/)
link_directories (/usr/lib/)

#some debugging messages
#MESSAGE( "Your program_options lib is in: $ENV{BOOST_ROOT}/bin.v2/libs/program_options/build/gcc-4.1.2/release/link-static/threading-multi.")

# Add shared library called "kosim" that is built from the source files
add_library (kosim_pythagoras SHARED wrap_pythagoras.cpp)

# Link the executable to the used libraries.
target_link_libraries (kosim_pythagoras pythagoras hierarchy_scanner program_options libboost_program_options-gcc43-mt-1_37.so libboost_python-gcc43-mt-1_37.so libscv.so libsystemc.a)

