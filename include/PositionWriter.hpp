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


};
#endif //POSITIONWRITER_HPP


