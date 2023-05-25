#include <iostream>
#include <string>
#include "../include/lobby.hpp"

using namespace vierGewinnt;

int main()
{

    Lobby spiel1;

    spiel1.createNewPlayers("Lukas", "LU");
    spiel1.createNewGame();
}
