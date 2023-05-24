#include "../include/Spieler.hpp"
#include <iostream>
#include <string>


namespace vierGewinnt
{
    
        Spieler(const std::string& name_, const std::string& symbol_)
            : name(name_), symbol(symbol_) {}

        std::string getName() const
        {
            return name;
        }

        std::string getSymbol() const
        {
            return symbol;
        }

        
    
}
