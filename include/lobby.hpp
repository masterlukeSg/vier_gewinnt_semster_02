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
        //std::vector<Spieler> spielerListe;
        //std::vector<Spielbrett> spielListe;
        Spieler spieler;

    public:

        Lobby();

        void createNewPlayer(std::string name1, std::string symbol1);
        

        Spielbrett createNewGame();
        

       
    };
}
