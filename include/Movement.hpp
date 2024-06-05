#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "PositionConverter.hpp"
#include "WhiteChildren.hpp"
#include "BlackChildren.hpp"

class Movement
{
        WhiteChildren whiteChildren;
        BlackChildren blackChildren;
        PositionConverter positionConverter;
        PositionFiller positionFiller;
public: struct Move{uint8_t from; uint8_t to; uint8_t promotion;};
        //********************
        void makeMove(gd::BitBoardPtr &movedPosition, Move move);
private:    void makeWhiteMove(gd::BitBoardPtr &movedPosition, Move move);
                void makeWhiteCastle(gd::BitBoardPtr &movedPosition, Move move);
                void makeWhitePromotion(gd::BitBoardPtr &movedPosition, Move move);
                void makeWhiteEnPassant(gd::BitBoardPtr &movedPosition, Move move);
                void makeWhiteDoublePush(gd::BitBoardPtr &position, Move move);
                void makeWhiteCommonMove(gd::BitBoardPtr &movedPosition, Move move);
            void makeBlackMove(gd::BitBoardPtr &movedPosition, Move move);
                void makeBlackCastle(gd::BitBoardPtr &movedPosition, Move move);
                void makeBlackPromotion(gd::BitBoardPtr &movedPosition, Move move);
                void makeBlackEnPassant(gd::BitBoardPtr &movedPosition, Move move);
                void makeBlackDoublePush(gd::BitBoardPtr &position, Move move);
                void makeBlackCommonMove(gd::BitBoardPtr &movedPosition, Move move);
};
#endif //MOVEMENT_HPP

