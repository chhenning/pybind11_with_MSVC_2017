#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <numeric>
#include <vector>

#include <pybind11\pybind11.h>
#include <pybind11\embed.h>
#include <pybind11\iostream.h>
#include <pybind11\stl.h>

namespace py = pybind11;

class SpatialPooler
{
public:

    SpatialPooler()
    {
        std::cout << "Default constructor" << std::endl;
    }

    SpatialPooler(std::vector<unsigned int> inputDimensions
        , unsigned int potentialRadius = 16, float potentialPct = 0.5)
    {
        std::cout << "Custom constructor" << std::endl;
        std::cout << inputDimensions[0] << std::endl;
        std::cout << inputDimensions[1] << std::endl;
        
        std::cout << potentialRadius << std::endl;
        std::cout << potentialPct << std::endl;
    }
};

PYBIND11_EMBEDDED_MODULE(spatial_pooler, m)
{
    py::class_<SpatialPooler> py_SpatialPooler(m, "SpatialPooler");

    py_SpatialPooler.def(py::init());

    py_SpatialPooler.def(py::init<std::vector<unsigned int>, unsigned int, float>()
        , py::arg("inputDimensions") = std::vector<unsigned int>({32, 32}), py::arg("potentialRadius") = 16, py::arg("potentialPct") = 0.5);
}


void test_module()
{
    py::scoped_interpreter guard{};
    auto spatial_pooler_module = py::module::import("spatial_pooler");

    try
    {
        py::exec(R"(
            from spatial_pooler import SpatialPooler
            a = SpatialPooler()
            b = SpatialPooler((1,2))
            c = SpatialPooler(potentialPct = 1.5, inputDimensions=(1,2))
            d = SpatialPooler(potentialPct = 1.5) # use inputDimensions default vector
        )");
    }
    catch (const py::error_already_set& e)
    {
        std::cout << e.what() << std::endl;
    }
}