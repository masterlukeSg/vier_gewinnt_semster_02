#include <iostream>
#include <vector>
#include "../include/Spieler.hpp"
#include "../include/Spielbrett.hpp"
#include "../include/lobby.hpp"

namespace vierGewinnt
{
    Lobby::Lobby(){
    }

    Spieler Lobby::createNewPlayer(std::string name, std::string symbol_)
    {
        vierGewinnt::Spieler spieler = vierGewinnt::Spieler(name, symbol_);
        return spieler;
    }

    Spielbrett Lobby::createNewGame()
    {
        Spielbrett spielbrett = Spielbrett();
        return spielbrett;
    }

}
