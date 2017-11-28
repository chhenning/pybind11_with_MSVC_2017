
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

void init_simple(py::module& m)
{
    // define a function with two named parameter and default values.
    m.def("add", &add, "A function which adds two numbers", py::arg("i") = 1, py::arg("j") = 5);
}

///////////////////

// py::args derives from py::tuple
// py::kwargs derives from py::dict
void test_args(py::args args, py::kwargs kwargs)
{
	std::cout << "inside test_args" << std::endl;
	if(kwargs)
	{
		
	}
}

void init_test_args(py::module& m)
{
    // define a function with two named parameter and default values.
    m.def("test_args", &test_args, "A function which adds two numbers");
}

////////////////////////////

// Operator Overloading
class Vector2 {
public:
    Vector2(float x, float y) : x(x), y(y) { }

    Vector2 operator+(const Vector2 &v) const { return Vector2(x + v.x, y + v.y); }
    Vector2 operator*(float value) const { return Vector2(x * value, y * value); }
    Vector2& operator+=(const Vector2 &v) { x += v.x; y += v.y; return *this; }
    Vector2& operator*=(float v) { x *= v; y *= v; return *this; }

    friend Vector2 operator*(float f, const Vector2 &v) {
        return Vector2(f * v.x, f * v.y);
    }

    std::string toString() const {
        return "[" + std::to_string(x) + ", " + std::to_string(y) + "]";
    }
	
	float get_x() const { return x; }
	float get_y() const { return y; }
	
private:
    float x, y;
};

void init_vector_class(py::module& m)
{
// >>> import pickle
// >>> import py_ext
// >>> v = py_ext.Vector2(1,2)
// >>> data = pickle.dumps(v,2)
// >>> data
// b'\x80\x02cpy_ext\nVector2\nq\x00)\x81q\x01G?\xf0\x00\x00\x00\x00\x00\x00G@\x00\x00\x00\x00\x00\x00\x00\x86q\x02b.'

	py::class_<Vector2>(m, "Vector2")
		.def(py::init<float, float>())
		.def(py::self + py::self)
		.def(py::self += py::self)
		.def(py::self *= float())
		.def(float() * py::self)
		.def(py::self * float())
		.def("__repr__", &Vector2::toString)
		// enable python's pickle
		.def(py::pickle( 
			[](const Vector2& v) // __getstate__
			{
				return py::make_tuple(v.get_x(), v.get_y());
			},
			[](py::tuple t) // __setstate__
			{
				if(t.size() != 2)
				{
					throw std::runtime_error("Invalid state!");
				}
				
				Vector2 v(t[0].cast<float>(), t[1].cast<float>());
				return v;
			}))
			;
}


PYBIND11_MODULE(py_ext, m)
{
    m.doc() = "example plugin"; // optional module docstring
    
    init_simple(m);

	init_vector_class(m);
}
