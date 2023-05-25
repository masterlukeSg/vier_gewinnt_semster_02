#pragma once

#include <iostream>
#include <vector>
#include "Spieler.hpp"
#include "Spielbrett.hpp"

namespace vierGewinnt
{
    class Lobby
    {
    private:
        //std::vector<Spieler> spielerListe;
        //std::vector<Spielbrett> spielListe;
        Spieler spieler;

    public:

        Lobby();

        void createNewPlayer(std::string name, std::string symbol);
        

        Spielbrett createNewGame();
        

       
    };
}
