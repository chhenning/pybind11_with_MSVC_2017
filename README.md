# pybind11_with_MSVC_2017

Examples of using pybind11 with Visual Studio 2017 and cmake in a x64 Windows environment.

# Setup

1. Create symbolic links to pybind11 folder, e.g. on cmd in Admin mode:

    mklink /D D:\pybind11_with_MSVC_2017\simple_extension\pybind11 D:\pybind11
    
This needs to be done for each project you like run from this repository.


2. Open Visual Studio x64 Native Tools Command Prompt for VS 2017

Build extension

    cd extension
    mkdir build
    cd build
    cmake -A x64 ..
    cmake --build . --config Release --target example
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
    
    
    