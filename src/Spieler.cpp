#include "../include/Spieler.hpp"
#include <iostream>
#include <string>

namespace vierGewinnt
{

    Spieler::Spieler(std::string name_)
    {   
        name = name_;
    }
    
    std::string Spieler::Spieler::getName()
    {
        return name;
    }
}