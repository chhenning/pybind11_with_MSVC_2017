#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <numeric>
#include <vector>

#include <pybind11\pybind11.h>
#include <pybind11\embed.h>
#include <pybind11\iostream.h>
#include <pybind11\numpy.h>
#include <pybind11\stl.h>


namespace py = pybind11;

PYBIND11_EMBEDDED_MODULE(fast_calc, m) {
    // `m` is a `py::module` which is used to bind functions and classes
    m.def("add", [](int i, int j) {
        return i + j;
    });

    m.def("generic", [](py::args args, py::kwargs kwargs)
    {
        // args is a py::tuple
        // kwargs is a py::dict


    });

    m.def("decipher_args", [](py::args args)
    {
        if (args.size() == 1)
        {
            auto arg = args[0];
            
            if (py::isinstance<float>(arg))
            {
                float f = arg.cast<float>();
            }
            if (py::isinstance<std::string>(arg))
            {
                std::string s = arg.cast<std::string>();
            }


            std::string as_string = py::str(arg.get_type());
        }
    });
}
