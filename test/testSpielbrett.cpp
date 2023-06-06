#include <gtest/gtest.h>
#include <iostream>
#include <../src/Spieler.cpp>
#include <../src/Spielbrett.cpp>


using namespace vierGewinnt;

TEST (Spielbrett, setPlayer()){
    Spielbrett board;
    Spieler player("Lukas", "LU")
    board.setPlayer(player)
    EXPECT_EQ(getPlayer().getSymbol, "Lukas");
}

TEST (Spielbrett,setPlayer)