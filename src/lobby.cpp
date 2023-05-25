#include <iostream>
#include <vector>
#include "../include/Spieler.hpp"
#include "../include/Spielbrett.hpp"
#include "../include/lobby.hpp"

namespace vierGewinnt
{
    Lobby::Lobby()
    {
    }

    void Lobby::createNewPlayer(std::string name, std::string symbol_)
    {
        Spieler spieler = Spieler(name, symbol_);
    }

    Spielbrett Lobby::createNewGame()
    {
        Spielbrett spielbrett = Spielbrett();
        return spielbrett;
    }

}
