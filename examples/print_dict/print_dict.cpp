
#include <iostream>

#include <pybind11/pybind11.h>

namespace py = pybind11;

////////////////////////

void print_dict(py::dict dict)
{
    for(auto item : dict)
    {
        std::cout << "key=" << std::string(py::str(item.first)) << ", "
            << "value="  << std::string(py::str(item.second)) << std::endl;
    }
}

PYBIND11_MODULE(py_ext, m)
{
    m.doc() = "print dictionary"; // optional module docstring
    
    m.def("print_dict", &print_dict, "print all key-values in dictionary");
}