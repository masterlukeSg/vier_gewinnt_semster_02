#include <../include/Spielbrett.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace vierGewinnt;

int main()
{

    vierGewinnt::Spielbrett s = vierGewinnt::Spielbrett("SO", "LU");
    vector liste = {2,3,4,5,6,7,7,7,77,7};

    for (int i = 0; i < liste.size(); i++)
        s.setRing(liste[i]);

    std::cout << s.print(); 
    if (s.whoIsWinning() != "null" || "unentschieden")
        std::cout << s.whoIsWinning() << " hat das Spiel gewonnen!" << std::endl;
}