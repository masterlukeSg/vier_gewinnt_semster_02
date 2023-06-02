#include <../include/Spielbrett.hpp>
#include <../include/Spieler.hpp>
#include <../include/lobby.hpp>

#include <iostream>
#include <string>

using namespace std;
using namespace vierGewinnt;

// cmake -S . -B build && cmake --build build && cmake --install build

int main()
{

    vierGewinnt::Spielbrett s = vierGewinnt::Spielbrett();

    vierGewinnt::Spieler lukas = vierGewinnt::Spieler("Lukas", "LU");
    vierGewinnt::Spieler imene = vierGewinnt::Spieler("imene", "KI");

    s.setPlayer(lukas);

    vector<int> liste;

    s.setPlayer(imene);
    // DIAGONAL: test 1: linsk oben nach rechts unten
    liste = {1};

    // DIAGONAL: test 2: rechts oben nach links unten
    liste = {7, 7, 7, 7, 7, 6, 6, 6, 6, 5, 5, 5, 4, 4};

    // DIAGONAL: test 3: links unten nach rechts oben
    liste = {2, 3, 3, 4, 4, 4, 5, 5, 5};

    // DIAGONAL:test 4: rechts unten nach linsk oben
    liste = {6, 5, 5, 4, 4, 3, 3, 3};

    liste = {2, 3, 3, 3, 4, 5, 6, 5, 7, 4, 4, 5,2};

    for (int i = 0; i < liste.size(); i++)
        s.setRing(liste[i]);

    /*
    Ab hier anderer Spieler
    */

    s.setPlayer(lukas);
    // DIAGONAL: test 1: linsk oben nach rechts unten
    // liste = {4, 3, 2, 1};

    // DIAGONAL: test 2: rechts oben nach links unten
    liste = {6, 5, 4, 7};

    // DIAGONAL: test 3: links unten nach rechts oben
    liste = {2, 3, 4, 5, 1};

    // DIAGONAL: test 4: rechts unten nach linsk oben
    liste = {6, 5,3, 4, 7,2,5,5, 4};

    // Horizontal
    // liste = {3, 3, 3, 3};

    // liste = {4,6,7,3,5};

    // vertikal
    // liste = {7,7,7,6,6,5,4};

    for (int i = 0; i < liste.size(); i++)
        s.setRing(liste[i]);

    std::cout << s.print();

    std::cout << s.whoIsWinning() << " hat das Spiel gewonnen!" << std::endl;
}