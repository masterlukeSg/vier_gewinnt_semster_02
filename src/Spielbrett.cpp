#include "../include/Spieler.hpp"
#include "../include/Spielbrett.hpp"
#include <iostream>
#include <string>
#include <vector>

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

    bool Spielbrett::setRing(int position)
    {
        if (!legalMove(position))
        {
            cout << "In die Reihe " << position << " kann nichts eingefügt werden" << endl;
            return false;
        }

        matrixBoard[position].push_back(ring);
        return true;
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

        // diagonal untersuchen
        counter = 0;
        d = 0;
        int f = d;
        while (d < 7)
        {
            for (int i = 1; i < matrixBoard.size(); i++)
            {   
               // std::cout << "I: "  << i << " \n" << "F: " << f << std::endl;
                if (matrixBoard[i].size() > f)
                {   
                    if (matrixBoard[i][f] == ring)
                        counter++;
                    else
                        counter = 0;
                }
                f++;
            }
            f = d;
            d++;
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