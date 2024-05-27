#ifndef PLAY_HPP
#define PLAY_HPP

#include "SearchTree.hpp"
#include "PositionWriter.hpp"


class Play
{
public:
        PositionConverter positionConverter;
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
            bool isTheSamePosition(gd::BitBoardPtr &positionA, gd::BitBoardPtr &positionB);
        bool setUserMove();
            void setUserMoveCoord();
            bool generateNewPosition();

        void run();






};
#endif //PLAY_HPP
