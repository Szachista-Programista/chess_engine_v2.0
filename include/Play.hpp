#ifndef PLAY_HPP
#define PLAY_HPP

#include "SearchTree.hpp"
#include "PositionWriter.hpp"


class Play
{
public:
        PositionConverter positionConverter;
        PositionFiller positionFiller;
        PositionWriter positionWriter;
        SearchTree searchTree;
        Movement movement;
        Movement::Move move;
        bool color;
        gd::BitBoardPtr position;
        //********************

        Play(bool color);
        bool setUserMove();
            void setUserMoveCoord();

        void run();


void yyy();



};
#endif //PLAY_HPP

