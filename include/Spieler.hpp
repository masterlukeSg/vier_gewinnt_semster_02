#include <string>
#include <iostream>

namespace vierGewinnt {

class Spieler
{
private:
std::string name;

public:
/**
 * @brief Spieler()
 *Construct a new Spieler object 
 * @param name 
 */
Spieler(std::string name);
/**
 * @brief getName()
 * Gets the Name object
 * @return std::string 
 */
std::string getName();


};
} 