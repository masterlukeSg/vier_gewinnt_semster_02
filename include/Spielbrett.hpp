#pragma once

#include "Spieler.hpp"
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <string>
#include <vector>

namespace vierGewinnt
{
    class Spielbrett
    {
    private:
        int matrix, position;
        std::string ring, unentschieden;
        std::vector<std::string> spaltenName, eins, zwei, drei, vier, fuenf, sechs, sieben;
        /**
         * @brief Breite: 7, Höhe: 6
         */
        std::vector<std::vector<std::string>> matrixBoard{spaltenName, eins, zwei, drei, vier, fuenf, sechs, sieben};
        /**
         * @brief Überprüft ob man den Ring an der Position platzieren darf
         *
         * @param Position
         * @return true
         * @return false
         */
        bool legalMove(int Position);
        std::tuple<int, int> getGesetzterRingPosition();

    public:
        /**
         * @brief Erstellt neues Spielbrettobjekt und fügt die Spaltennamen hinzu
         */
        Spielbrett();
        /**
         * @brief Überprüft ob ein Spieler 4 Ringe horizontal,vertikal oder diagonal platziert hat
         * @return Gewinner des Spiels
         */
        std::string whoIsWinning();
        /**
         * @brief Setzt Ring auf Namen des aktuellen Spieler
         *
         * @param player
         */
        void setPlayer(Spieler player);
        /**
         * @brief Übergibt dem legalMove fkt die Position und setzt es danach an die gewünschte Position
         *
         * @param Position
         * @return Position erlaubt (true) oder nicht (false)
         */

        Spieler getPlayer();


        bool setRing(int Position);
        /**
         * @brief Gibt das Spielbrett wieder
         *
         * @return Spielbrett
         */
        std::string print();
    };
}