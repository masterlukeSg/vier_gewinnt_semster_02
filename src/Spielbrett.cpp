#include "../include/Spielbrett.hpp"
#include <iostream>
#include <string>
#include <vector>

// cmake -S . -B build && cmake --build build && cmake --install build

using namespace std;

namespace vierGewinnt
{

    Spielbrett::Spielbrett(string ringOne_, string ringTwo_)
    {
        ringOne = ringOne_;
        ringTwo = ringTwo_;

        vector spaltenName = matrixBoard[0];

        for (int i = 0; i < 6; i++)
            spaltenName.push_back("0" + to_string(i + 1));
        matrixBoard[0] = spaltenName;
        matrixBoard[2].push_back(ringOne);
        matrixBoard[2].push_back(ringTwo);
        matrixBoard[4].push_back(ringOne);
        matrixBoard[4].push_back(ringOne);

        // for (int i = 1; i < matrixBoard.size(); i++)
        //     for (int y = 0; y < 6; y++)
        //         matrixBoard[i].push_back("--");
    }

    string Spielbrett::print()
    {
        string returnString;

        for (string d : matrixBoard[0])

            returnString = returnString + d + " ";

        returnString = returnString + "\n";

        int d = 0;

        while (d < 7)
        {
            for (int i = 1; i < matrixBoard.size(); i++)
            {
                if (matrixBoard[i].size() > d)
                    returnString = returnString + matrixBoard[i][d];
                else
                    returnString = returnString + "-- ";
            }
            returnString = returnString + "\n";
            d++;
        }

        /*
        for (vector<std::string> p : matrixBoard)
        {
            for (int d = 0; d < 6; d++)
            {
                if (p[d] == ringOne || p[d] == ringTwo)
                    returnString = returnString + (d + " ");
            }
            returnString = returnString + "\n";
        }
        */

        return returnString;
    }

}