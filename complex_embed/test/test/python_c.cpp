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


//std::string parse_python_exception()
//{
//    // http://thejosephturner.com/blog/post/embedding-python-in-c-applications-with-boostpython-part-2/
//    // https://stackoverflow.com/questions/37904452/boost-python-throws-exception-while-printing-traceback
//    namespace bp = boost::python;
//
//    std::string ret("Unfetchable Python error");
//
//
//    PyObject* exType;
//    PyObject* value;
//    PyObject* traceBack;
//    PyErr_Fetch(&exType, &value, &traceBack);
//    PyErr_NormalizeException(&exType, &value, &traceBack);
//
//    if (exType != nullptr)
//    {
//        bp::object oExType(bp::handle<>(bp::borrowed(exType)));
//        bp::str type_pstr(oExType);
//
//        auto error_string = std::string(p::extract<char const*>(type_pstr));
//
//        if (error_string.empty() == false)
//            ret = error_string;
//        else
//            ret = "Unknown exception type";
//    }
//
//    if (value != nullptr)
//    {
//        bp::object obj(bp::handle<>(bp::borrowed(value)));
//        bp::str pstr(obj);
//
//        auto error_string = std::string(p::extract<char const*>(pstr));
//
//        if (error_string.empty() == false)
//            ret += ": " + error_string + "\n";
//        else
//            ret += std::string(": Unparseable Python error: ");
//    }
//
//    if (traceBack != nullptr)
//    {
//        bp::object oExType(bp::handle<>(bp::borrowed(exType)));
//        bp::object oValue(bp::handle<>(bp::borrowed(value)));
//        bp::object oTraceBack(bp::handle<>(bp::borrowed(traceBack)));
//
//        bp::object lines = bp::import("traceback").attr("format_exception")(oExType, oValue, oTraceBack);
//
//        std::string result;
//        for (int i = 0; i < len(lines); ++i)
//        {
//            auto pp = lines[i];
//            auto stt = std::string(bp::extract<char const*>(pp));
//
//            ret += stt;
//        }
//    }
//
//
//    PyErr_Restore(exType, value, traceBack);
//
//    return ret;
//}
//
