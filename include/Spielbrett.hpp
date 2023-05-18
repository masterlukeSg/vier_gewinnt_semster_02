#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace vierGewinnt
{
    class Spielbrett
    {
    private:
        int ringOne;
        int ringTwo;
        
        /**
         * @brief Breite: 7, Höhe: 6 
         */
        int matrixBoard[7][6];

    public:
        Spielbrett();
        void whoIsWinning();
        bool legalMove(int Position);
        void setRing(int Position);
        std::string print();
    };
}