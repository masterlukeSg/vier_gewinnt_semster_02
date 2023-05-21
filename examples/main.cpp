#include <../include/Spielbrett.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace vierGewinnt;


int main(){


    vierGewinnt::Spielbrett s = vierGewinnt::Spielbrett("SO ", "LU ");

    std::cout << s.print();
}