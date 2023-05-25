#include "../include/Spieler.hpp"
#include <iostream>
#include <string>

namespace vierGewinnt{
/**
 * @brief Spieler()
 * Konstruktor - settet einen namen
 * @param name_ 
 */
    Spieler::Spieler(std::string name_){
        name=name_ ;
    }
/**
 * @brief getName()
 * gibt den NAmen des Spielers zurueck
 * @return std::string 
 */
    std::string Spieler::getName(){
    return name;
}
}