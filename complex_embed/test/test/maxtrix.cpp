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

/*
A very generic matrix class
*/
class Matrix {
public:
    Matrix(size_t rows, size_t cols)
        : m_rows(rows), m_cols(cols)
    {
        m_vec = std::vector<float>(rows * cols, 12.f);
    }

    float *data() { return &m_vec.front(); }
    size_t rows() const { return m_rows; }
    size_t cols() const { return m_cols; }

    float sum() const
    {
        return std::accumulate(m_vec.begin(), m_vec.end(), 0.f);
    }

private:
    size_t m_rows, m_cols;
    std::vector<float> m_vec;
};


void init_chh_matrix(py::module& m)
{
    py::class_<Matrix> PyMatrix(m, "Matrix", py::buffer_protocol());
    PyMatrix.def(py::init<size_t, size_t>());

    // create matrix from numpy array using buffer protocol
    PyMatrix.def(py::init([](py::buffer b)
    {
        // request a buffer descriptor from python
        py::buffer_info info = b.request();

        if (info.format != py::format_descriptor<float>::format())
        {
            throw std::runtime_error("Incompatible format: expected a float array!");
        }

        if (info.ndim != 2)
        {
            throw std::runtime_error("Incompatible buffer dimension!");
        }

        std::unique_ptr<Matrix> M = std::make_unique<Matrix>(info.shape[0], info.shape[1]);
        std::memcpy(M->data(), static_cast<float*>(info.ptr), info.shape[0] * info.shape[1] * sizeof(float));

        return M;
    }));


    // according to Python's buffer protocol specification
    PyMatrix.def_buffer([](Matrix &m) -> py::buffer_info {
        return py::buffer_info(
            m.data(),                               /* Pointer to buffer */
            sizeof(float),                          /* Size of one scalar */
            py::format_descriptor<float>::format(), /* Python struct-style format descriptor */
            2,                                      /* Number of dimensions */
            { m.rows(), m.cols() },                 /* Buffer dimensions */
            { sizeof(float) * m.cols(),             /* Strides (in bytes) for each index */
            sizeof(float) }
        );
    });

    PyMatrix.def("sum", &Matrix::sum);

    PyMatrix.def(py::pickle(
        [](const Matrix& a) -> std::string
    {
        // __getstate__
        return std::string("Hello World.");
    },
        [](const std::string& str ) -> Matrix
    {
        py::scoped_ostream_redirect stream(
            std::cout,                               // std::ostream&
            py::module::import("sys").attr("stdout") // Python output
        );

        std::cout << "Loading matrix from string" << std::endl;

        // __setstate__

        return Matrix(10,10);
    }
    ));
}



PYBIND11_EMBEDDED_MODULE(chh, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    init_chh_matrix(m);
}

