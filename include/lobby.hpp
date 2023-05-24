#include <iostream>
#include <vector>
#include "../include/Spieler.hpp"
#include "../include/Spielbrett.hpp"

namespace vierGewinnt
{
    class Lobby
    {
    private:
        std::vector<Spieler> spielerListe;
        std::vector<Spielbrett> spielListe;

    public:
        void createNewPlayer(const std::string& name, const std::string& symbol_);
        

        void createNewGame(const Spieler& spieler1, const Spieler& spieler2);
        

       
    };
}
