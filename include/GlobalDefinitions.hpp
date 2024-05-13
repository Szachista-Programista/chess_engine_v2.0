#ifndef GLOBAL_DEFINITIONS_HPP
#define GLOBAL_DEFINITIONS_HPP

#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
#include <vector>


namespace gd
{
using BitBoardPtr = std::bitset<64>*;
using ChessBoardPtr = char(*)[8];

const std::bitset<64> SINGLE_RIGHT_EDGE_MASK = 0xfefefefefefefefe;
const std::bitset<64> DOUBLE_RIGHT_EDGE_MASK = 0xfcfcfcfcfcfcfcfc;
const std::bitset<64> SINGLE_LEFT_EDGE_MASK  = 0x7f7f7f7f7f7f7f7f;
const std::bitset<64> DOUBLE_LEFT_EDGE_MASK  = 0x3f3f3f3f3f3f3f3f;

struct errorType{std::string errorMessage;};

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
    anyPiece,
    emptySquare,
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
}


#endif//GLOBAL_DEFINITIONS_HPP
