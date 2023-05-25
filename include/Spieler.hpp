#pragma once

#include <string>
#include <iostream>

namespace vierGewinnt
{
    class Spieler
    {
    private:
        std::string name;
        std::string symbol;

    public:
        
        Spieler(std::string name_,  std::string symbol_)
            : name(name_), symbol(symbol_) {}

        std::string getName() const;

        std::string getSymbol() const;
        

    };
}