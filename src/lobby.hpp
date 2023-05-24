#include <iostream>
#include <vector>
#include "../include/Spieler.hpp"
#include "../include/Spielbrett.hpp"
#include "../include/lobby.hpp"

namespace vierGewinnt
{
  
        void createNewPlayer(const std::string& name, const std::string& symbol_)
        {
            Spieler spieler(name, symbol_);
            spielerListe.push_back(spieler);
        }

        void createNewGame(const Spieler& spieler1, const Spieler& spieler2)
        {
            Spielbrett spielbrett(spieler1.getSymbol(), spieler2.getSymbol());
            spielListe.push_back(spielbrett);
        }

       
}  
