# The Boost Libraries

## Compiling
In order to build the Boost libraries, the tool `b2` should be used. Assuming `clang++` is in the path, in order to build Boost using `clang++` and `libc++`:

```
./b2 toolset=clang cxxflags="-stdlib=libc++ -std=c++14" linkflags="-stdlib=libc++" -j 8
```

At the time of this writing (Boost version 1.66.0), compilation cannot be done with the `-std=c++17` flag, because the `auto_ptr` class is no longer in existence, but parts of Boost are still using it. `auto_ptr` had been deprecated since C++11 and finally removed in C++17.

Compiling boost took the following time in the first round:
```
real	116m2.628s
user	474m24.432s
sys	90m33.540s
```

In total, there were 54 failed targets due to missing `pyconfig.h` header, which is due to not having the package `python3.5-dev` installed. After installing, I also had to execute the following:
```
export CPLUS_INCLUDE_PATH=/usr/include/python3.5
```

After installing the needed package, and re-running the build script, it took the following times:
```
real	7m17.312s
user	29m13.704s
sys	5m40.344s
```

In order to install the built libraries, as root and after making sure CXX is set to `clang++`, I executed the following:
```
./b2 install toolset=clang cxxflags="-std=c++14 -stdlib=libc++" linkflags="-stdlib=libc++" --prefix=/usr/local
```

Also, last but not least, when building a project that uses **Boost::Log**, I encountered linker errors that I could not exactly figure out why they are happening, as it seems like I do have the shared object files of the log library. However, after modifying `boost/config/user.hpp` and adding the following line, then rebuilding boost, I seem to be able to correctly link:
```
#define BOOST_LOG_DYN_LINK
```

**Update:** Later on, I was trying to see if I can link Boost libraries statically, as this reduced the need to deploy the built Boost libraries along with my program. To do this, I re-built Boost using the following:
```
./b2 toolset=clang link=static cxxflags="-stdlib=libc++ -std=c++14" linkflags="-stdlib=libc++" -j 8
```

Then, in order to force a static link of Boost in my project, I used the following CMake file:
```
set("${TARGET_NAME}" PROPERTY CXX_STANDARD 14)

add_executable("${TARGET_NAME}" "src/main.cpp")

target_include_directories("${TARGET_NAME}" PUBLIC "include" ${Boost_INCLUDE_DIRS})
target_compile_options("${TARGET_NAME}" PUBLIC "-stdlib=libc++")

target_link_libraries("${TARGET_NAME}" PUBLIC -nodefaultlibs -lc++ -lc++abi -lc -lm -lgcc_s -lgcc)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.66.0 EXACT REQUIRED COMPONENTS thread system log_setup log filesystem)
message(${Boost_LIBRARIES})
target_link_libraries("${TARGET_NAME}" PUBLIC ${Boost_LIBRARIES})

target_link_libraries("${TARGET_NAME}" PUBLIC -lpthread)
```

At first, there were some linker errors with references to code in the filesystem library. It turns out, the log library depends on filesystem and therefore, the filesystem library must be linked after the log library. This has been fixed in the above CMake example.

## Using The Compiled Boost Libraries
The following example shows how to compile a project that depends on Boost.Beast, which is a header-only library.

Assuming the Boost libraries have been installed such that all of the necessary libraries and include files are in `PATH`, the following CMake file can be used:
```
cmake_minimum_required(VERSION 3.5)
project(beast_test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lc -lc++ -lc++abi -lpthread")

set(INCLUDES "")
include_directories("${INCLUDES}")

add_executable(beast_test "src/main.cpp")
target_link_libraries(beast_test "libboost_system.so")
```

The only dependency of Boost.Beast is on Boost.System.
