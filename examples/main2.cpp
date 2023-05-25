#include <iostream>
#include <string>
#include "../include/Lobby.hpp"

using namespace vierGewinnt;

int main()
{

    vierGewinnt::Lobby spiel1 = vierGewinnt::Lobby();

   Spieler s =  spiel1.createNewPlayer("Lukas", "LU");
    spiel1.createNewGame();

    std::cout << s.getName() << std::endl;
}
