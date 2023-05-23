#include <../include/Spielbrett.hpp>
#include <../include/Spieler.hpp>

#include <iostream>
#include <string>

using namespace std;
using namespace vierGewinnt;

int main()
{

    vierGewinnt::Spielbrett s = vierGewinnt::Spielbrett();
    vierGewinnt::Spieler lukas = vierGewinnt::Spieler("LU");
    vierGewinnt::Spieler ki = vierGewinnt::Spieler("KI");
    

    s.setPlayer(lukas);
    
    vector liste = {2, 3, 4, 5, 3, 3, 3};

    for (int i = 0; i < liste.size(); i++)
        s.setRing(liste[i]);

    std::cout << s.print();

    std::cout << s.whoIsWinning() << " hat das Spiel gewonnen!" << std::endl;
}