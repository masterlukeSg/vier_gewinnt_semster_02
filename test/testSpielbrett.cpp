
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include "../src/Spieler.cpp"
#include "../src/Spielbrett.cpp"

// cmake -S . -B build && cmake --build build

using namespace vierGewinnt;

TEST(Spielbrett, setRing)
{
    Spielbrett board = Spielbrett();
    Spieler player = Spieler("Lukas", "LU");
    board.setPlayer(player);
    EXPECT_EQ(board.setRing(4), true);
}

TEST(Spielbrett, whoIsWinning)
{
    Spielbrett board = Spielbrett();
    Spieler player = Spieler("Lukas", "LU");
    board.setPlayer(player);
    std::vector<int> list = {1, 2, 3, 4};
    for (int f : list)
        board.setRing(f);
    EXPECT_EQ(board.whoIsWinning(), "LU") << "Gewinner wurde nicht richtig erkannt";
}
