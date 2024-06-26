#ifndef GLOBAL_DEFINITIONS_HPP
#define GLOBAL_DEFINITIONS_HPP

//#include <windows.h>
#include <iostream>
#include <iomanip>
#include <bitset>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdint>//??????????
#include <chrono>////////////

namespace gd
{
using BitBoardPtr = std::bitset<64>*;
using ChessBoardPtr = char(*)[8];

const std::bitset<64> SINGLE_RIGHT_EDGE_MASK = 0xfefefefefefefefe;
const std::bitset<64> DOUBLE_RIGHT_EDGE_MASK = 0xfcfcfcfcfcfcfcfc;
const std::bitset<64> SINGLE_LEFT_EDGE_MASK  = 0x7f7f7f7f7f7f7f7f;
const std::bitset<64> DOUBLE_LEFT_EDGE_MASK  = 0x3f3f3f3f3f3f3f3f;
const std::bitset<64> WHITE_EN_PASSANT_MASK  = 0xffff00ffffffffff;
const std::bitset<64> BLACK_EN_PASSANT_MASK  = 0xffffffffff00ffff;
const std::bitset<64> MOVE_NUMBER_MASK       = 0xffffff00ffffffff;
const std::bitset<64> RULE_OF_50_MOVES_MASK  = 0xffffffff00ffffff;
const int INF = 1'000'000'000;
const int MAX_DEPTH = 20;

struct errorType{std::string errorMessage;};
struct EvaluedPosition{BitBoardPtr position; int eval; int moveNumber;};


enum BitIndex
{
    isWhiteTurn = 15,
    isCheck = 16
};
enum BitBoardIndex
{
    whitePawn,
    whiteKnight,
    whiteBishop,
    whiteRook,
    whiteQueen,
    whiteKing,

    blackPawn,
    blackKnight,
    blackBishop,
    blackRook,
    blackQueen,
    blackKing,

    whitePiece,
    whiteCapturedSquare,
    blackPiece,
    blackCapturedSquare,

    emptySquare,
    extraInfo,
    bitBoardSize
};
enum BitwiseShift
{
    up = 8,
    upRight = 7,
    rightt = 1,
    downRight = 9,
    down = 8,
    downLeft = 7,
    leftt = 1,
    upLeft = 9,

    upUp = 16,
    downDown = 16,

    upUpRight = 15,
    upRightRight = 6,
    downRightRight = 10,
    downDownRight = 17,
    downDownLeft = 15,
    downLeftLeft = 6,
    upLeftLeft = 10,
    upUpLeft = 17
};
enum Movements
{
    u = 8,
    ur = 7,
    r = -1,
    dr = -9,
    d = -8,
    dl = -7,
    l = 1,
    ul = 9,

    uu = 16,
    dd = -16,

    uur = 15,
    urr = 6,
    drr = -10,
    ddr = -17,
    ddl = -15,
    dll = -6,
    ull = 10,
    uul = 17
};


    gd::BitBoardPtr copyBitBoard(const gd::BitBoardPtr orginal);


}
#endif//GLOBAL_DEFINITIONS_HPP


