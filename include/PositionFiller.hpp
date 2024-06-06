#ifndef POSITIONFILLER_HPP
#define POSITIONFILLER_HPP

#include "GlobalDefinitions.hpp"

class PositionFiller
{
        //********************
public: void fillBitBoard(gd::BitBoardPtr &ptr, bool white = true, bool black = true);
private:    void computeSquareCapturedByWhite(gd::BitBoardPtr &ptr);
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
public: void updateBitBoardBeforeBlackMove(gd::BitBoardPtr &ptr);
private:    void updateExtraInfoBeforeBlackMove(gd::BitBoardPtr &ptr);
                void checkWhiteCastles(gd::BitBoardPtr &ptr);
                void updateMovesCounter(gd::BitBoardPtr &ptr);
public: void updateBitBoardBeforeWhiteMove(gd::BitBoardPtr &ptr);
private:    void updateExtraInfoBeforeWhiteMove(gd::BitBoardPtr &ptr);
                void checkBlackCastles(gd::BitBoardPtr &ptr);
};
#endif //POSITIONFILLER_HPP
