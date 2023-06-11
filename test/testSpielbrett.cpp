
#include <gtest/gtest.h>
#include "../src/Spieler.cpp"
#include "../src/Spielbrett.cpp"

using namespace vierGewinnt;

TEST(Spielbrett, setRing)
{
    Spielbrett board = Spielbrett();
    Spieler player = Spieler("Lukas", "LU");
    board.setPlayer(player);
    EXPECT_EQ(board.setRing(4), true);
}
