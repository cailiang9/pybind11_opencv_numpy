/*
<%
setup_pybind11(cfg)
cfg['sources'] = 'ndarray_converter.cpp'.split()
cfg['compiler_args'] = '-std=c++14 -flto -O3 -fomit-frame-pointer -ffast-math -Wall -fPIC -D__USE_FILE_OFFSET64 -D__USE_LARGEFILE'.split()
#cfg['parallel'] = True
cfg['linker_args'] = '-O3 -Wall'.split()
cfg['libraries'] = 'opencv_core opencv_imgproc opencv_imgcodecs opencv_video opencv_videoio opencv_objdetect m z'.split()
#cfg['include_dirs'] = ['...']
%>
*/
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <tuple>
#include "ndarray_converter.h"

namespace py = pybind11;
using namespace std;
auto testtup(int x) {
    return std::make_tuple(cv::Mat1f(x,x,.0f),cv::Mat3b(x,x,128));
}

auto testmat(int x) {
    return cv::Mat1f(x,x,.0f);
}

vector<vector<string> > testvstr(int x) {
    vector<vector<string> > vs;
    for (auto i = 0; i < x; ++i)
        vs.push_back(vector<string>(x, "stra"));
    return vs;
}

PYBIND11_PLUGIN(cpy) {
    NDArrayConverter::init_numpy();
    pybind11::module m("cpy", "auto-compiled c++ extension");
    m.def("testmat", &testmat);
    m.def("testvstr", &testvstr);
    m.def("testtup", &testtup);
    return m.ptr();
}