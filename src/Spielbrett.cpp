#include "../include/Spielbrett.hpp"
#include <iostream>
#include <string>
#include <vector>

// cmake -S . -B build && cmake --build build && cmake --install build

using namespace std;

namespace vierGewinnt
{

    Spielbrett::Spielbrett(string ringOne_, string ringTwo_) : unentschieden("unentschieden"), ringOne(ringOne_), ringTwo(ringTwo_)
    {

        vector spaltenName = matrixBoard[0];

        for (int i = 0; i < 7; i++)
            spaltenName.push_back("0" + to_string(i + 1));

        matrixBoard[0] = spaltenName;
    
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

        // TODO: player->getName();
        matrixBoard[position].push_back(ringOne);
        return true;
    }

    std::string Spielbrett::whoIsWinning()
    {
        int counterOne, counterTwo = 0;

        // vertikal untersuchen
        for (size_t i = 1; i < matrixBoard.size(); i++)
        {
            for (string names : matrixBoard[i])
            {
                if (names == ringOne)
                {
                    counterTwo = 0;
                    counterOne++;

                    std::cout << names << " " << counterOne << std::endl;
                }
                else if (names == ringTwo)
                {
                    counterOne = 0;
                    counterTwo++;

                    std::cout << names << " " << counterTwo << std::endl;
                }
                else
                {
                    if (counterOne >= 4)
                        return ringOne;
                    if (counterTwo >= 4)
                        return ringTwo;
                }
            }
        }
        /*
        // horizontal untersuchen
        counterOne = 0;
        counterTwo = 0;
        int d = 1;
        while (d < 7)
        {
            for (int i = 0; i < matrixBoard.size(); i++)
            {
                // TODO: Klappt diese Abfrage ??
                if (matrixBoard[i].size() > d)
                {
                    if (matrixBoard[i][d] == ringOne)
                    {
                        counterTwo = 0;
                        counterOne++;
                    }
                    else if (matrixBoard[i][d] == ringTwo)
                    {
                        counterOne = 0;
                        counterTwo++;
                    }
                }
            }
            if (counterOne >= 4)
                return ringOne;
            if (counterTwo >= 4)
                return ringTwo;
            counterOne = 0;
            counterTwo = 0;
            d++;
        }
        */
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