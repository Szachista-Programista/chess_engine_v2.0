#ifndef POSITIONWRITER_HPP
#define POSITIONWRITER_HPP

#include "PositionConverter.hpp"

class PositionWriter
{
        PositionConverter positionConverter;
        //********************
public: void writeBitBoard(const std::bitset<64> &bs);
        void writeBitBoard(const gd::BitBoardPtr &ptr);
        void writeChessboard(gd::BitBoardPtr BBPtr);


void writeChessboard(std::string position, bool side);
    void writeBoard();
    void writeBitNumbers();
    void writePieces(std::string position, bool side);
        void writePiece(char piece, int x, int y);

};
#endif //POSITIONWRITER_HPP


