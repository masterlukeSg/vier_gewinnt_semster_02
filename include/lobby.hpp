#pragma once

#include <iostream>
#include <vector>
#include "Spieler.hpp"
#include "Spielbrett.hpp"

namespace vierGewinnt
{
    class Lobby
    {
    public:
        Lobby(); 

        Spieler createNewPlayer(std::string name1, std::string symbol1);

        Spielbrett createNewGame();
    };
}
