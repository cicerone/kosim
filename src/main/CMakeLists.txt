include_directories ($ENV{BOOST_ROOT}/include)
include_directories ($ENV{BOOST_ROOT}/boost/thread)
include_directories (${KOSIM_SOURCE_DIR}/first_class)
include_directories (/usr/include/python2.5)


#some debugging messages
MESSAGE( "Your Unix home directory is $ENV{HOME}." )
#MESSAGE( "Your irrlicht home directory is $ENV{IRRLICHT_ROOT}." )

#SET(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_RELEASE        "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")
#SET(CMAKE_CXX_FLAGS_DEBUG          "-ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings -Wpadded")

# Make sure the linker can find the Cost library once it is built.
#link_directories (${VSM_SERIAL_BINARY_DIR}/cost)
#link_directories (${VSM_SERIAL_BINARY_DIR}/io)
#link_directories (${VSM_SERIAL_BINARY_DIR}/slot)
#link_directories (${VSM_SERIAL_BINARY_DIR}/utils)
#link_directories (${VSM_SERIAL_BINARY_DIR}/sound)

#link_directories (/usr/local/lib/)
#link_directories ($ENV{IRRLICHT_ROOT}/lib/Linux)
#link_directories ($ENV{IRRKLANG_ROOT}/bin/linux-gcc)
link_directories (/usr/lib/)

#some debugging messages
#MESSAGE( "Your program_options lib is in: $ENV{BOOST_ROOT}/bin.v2/libs/program_options/build/gcc-4.1.2/release/link-static/threading-multi.")

# Add executable called "kosim" that is built from the source files
#add_executable (kosim main.cpp)
add_library (kosim SHARED hello.cpp wrap_hello.cpp)

# Link the executable to the used libraries.
target_link_libraries (kosim first_class libboost_python-gcc43-mt-1_37.so)

