#ifndef POSITIONFILLER_HPP
#define POSITIONFILLER_HPP

#include "GlobalDefinitions.hpp"

class PositionFiller
{
        //const bool whiteMove;
        //const bool blackMove;
        //********************
public: //PositionFiller(bool white = false, bool black = false);
        void fillExtraInfo(gd::BitBoardPtr &ptr)const;
        void fillBitBoard(gd::BitBoardPtr &ptr)const;
private:    void computeSquareCapturedByWhite(gd::BitBoardPtr &ptr)const;
                void computeSquareCapturedByWhitePawn(gd::BitBoardPtr &ptr)const;
                void computeSquareCapturedByWhiteKnight(gd::BitBoardPtr &ptr)const;
                void computeSquareCapturedByWhiteBishop(gd::BitBoardPtr &ptr)const;
                void computeSquareCapturedByWhiteBishopRook(gd::BitBoardPtr &ptr)const;
                void computeSquareCapturedByWhiteQueen(gd::BitBoardPtr &ptr)const;
                void computeSquareCapturedByWhiteKing(gd::BitBoardPtr &ptr)const;
            void computeSquareCapturedByBlack(gd::BitBoardPtr &ptr)const;
                void computeSquareCapturedByBlackPawn(gd::BitBoardPtr &ptr)const;
                void computeSquareCapturedByBlackKnight(gd::BitBoardPtr &ptr)const;
                void computeSquareCapturedByBlackBishop(gd::BitBoardPtr &ptr)const;
                void computeSquareCapturedByBlackBishopRook(gd::BitBoardPtr &ptr)const;
                void computeSquareCapturedByBlackQueen(gd::BitBoardPtr &ptr)const;
                void computeSquareCapturedByBlackKing(gd::BitBoardPtr &ptr)const;
            void updateExtraInfoAfterWhiteMove(gd::BitBoardPtr &ptr)const;
            void updateExtraInfoAfterBlackMove(gd::BitBoardPtr &ptr)const;
};
#endif //POSITIONFILLER_HPP
