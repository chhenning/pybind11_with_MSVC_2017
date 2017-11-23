
#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;
using namespace pybind11::literals;

int main()
{
    py::scoped_interpreter guard{};
    
    py::int_ py_int(42);
    py::str py_str("Hello from python");
    
    std::cout << py_str.cast<std::string>() << std::endl;
    
    return 0;
}