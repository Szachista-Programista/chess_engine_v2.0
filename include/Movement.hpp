#ifndef MOVEMENT_HPP
#define MOVEMENT_HPP

#include "TranspositionTable.hpp"
#include "PositionWriter.hpp"//////////////////////////////

class Movement
{
        PositionWriter positionWriter;////////////////////
        WhiteChildren whiteChildren;
        BlackChildren blackChildren;
        PositionConverter positionConverter;
        PositionFiller positionFiller;
        TranspositionTable transpositionTable;
public: struct Move{uint8_t from; uint8_t to; uint8_t promotion;};
        //********************
        bool makeMove(gd::BitBoardPtr &position, Move move);
private:    void makeWhiteMove(gd::BitBoardPtr &position, Move move);
                void makeWhiteCastle(gd::BitBoardPtr &position, Move move);
                void makeWhitePromotion(gd::BitBoardPtr &position, Move move);
                void makeWhiteEnPassant(gd::BitBoardPtr &position, Move move);
                void makeWhiteDoublePush(gd::BitBoardPtr &position, Move move);
                void makeWhiteCommonMove(gd::BitBoardPtr &position, Move move);
            void makeBlackMove(gd::BitBoardPtr &position, Move move);
                void makeBlackCastle(gd::BitBoardPtr &position, Move move);
                void makeBlackPromotion(gd::BitBoardPtr &position, Move move);
                void makeBlackEnPassant(gd::BitBoardPtr &position, Move move);
                void makeBlackDoublePush(gd::BitBoardPtr &position, Move move);
                void makeBlackCommonMove(gd::BitBoardPtr &position, Move move);
public: bool isMoveAllowed(gd::BitBoardPtr &startPosition, gd::BitBoardPtr &movedPosition);
        void check50MovesCounter(gd::BitBoardPtr &startPosition, gd::BitBoardPtr &movedPosition);



};
#endif //MOVEMENT_HPP

