#ifndef POSITIONFILLER_HPP
#define POSITIONFILLER_HPP

#include "GlobalDefinitions.hpp"


class PositionFiller
{
public:////

//sproboj stworyc w tej klasie obiekt typu gd::BitBoardPtr zamiast przekazywac go do funkcji

//sproboj podzielic funkcjonalnosc na computeSquareCapturedByWhite / computeSquareCapturedByBlack
const bool fillWhiteCapturedSquare;
const bool fillBlackCapturedSquare;

PositionFiller(bool white, bool black);
void fillBitBoard(gd::BitBoardPtr &ptr);
    void computeSquareCapturedByWhite(gd::BitBoardPtr &ptr);
        void computeSquareCapturedByWhitePawn(gd::BitBoardPtr &ptr);
        void computeSquareCapturedByWhiteKnight(gd::BitBoardPtr &ptr);
        void computeSquareCapturedByWhiteBishop(gd::BitBoardPtr &ptr);
        void computeSquareCapturedByWhiteBishopRook(gd::BitBoardPtr &ptr);
        void computeSquareCapturedByWhiteQueen(gd::BitBoardPtr &ptr);
        void computeSquareCapturedByWhiteKing(gd::BitBoardPtr &ptr);
    void computeSquareCapturedByBlack(gd::BitBoardPtr &ptr);
        void computeSquareCapturedByBlackPawn(gd::BitBoardPtr &ptr);
        void computeSquareCapturedByBlackKnight(gd::BitBoardPtr &ptr);
        void computeSquareCapturedByBlackBishop(gd::BitBoardPtr &ptr);
        void computeSquareCapturedByBlackBishopRook(gd::BitBoardPtr &ptr);
        void computeSquareCapturedByBlackQueen(gd::BitBoardPtr &ptr);
        void computeSquareCapturedByBlackKing(gd::BitBoardPtr &ptr);



};
#endif //POSITIONFILLER_HPP

