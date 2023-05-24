#include "../include/Spieler.hpp"
#include "../include/Spielbrett.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <tuple>

// cmake -S . -B build && cmake --build build && cmake --install build

using namespace std;

namespace vierGewinnt
{

    Spielbrett::Spielbrett() : unentschieden("unentschieden")
    {

        vector spaltenName = matrixBoard[0];

        for (int i = 0; i < 7; i++)
            spaltenName.push_back("0" + to_string(i + 1));

        matrixBoard[0] = spaltenName;
    }

    void Spielbrett::setPlayer(vierGewinnt::Spieler player)
    {
        ring = player.getName();
    }

    string Spielbrett::print()
    {
        string returnString;
        vector<string> returnStringV;

        for (string d : matrixBoard[0])
            returnString = returnString + (d + " ");

        int d = 0;
        while (d < 6)
        {
            for (int i = matrixBoard.size() - 1; i >= 1; i--)
            {
                if (matrixBoard[i].size() > d)
                    returnStringV.push_back(matrixBoard[i][d] + " ");
                else
                    returnStringV.push_back("-- ");
            }
            returnStringV.push_back("\n");
            d++;
        }

        for (int i = returnStringV.size() - 1; i >= 0; i--)
            returnString = returnString + returnStringV[i];

        returnString = returnString + "\n";
        return returnString;
    }

    bool Spielbrett::legalMove(int position)
    {
        if (ring == "null")
            return false;
        if (position > 7)
            return false;
        else if (position <= 0)
            return false;
        else if (matrixBoard[position].size() == 6)
            return false;

        return true;
    }

    bool Spielbrett::setRing(int coordinate)
    {
        if (!legalMove(coordinate))
        {
            cout << "In die Reihe " << coordinate << " kann nichts eingefügt werden" << endl;
            return false;
        }

        matrixBoard[coordinate].push_back(ring);

        // für getGesetzterRingPosition Variablen
        matrix = coordinate;
        position = matrixBoard[coordinate].size() - 1;

        return true;
    }

    std::tuple<int, int> Spielbrett::getGesetzterRingPosition()
    {
        return std::tuple<int, int>{matrix, position};
    }

    std::string Spielbrett::whoIsWinning()
    {

        // vertikal untersuchen
        int counter = 0;

        for (size_t i = 1; i < matrixBoard.size(); i++)
        {
            for (string names : matrixBoard[i])
            {
                if (names == ring)
                {
                    counter++;
                }
                else
                {
                    counter = 0;
                }
            }

            if (counter >= 4)
                return ring;
            counter = 0;
        }

        // horizontal untersuchen
        counter = 0;
        int d = 0;
        while (d < 7)
        {
            for (int i = 0; i < matrixBoard.size(); i++)
            {
                // TODO: Klappt diese Abfrage ??
                if (matrixBoard[i].size() > d)
                {
                    if (matrixBoard[i][d] == ring)
                        counter++;

                    else
                        counter = 0;
                }
            }
            if (counter >= 4)
                return ring;
            counter = 0;
            d++;
        }

        // braucht man das eigentlich???
        auto getPosition = getGesetzterRingPosition();

        int matrixInt = std::get<0>(getPosition);
        int positionInt = std::get<1>(getPosition);

        counter = 0;
        // positionInt soll man bearbeiten können. position nicht
        positionInt = position;

        // diagonal untersuchen
        if (position == 0 || position == 5)
        {
            // erster Try ueberprueft die diagonale nach rechts und die zweite nach links
            int trys = 0;
            while (trys != 2)
            {
                // durch "i++" wird, wenn unten nicht i-2, nach rechts oben die diagonale ueberprueft
                for (int i = matrix; i < matrixBoard.size(); i++)
                {
                    // gitb es im Array überhaupt ein Element, dass in unserer Range liegt
                    if (matrixBoard[i].size() > positionInt)
                    {
                        // Ite Matrix am Punkt positionInt checken, ob Ring ist: counter erhöhen
                        if (matrixBoard[i][positionInt] == ring)
                            counter++;
                        // Wenn anderer Spieler, dann counter auf null setzten
                        else
                            counter = 0;
                    }

                    // wenn letzter eingesetzter Wert beim Array Vier oder
                    if (matrix >= 4 && trys == 1)
                        i = i - 2;

                    // positionInt proportional zum nächsten Array erhöhre. Somit geht man die (rechte/line) Diagonale ab
                    // abfrage position, weil positionInt bearbietet wird
                    if (position == 0)
                        positionInt++;

                    // positionInt proportional zum nächsten Array verringert. Somit geht man die (rechte/line) Diagonale ab
                    else if (position == 5)
                        positionInt--;

                    // wenn counter größer gleich 4, ist das Spiel zuende und ring spieler hat gewonnen
                    if (counter >= 4)
                        return ring;
                }
                trys++;
                // reset: positionInt muss wieder auf position gesetzt werden. Jetz wird Links diagonal ueberprueft
                positionInt = position;
                counter = 0;
            }
        }

        else
        {
        }

        int matrixBoardGroeße = 0;
        for (size_t i = 1; i < matrixBoard.size(); i++)
            if (matrixBoard[i].size() == 6)
                matrixBoardGroeße++;

        if (matrixBoardGroeße == 7)
            return unentschieden;
        else
            return "null";
    }
}