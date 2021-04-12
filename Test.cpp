/**
 * An example of how to write unit tests.
 * Use this as a basis to build a more complete Test.cpp file.
 * 
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: <Please write your names here>
 * 
 * Date: 2020-02
 */

#include "doctest.h"
#include "Board.hpp"
using namespace ariel;

#include <string>
using namespace std;


TEST_CASE("just a test") {
    Board board;
    CHECK_NOTHROW(board.post(100,200,Direction::Horizontal,"abcd"));
    CHECK_NOTHROW(board.post(0,0,Direction::Horizontal,"abcd"));
    CHECK_NOTHROW(board.post(1500,1500,Direction::Horizontal,"abcd"));
    CHECK_NOTHROW(board.post(2000,2000,Direction::Horizontal,"abcd"));
    CHECK_NOTHROW(board.post(10000,10000,Direction::Horizontal,"abcd"));
}

TEST_CASE("Overwrite test") {
    Board boardTwo;
    CHECK(boardTwo.read(1000000000, 200, Direction::Horizontal, 4) == string("____"));
    boardTwo.post(1000000000, 200, Direction::Horizontal, "abcd");
    CHECK(boardTwo.read(1000000000, 200, Direction::Horizontal, 4) == string("abcd"));
    boardTwo.post(1000000001, 201, Direction::Horizontal, "abcd");
    boardTwo.post(1000000002, 202, Direction::Horizontal, "abcd");
    boardTwo.post(1000000001, 202, Direction::Horizontal, "abcd");
    /* Demo example */
    Board BoardThree;
    BoardThree.post(100, 200, Direction::Horizontal, "abcd");
    CHECK(BoardThree.read(99, 201, Direction::Vertical, 3) == string("_b_"));
	BoardThree.post(99, 202, Direction::Vertical, "xyz");
    CHECK(BoardThree.read(100, 200, Direction::Horizontal, 6) == string("abyd__"));
    /* End Demo example */
}

TEST_CASE("Board expand test") {
    Board ExpandBoard;
    ExpandBoard.post(100, 200, Direction::Horizontal, "abcd");
    // ExpandBoard.show();
    ExpandBoard.post(85, 190, Direction::Horizontal, "abcd");
    CHECK(ExpandBoard.read(84, 190, Direction::Horizontal, 3) == string("___"));
    CHECK(ExpandBoard.read(84, 190, Direction::Vertical, 3) == string("_a_"));
    CHECK(ExpandBoard.read(84, 191, Direction::Horizontal, 3) == string("___"));
    CHECK(ExpandBoard.read(84, 191, Direction::Vertical, 3) == string("_b_"));
    CHECK(ExpandBoard.read(84, 192, Direction::Horizontal, 3) == string("___"));
    CHECK(ExpandBoard.read(84, 192, Direction::Vertical, 3) == string("_c_"));
    CHECK(ExpandBoard.read(84, 193, Direction::Horizontal, 3) == string("___"));
    CHECK(ExpandBoard.read(84, 193, Direction::Vertical, 3) == string("_d_"));
    // ExpandBoard.show();
    ExpandBoard.post(115, 215, Direction::Vertical, "abcd");
    CHECK(ExpandBoard.read(115, 214, Direction::Vertical, 3) == string("___"));
    CHECK(ExpandBoard.read(115, 214, Direction::Horizontal, 3) == string("_a_"));
    CHECK(ExpandBoard.read(116, 214, Direction::Vertical, 3) == string("___"));
    CHECK(ExpandBoard.read(116, 214, Direction::Horizontal, 3) == string("_b_"));
    CHECK(ExpandBoard.read(117, 214, Direction::Vertical, 3) == string("___"));
    CHECK(ExpandBoard.read(117, 214, Direction::Horizontal, 3) == string("_c_"));
    CHECK(ExpandBoard.read(118, 214, Direction::Vertical, 3) == string("___"));
    CHECK(ExpandBoard.read(118, 214, Direction::Horizontal, 3) == string("_d_"));
    // ExpandBoard.show();
}

TEST_CASE("Edges test") {
    Board BoardFour;
    BoardFour.post(4294967294, 4294967294, Direction::Horizontal, "T");
    BoardFour.post(4294967293, 4294967293, Direction::Horizontal, "C");
    BoardFour.post(4294967292, 4294967292, Direction::Horizontal, "E");
    BoardFour.post(4294967291, 4294967291, Direction::Horizontal, "F");
    BoardFour.post(4294967290, 4294967290, Direction::Horizontal, "R");
    BoardFour.post(4294967289, 4294967289, Direction::Horizontal, "E");
    BoardFour.post(4294967288, 4294967288, Direction::Horizontal, "P");
    CHECK(BoardFour.read(4294967288, 4294967288, Direction::Vertical, 7) == string("P______"));
    CHECK(BoardFour.read(4294967288, 4294967289, Direction::Vertical, 7) == string("_E_____"));
    CHECK(BoardFour.read(4294967288, 4294967290, Direction::Vertical, 7) == string("__R____"));
    CHECK(BoardFour.read(4294967288, 4294967291, Direction::Vertical, 7) == string("___F___"));
    CHECK(BoardFour.read(4294967288, 4294967292, Direction::Vertical, 7) == string("____E__"));
    CHECK(BoardFour.read(4294967288, 4294967293, Direction::Vertical, 7) == string("_____C_"));
    CHECK(BoardFour.read(4294967288, 4294967294, Direction::Vertical, 7) == string("______T"));
    // BoardFour.show();
    Board BoardFive;
    BoardFive.post(6, 6, Direction::Horizontal, "T");
    BoardFive.post(5, 5, Direction::Horizontal, "C");
    BoardFive.post(4, 4, Direction::Horizontal, "E");
    BoardFive.post(3, 3, Direction::Horizontal, "F");
    BoardFive.post(2, 2, Direction::Horizontal, "R");
    BoardFive.post(1, 1, Direction::Horizontal, "E");
    BoardFive.post(0, 0, Direction::Horizontal, "P");
    CHECK(BoardFive.read(0, 0, Direction::Vertical, 7) == string("P______"));
    CHECK(BoardFive.read(0, 1, Direction::Vertical, 7) == string("_E_____"));
    CHECK(BoardFive.read(0, 2, Direction::Vertical, 7) == string("__R____"));
    CHECK(BoardFive.read(0, 3, Direction::Vertical, 7) == string("___F___"));
    CHECK(BoardFive.read(0, 4, Direction::Vertical, 7) == string("____E__"));
    CHECK(BoardFive.read(0, 5, Direction::Vertical, 7) == string("_____C_"));
    CHECK(BoardFive.read(0, 6, Direction::Vertical, 7) == string("______T"));
    // BoardFive.show();
    Board BoardSix;
    BoardSix.post(6, 4294967294, Direction::Horizontal, "T");
    BoardSix.post(5, 4294967293, Direction::Horizontal, "C");
    BoardSix.post(4, 4294967292, Direction::Horizontal, "E");
    BoardSix.post(3, 4294967291, Direction::Horizontal, "F");
    BoardSix.post(2, 4294967290, Direction::Horizontal, "R");
    BoardSix.post(1, 4294967289, Direction::Horizontal, "E");
    BoardSix.post(0, 4294967288, Direction::Horizontal, "P");
    CHECK(BoardSix.read(0, 4294967288, Direction::Vertical, 7) == string("P______"));
    CHECK(BoardSix.read(0, 4294967289, Direction::Vertical, 7) == string("_E_____"));
    CHECK(BoardSix.read(0, 4294967290, Direction::Vertical, 7) == string("__R____"));
    CHECK(BoardSix.read(0, 4294967291, Direction::Vertical, 7) == string("___F___"));
    CHECK(BoardSix.read(0, 4294967292, Direction::Vertical, 7) == string("____E__"));
    CHECK(BoardSix.read(0, 4294967293, Direction::Vertical, 7) == string("_____C_"));
    CHECK(BoardSix.read(0, 4294967294, Direction::Vertical, 7) == string("______T"));
    // BoardSix.show();
    Board BoardSeven;
    BoardSeven.post(4294967294, 6, Direction::Horizontal, "T");
    BoardSeven.post(4294967293, 5, Direction::Horizontal, "C");
    BoardSeven.post(4294967292, 4, Direction::Horizontal, "E");
    BoardSeven.post(4294967291, 3, Direction::Horizontal, "F");
    BoardSeven.post(4294967290, 2, Direction::Horizontal, "R");
    BoardSeven.post(4294967289, 1, Direction::Horizontal, "E");
    BoardSeven.post(4294967288, 0, Direction::Horizontal, "P");
    CHECK(BoardSeven.read(4294967288, 0, Direction::Vertical, 7) == string("P______"));
    CHECK(BoardSeven.read(4294967288, 1, Direction::Vertical, 7) == string("_E_____"));
    CHECK(BoardSeven.read(4294967288, 2, Direction::Vertical, 7) == string("__R____"));
    CHECK(BoardSeven.read(4294967288, 3, Direction::Vertical, 7) == string("___F___"));
    CHECK(BoardSeven.read(4294967288, 4, Direction::Vertical, 7) == string("____E__"));
    CHECK(BoardSeven.read(4294967288, 5, Direction::Vertical, 7) == string("_____C_"));
    CHECK(BoardSeven.read(4294967288, 6, Direction::Vertical, 7) == string("______T"));
    // BoardSeven.show();
}
/* Add more test cases here */
