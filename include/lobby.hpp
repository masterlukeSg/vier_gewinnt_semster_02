#include <iostream>
#include <vector>
#include "../include/Spieler.hpp"
#include "../include/Spielbrett.hpp"

namespace vierGewinnt
{
    class Lobby
    {
    private:

    public:
        Lobby();
        void createNewPlayer(std::string name,  std::string symbol_);

        Spielbrett createNewGame();
        

       
    };
}
