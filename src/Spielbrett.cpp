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
        ring = player.getSymbol();
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

        // untschieden

        if (matrix == 0 && position == 0)
            return "null";

        int matrixBoardGroeße, counter, trys = 0;

        for (size_t i = 1; i < matrixBoard.size(); i++)
            if (matrixBoard[i].size() == 6)
                matrixBoardGroeße++;

        if (matrixBoardGroeße == 7)
            return unentschieden;
        else if (matrixBoardGroeße == 0)
            return "null";

        // vertikal untersuchen

        for (size_t i = 1; i < matrixBoard.size(); i++)
        {
            for (string names : matrixBoard[i])
            {
                if (names == ring)
                    counter++;

                else
                    counter = 0;
            }

            if (counter == 4)
                return ring;

            counter = 0;
        }

        // horizontal untersuchen
        counter = 0;
        while (trys < 7)
        {
            for (int i = 0; i < matrixBoard.size(); i++)
            {
                // TODO: Klappt diese Abfrage ??
                if (matrixBoard[i].size() > trys)
                {
                    if (matrixBoard[i][trys] == ring)
                        counter++;

                    else
                        counter = 0;
                }
            }

            if (counter == 4)
                return ring;
            counter = 0;
            trys++;
        }

        auto getPosition = getGesetzterRingPosition();

        const int matrixInt = std::get<0>(getPosition);
        int positionInt = std::get<1>(getPosition);

        int board = std::get<0>(getPosition);
        int coordinateInBoard = std::get<1>(getPosition);
        // 4 trys:
        // 0->1: rechts oben, bis man auf was "flasches stoßt" + 1->2 links unten. Danach counter reseten
        // 2->3: links oben + 3->4 rechts unten. Danach counter reseten

        trys = 0;
        bool goOn = true;
        std::vector<string> boardAndCoordinateVector;
        bool alreadyCounted = false;

        while (trys != 4)
        {
            for (int i = 0; i < matrixBoard[board].size(); i++)
            {
                // Abfragen stehen hier, damit man nicht zwei mal den Anfangswert "matrixBoard[board][coordiate]" abfragt und somit doppelt den couter zählen lässt

                // Trysabfrage
                if (trys == 1 && board > 2 && coordinateInBoard > 0)
                {
                    coordinateInBoard--;
                    board--;
                }

                else if (trys == 3 && board < 7 && coordinateInBoard > 0)
                {
                    coordinateInBoard--;
                    board++;
                }

                // Koordinaten gespeichert werden und am Ende wird gezählt
                for (string s : boardAndCoordinateVector)
                {
                    if (s == to_string(board) + to_string(coordinateInBoard))
                        alreadyCounted = true;
                }

                // Richtige Abfrage
                if (matrixBoard[board].size() > coordinateInBoard && coordinateInBoard >= 0 && !alreadyCounted)
                {
                    if (matrixBoard[board][coordinateInBoard] == ring)
                    {
                        boardAndCoordinateVector.push_back(to_string(board) + to_string(coordinateInBoard));
                        alreadyCounted = false;
                    }

                    else
                        goOn = false;
                }

                // Trysabfrage
                if (trys == 0 && board < 7)
                {
                    coordinateInBoard++;
                    board++;
                }
                else if (trys == 2 && board > 2)
                {
                    coordinateInBoard++;
                    board--;
                }

                if (boardAndCoordinateVector.size() == 4)
                    return ring;
            }

            trys++;
            board = matrixInt;
            coordinateInBoard = position;
            goOn = true;
            alreadyCounted = false;

            if (trys == 2)
                boardAndCoordinateVector.clear();
        }

        for (string s : boardAndCoordinateVector)
            std::cout << s << std::endl;

        return "null";
    }
}