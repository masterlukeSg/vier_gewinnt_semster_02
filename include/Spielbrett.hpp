#pragma once

#include "Spieler.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace vierGewinnt
{
    class Spielbrett
    {
    private:
        std::string ringOne, ringTwo, unentschieden;
        std::vector<std::string> spaltenName, eins, zwei, drei, vier, fuenf, sechs, sieben;

        /**
         * @brief Breite: 7, Höhe: 6
         */
        std::vector<std::vector<std::string>> matrixBoard{spaltenName, eins, zwei, drei, vier, fuenf, sechs, sieben};
        bool legalMove(int Position);

    public:
        Spielbrett();
        std::string whoIsWinning();
        void setPlayer(Spieler player);
        bool setRing(int Position);
        std::string print();
    };
}