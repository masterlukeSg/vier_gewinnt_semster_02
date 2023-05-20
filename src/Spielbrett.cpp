#include "../include/Spielbrett.hpp"
#include <iostream>
#include <string>
#include <vector>

// cmake -S . -B build && cmake --build build && cmake --install build

using namespace std;

namespace vierGewinnt
{

    Spielbrett::Spielbrett()
    {
        vector reihenName = matrixBoard[0];

        for (int d = 0; d < 6; d++)
            reihenName.push_back("0" + to_string(d + 1));

        matrixBoard[0] = reihenName;

        for (int i = 1; i < matrixBoard.size(); i++)
            for (int y = 0; y < 6; y++)
                matrixBoard[i].push_back("--");
    }

    string Spielbrett::print()
    {

        for (vector<std::string> p : matrixBoard)
        {
            for (string d : p)
                cout << d << " ";

            cout << "\n";
        }
        return "null";
    }
}