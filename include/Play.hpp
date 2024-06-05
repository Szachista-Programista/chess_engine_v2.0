#ifndef PLAY_HPP
#define PLAY_HPP

#include "SearchTree.hpp"
#include "PositionWriter.hpp"


class Play
{
public:
        PositionConverter positionConverter;
        TranspositionTable transpositionTable;
        PositionWriter positionWriter;
        PositionFiller positionFiller;
        SearchTree searchTree;
        WhiteChildren whiteChildren;
        BlackChildren blackChildren;
        int from;
        int to;
        bool color;
        gd::BitBoardPtr position;
        //********************

        Play(bool color);
        bool isMoveAllowed(gd::BitBoardPtr &startPosition, gd::BitBoardPtr &targetPosition);
        bool setUserMove();
            void setUserMoveCoord();
            bool generateNewPosition();

        void run();






};
#endif //PLAY_HPP

