#ifndef MOVE_HPP
#define MOVE_HPP

#include "PositionConverter.hpp"
#include "WhiteChildren.hpp"
#include "BlackChildren.hpp"

class Move
{
        WhiteChildren whiteChildren;
        BlackChildren blackChildren;
        PositionConverter positionConverter;
        PositionFiller positionFiller;
        struct Move{uint8_t from; uint8_t to; uint8_t promotion;};
        //********************
public: void makeMove(gd::BitBoardPtr &movedPosition, gd::Move move);
private:    void makeWhiteMove(gd::BitBoardPtr &movedPosition, gd::Move move);
                void makeWhiteCastle(gd::BitBoardPtr &movedPosition, gd::Move move);
                void makeWhitePromotion(gd::BitBoardPtr &movedPosition, gd::Move move);
                void makeWhiteEnPassant(gd::BitBoardPtr &movedPosition, gd::Move move);
                void makeWhiteDoublePush(gd::BitBoardPtr &position, gd::Move move);
                void makeWhiteCommonMove(gd::BitBoardPtr &movedPosition, gd::Move move);
            void makeBlackMove(gd::BitBoardPtr &movedPosition, gd::Move move);
                void makeBlackCastle(gd::BitBoardPtr &movedPosition, gd::Move move);
                void makeBlackPromotion(gd::BitBoardPtr &movedPosition, gd::Move move);
                void makeBlackEnPassant(gd::BitBoardPtr &movedPosition, gd::Move move);
                void makeBlackDoublePush(gd::BitBoardPtr &position, gd::Move move);
                void makeBlackCommonMove(gd::BitBoardPtr &movedPosition, gd::Move move);
};
#endif //MOVE_HPP

