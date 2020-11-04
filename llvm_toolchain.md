# Building a complete LLVM toolchain

## The LLVM project directory structure
Given that there are multiple components to a complete LLVM-based C++ toolchain, it is important to know where each component should go in order to be able to build the toolchain. The following is a concise explanation of these components:
```
llvm
 |
 |--- tools/
 |     |--- clang - The clang repository.
 |     |--- clang/tools/extra - The clang-tools-extra repository.
 |     |--- lld - The LLVM linker repository.
 |     |--- lldb - The LLVM debugger repository.
 |     |--- polly - High-level loop and data-locality optimizer and optimization infrastructure for LLVM.
 |--- projects/
       |--- compiler-rt - Implementation of the low-level target-specific hooks required by code generation and other runtime components, runtime libraries that are required to run the code with sanitizer instrumentation, a library for collecting coverage information, and a target-independent implementation of Apple "Blocks" runtime interfaces.
       |--- libcxxabi - An implementation of the low level support for a standard C++ library.
       |--- libcxx - The LLVM implementation of the C++ standard library, named libc++.
       |--- libunwind - An implementation of the interface defined by the HP libunwind project.
       |--- openmp - Contains the components required to build an executable OpenMP program that are outside the compiler itself.
```

## Building the toolchain
After building the complete LLVM directory structure as specified above, the following CMake command may be used to build the toolchain:
```
cd llvm
mkdir build
cd build
cmake -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=On -DLLVM_ENABLE_LIBCXX=On -DLIBCXXABI_USE_LLVM_UNWINDER=YES -DLIBCXX_USE_COMPILER_RT=YES -DLIBCXXABI_USE_COMPILER_RT=YES -DLLVM_ENABLE_THREADS=On -DLIBCXX_ENABLE_EXCEPTIONS=On -DLIBCXX_ENABLE_RTTI=On -DLLVM_USE_LINKER=gold -DCMAKE_INSTALL_PREFIX=~/toolchain/llvm -DCMAKE_BUILD_TYPE=Release ../
```

**Note:** If `-DLLVM_ENABLE_PROJECTS=libunwind` is added to the CMake command above, it will look for a libunwind folder next to the main `llvm` folder. I am guessing this option is used for an out-of-tree build of `libunwind`. When not using this option, and placing the `libunwind` folder in `llvm/projects/libunwind`, the `libunwind` library is built along with the toolchain.

**Note:** The above CMake command example sets `CMAKE_INSTALL_PREFIX` to a specific directory in current user's home directory. If desired, this path should be changed.

**Note:** The CMake command example uses the GNU Gold linker.

## Helper Script
The following script downloads the desired LLVM version and builds it:
```
#!/bin/bash

version=$1
if [ -z $version ]; then
    echo "Version is empty"
    exit 1
fi
bases="llvm-${version}.src"
bases="${bases} clang-${version}.src"
bases="${bases} compiler-rt-${version}.src"
bases="${bases} libcxx-${version}.src"
bases="${bases} libcxxabi-${version}.src"
bases="${bases} libunwind-${version}.src"
bases="${bases} lld-${version}.src"
bases="${bases} lldb-${version}.src"              \
bases="${bases} openmp-${version}.src"
bases="${bases} polly-${version}.src"
bases="${bases} clang-tools-extra-${version}.src"

for base in ${bases}
do
    # wget -t inf -c http://releases.llvm.org/${version}/${base}.tar.xz
    # It seems like sometimes LLVM uses the following URL:
    wget -t inf -c https://github.com/llvm/llvm-project/releases/download/llvmorg-${version}/${base}.tar.xz
    tar xvf ${base}.tar.xz >/dev/null
done

llvm_root=llvm-${version}.src
mv -v clang-${version}.src ${llvm_root}/tools/clang
mv -v clang-tools-extra-${version}.src ${llvm_root}/tools/clang/tools/extra
mv -v lld-${version}.src ${llvm_root}/tools/lld
mv -v lldb-${version}.src ${llvm_root}/tools/lldb
mv -v polly-${version}.src ${llvm_root}/tools/polly

mv -v compiler-rt-${version}.src ${llvm_root}/projects/compiler-rt
mv -v libcxx-${version}.src ${llvm_root}/projects/libcxx
mv -v libcxxabi-${version}.src ${llvm_root}/projects/libcxxabi
mv -v libunwind-${version}.src ${llvm_root}/projects/libunwind
mv -v openmp-${version}.src ${llvm_root}/projects/openmp

for base in ${bases}
do
    echo "Removing ${base}"
    rm ./${base}.tar.xz
done

echo "Finished!"
exit 0
```

# Separately Building libcxx and libcxxabi
## Compiling libcxx Without libcxxabi
```
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/home/kian/libc++ -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="-std=c++17" ../libcxx
```

## Compiling libcxxabi With libc++
```
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/home/kian/libc++abi -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="-std=c++17 -I/home/kian/libc++/include" -DLIBCXXABI_LIBCXX_INCLUDES=/home/kian/libc++/include/c++/v1 ../libcxxabi/
```

## Compiling libcxx With libcxxabi
```
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/home/kian/cpp-toolchain/libc++ -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS="-std=c++17" -DLIBCXX_CXX_ABI=libcxxabi -DLIBCXX_CXX_ABI_LIBRARY_PATH=/home/kian/libc++abi/lib -DLIBCXX_CXX_ABI_INCLUDE_PATHS=../libcxxabi/include ../libcxx
```

## Compiling source code using the above toolchain
If both libc++ and libc++abi are installed with a prefix of /usr, then compiling code can be as simple as the following:

```
clang++ -o helloworld -std=c++17 -stdlib=libc++ -lc++ -lc++abi -lc -lgcc_s main.cpp
```

The following is a simple shell script that can be used to compile source code using the above toolchain, if it is not installed in a place that is already in the lookup path:

```
#!/bin/bash
LIBCPP_INCLUDE_DIR="/home/kian/cpp-toolchain/libc++/include/c++/v1"
LIBCPP_LIB_DIR="/home/kian/cpp-toolchain/libc++/lib"
LIBCPPABI_LIB_DIR="/home/kian/cpp-toolchain/libc++abi/lib"
CXX_FLAGS="-std=c++17 -stdlib=libc++ -lc++abi -lc -lgcc_s"
SOURCES="src/main.cpp"
clang++ -o ./build/a.out -I "${LIBCPP_INCLUDE_DIR}" -L "${LIBCPP_LIB_DIR}" -L "${LIBCPPABI_LIB_DIR}" ${CXX_FLAGS} ${SOURCES}
```

Running `ldd` on the produced executable will show the dynamic libraries it needs to run:
```
    linux-vdso.so.1 =>  (0x00007fffa4997000)
    libc++abi.so.1 => not found
    libc++.so.1 => not found
    libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f70061ea000)
    libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f7005fd4000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f7005c0a000)
    /lib64/ld-linux-x86-64.so.2 (0x00007f70064f3000)
```

So, it turns out, the shared libraries for libc++ and libc++abi are not in a path that they should be, like the other shared libraries. I think the reason is due to the fact that I have installed the shared libraries in my home folder. Therefore, in order to get this to work properly, I have to set the environment variable `LD_LIBRARY_PATH` to the directory where these shared libraries are in.

Aside from using the `LD_LIBRARY_PATH` variable, during compilation, the flag `-Wl,-rpath,/abs/path/to/libdir` can be used to provide an absolute path to the location of the shared libraries that may be needed.As a slightly better alternative, the symbol `$ORIGIN` can be used to build the path relative to the executable's location. As an example, to inform `ld` to lookup the lib directory that is alongside the executable, the following flag can be used: `-Wl,-rpath,'$ORIGIN/lib'`.
It is important to use single quotes so that `$ORIGIN` does not get resolved when executing the command. The proper value for origin is resolved at runtime.

In order for the linker to be able to see where libraries are located, the configuration in `/etc/ld.so.conf` is used. In Debian-based distros, there is a `/etc/ld.so.conf.d/` directory that has a bunch of different configurations. Long story short, adding shared libraries to `/usr/local/lib` will make sure the linker sees these libraries because this directory is in the default configurations of /etc/ld.so.conf.d.
