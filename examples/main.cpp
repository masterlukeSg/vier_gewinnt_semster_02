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
   
    s.setPlayer(ki);
    s.setRing(5);
    s.setPlayer(lukas);

    vector liste = { 2,3, 3, 4,4,4,5,5,5};

    for (int i = 0; i < liste.size(); i++)
        s.setRing(liste[i]);
    s.setPlayer(ki);
    s.setRing(4);
    s.setRing(4);

    s.setPlayer(lukas);
    s.setRing(4);
    s.setRing(4);
    s.setRing(4);
    s.setRing(4);

    std::cout << s.print();

    std::cout << s.whoIsWinning() << " hat das Spiel gewonnen!" << std::endl;
}