#include "../include/Spielbrett.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace vierGewinnt;


PYBIND11_MODULE(vierGewinnt, m) {
  m.doc() = "Spiel von Aicha, Imene und Lukas";
  
  py::class_<Spielbrett>(m, "Spielbrett")
    .def(py::init<>())
    .def("setRing", &Spielbrett::setRing)
    .def("legalMove", &Spielbrett::whoIsWinning)
    .def("setPlayer", &Spielbrett::setPlayer)
    .def("print", &Spielbrett::print);
}

