#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace vierGewinnt
{
    class Spielbrett
    {
    private:
        std::string ringOne,ringTwo;
        std::vector<std::string> spaltenName, eins, zwei, drei, vier, fuenf, sechs, sieben;

        /**
         * @brief Breite: 7, Höhe: 6
         */
        std::vector<std::vector<std::string>> matrixBoard{spaltenName, eins, zwei, drei, vier, fuenf, sechs, sieben};
        bool legalMove(int Position);

    public:
        Spielbrett(std::string ringOne_,std::string ringTwo_);
        void whoIsWinning();
        void setRing(int Position);
        std::string print();
    };
}