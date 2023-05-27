#include "../include/Spieler.hpp"
#include <iostream>
#include <string>


namespace vierGewinnt
{
    std::string Spieler::getName() const
    {
        return name;
    }

    std::string Spieler::getSymbol() const
    {
        return symbol;
    }

}
