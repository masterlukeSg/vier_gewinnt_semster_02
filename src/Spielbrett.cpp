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

        for (int i = 0; i < 7; i++)
            spaltenName.push_back("0" + to_string(i + 1));

        matrixBoard[0] = spaltenName;

        // Probe: wird vom nutzer gemacht!
        matrixBoard[1].push_back(ringOne);
        matrixBoard[1].push_back(ringOne);
        matrixBoard[1].push_back(ringOne);

        matrixBoard[2].push_back(ringTwo);

        matrixBoard[3].push_back(ringOne);
        matrixBoard[3].push_back(ringOne);
        matrixBoard[3].push_back(ringOne);

        matrixBoard[7].push_back(ringTwo);
        matrixBoard[7].push_back(ringOne);
        matrixBoard[7].push_back(ringTwo);

        // for (int i = 1; i < matrixBoard.size(); i++)
        //     for (int y = 0; y < 6; y++)
        //         matrixBoard[i].push_back("--");
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
                    returnStringV.push_back(matrixBoard[i][d]);
                else
                    returnStringV.push_back("-- ");
            }
            returnStringV.push_back("\n");
            d++;
        }

        for (int i = returnStringV.size() - 1; i >= 0; i--)
            returnString = returnString + returnStringV[i];
    
        return returnString;
    }

}