# pybind11_with_MSVC_2017

Examples of using pybind11 with Visual Studio 2017 and cmake in a x64 Windows environment.

# Setup

1. Update the sub-module:

    git submodule update --init    

Explanation: Your code "example.cpp" looks for the header files in the pybind11 directory. git submodule command clones the pybind header files from the official repo. 


2. Open Visual Studio x64 Native Tools Command Prompt for VS 2017

How to build simple_extension

    cd simple_extension
    mkdir build
    cd build
    cmake -A x64 ..
    cmake --build . --config Release --target example
    cd Release
    python
    >>> import example
    >>> example.add(9,7)
    16
    >>>quit()

    
Build embed

    cd embed
    mkdir build
    cd build
    cmake -A x64 ..
    cmake --build . --config Release --target example
    cd Release
    .\example.exe
    
    
    