#include "../include/Spielbrett.hpp"
#include "../include/Spieler.hpp"
#include "../include/lobby.hpp"

#include <string>
#include <pybind11/pybind11.h>

namespace py = pybind11;
using namespace vierGewinnt;

PYBIND11_MODULE(vierGewinnt, m)
{

  m.doc() = "Spiel von Aicha, Imene und Lukas";

  py::class_<Lobby>(m, "Lobby")
      .def(py::init<>())
      .def("createNewPlayer", &Lobby::createNewPlayer)
      .def("createNewGame", &Lobby::createNewGame);

  py::class_<Spieler>(m, "Spieler")
      .def(py::init<std::string, std::string>())
      .def("getName", &Spieler::getName)
      .def("getSymbol", &Spieler::getSymbol);

  py::class_<Spielbrett>(m, "Spielbrett")
      .def(py::init<>())
      .def("setRing", &Spielbrett::setRing)
      .def("legalMove", &Spielbrett::whoIsWinning)
      .def("setPlayer", &Spielbrett::setPlayer)
      .def("print", &Spielbrett::print);
}
