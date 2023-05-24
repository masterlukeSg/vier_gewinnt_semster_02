#pragma once

#include <string>
#include <iostream>
namespace vierGewinnt
{
    class Spieler
    {
    private:
        std::string name;

    public:
        Spieler(std::string name_);
        
        std::string getName();
    };
}