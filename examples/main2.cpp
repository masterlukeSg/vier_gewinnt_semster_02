#include <iostream>
#include <string>
#include "../include/lobby.hpp"

using namespace vierGewinnt;

int main()
{

    vierGewinnt::Lobby spiel1 = vierGewinnt::Lobby();

    spiel1.createNewPlayer("Lukas", "LU");
    spiel1.createNewGame();
}
