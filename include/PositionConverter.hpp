#ifndef POSITIONCONVERTER_HPP
#define POSITIONCONVERTER_HPP

#include "PositionFiller.hpp"


class PositionConverter
{
public:
        //********************

        gd::ChessBoardPtr convertBitBoardTo8x8CharArray(gd::BitBoardPtr BBPtr);
        void convertStringToBitBoard(std::string content, gd::BitBoardPtr &ptr);
        std::string convertChessBoardFileContentToString();

        gd::BitBoardPtr initializeBitBoardPtr();
            gd::BitBoardPtr loadBitBoard();
                



};
#endif //POSITIONCONVERTER_HPP

