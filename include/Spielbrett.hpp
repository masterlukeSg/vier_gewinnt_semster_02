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
        std::vector<std::string> reihenName, eins, zwei, drei, vier, fuenf, sechs, sieben;

        /**
         * @brief Breite: 7, Höhe: 6
         */
        std::vector<std::vector<std::string>> matrixBoard{reihenName, eins, zwei, drei, vier, fuenf, sechs, sieben};
        bool legalMove(int Position);

    public:
        Spielbrett();
        void whoIsWinning();

        void setRing(int Position);
        std::string print();
    };
}