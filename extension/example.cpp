#include <pybind11/pybind11.h>

namespace py = pybind11;

////////////////////////

int add(int i, int j) {
    return i + j;
}

void init_simple(py::module& m)
{
    // define a function with two named parameter and default values.
    m.def("add", &add, "A function which adds two numbers", py::arg("i") = 1, py::arg("j") = 5);
    
    // exporting a variable
    m.attr("the_answer") = 42;

    // export a std::string
    std::string world("Hello World!");
    py::object py_world = py::cast(world);
    m.attr("what") = world;    
}


////////////////////////

struct Pet {
    enum Kind {
        Dog = 0,
        Cat
    };

    Pet(const std::string &name, Kind k) : name(name), type(k) { }
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }

    std::string name;
    Kind type;
};

void init_pet(py::module m)
{
    py::class_<Pet> pet(m, "Pet");

    pet.def(py::init<const std::string&, Pet::Kind>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName)
        .def("__repr__", [](const Pet& p) { return "<example.Pet named '" + p.getName() + " " + ((p.type == Pet::Kind::Dog)? "Dog" : "Cat") + "'>"; })
        .def_readwrite("name", &Pet::name)
        .def_readwrite("type", &Pet::type)
        //.def_readwrite("type", &Pet::type)
        // in case name is private use field-like interface using getter and setter functions. Use nullptr if one of them is not available
        //.def_property("name", &Pet::getName, &Pet::setName)
        ;
        
    // adding dynamic attribute (python feature) -- http://pybind11.readthedocs.io/en/master/classes.html#dynamic-attributes
    //py::class_<Pet>(m, "Pet", py::dynamic_attr())
    // python it should look like:
    // >>> p.age = 2  # OK, dynamically add a new attribute
    // >>> p.__dict__  # just like a native Python class
    // {'age': 2}
        
    // Inheritance and automatic upcasting -- http://pybind11.readthedocs.io/en/master/classes.html#inheritance-and-automatic-upcasting
    
    // Overloaded methods -- http://pybind11.readthedocs.io/en/master/classes.html#overloaded-methods
    // py::class_<Pet>(m, "Pet")
    //    .def(py::init<const std::string &, int>())
    //    .def("set", (void (Pet::*)(int)) &Pet::set, "Set the pet's age")
    //    .def("set", (void (Pet::*)(const std::string &)) &Pet::set, "Set the pet's name");    
    // 
    // Use help(example.Pet) to find all information about Pet

    // can be inquired by __members__
    py::enum_<Pet::Kind>(pet, "Kind")
        .value("Dog", Pet::Kind::Dog)
        .value("Cat", Pet::Kind::Cat)
        .export_values();
}

//////////////////////


PYBIND11_MODULE(example, m)
{
    m.doc() = "example plugin"; // optional module docstring
    
    init_simple(m);
    init_pet(m);
}