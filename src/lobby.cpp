#include <iostream>
#include <vector>
#include "../include/Spieler.hpp"
#include "../include/Spielbrett.hpp"
#include "../include/lobby.hpp"



namespace vierGewinnt
{
        

        Lobby::Lobby(){
          
        }
        void Lobby::createNewPlayer(std::string name1, std::string symbol1)
        {
            spieler = Spieler(name1, symbol1);

            //spielerListe.push_back(spieler);
        }

        Spielbrett Lobby::createNewGame()
        {
            Spielbrett spielbrett= Spielbrett();
            return spielbrett;
            //spielListe.push_back(spielbrett);
        }

       
}  
