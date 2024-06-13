#ifndef PLAY_SERVIVE_HPP
#define PLAY_SERVIVE_HPP

#include "SearchTree.hpp"
#include "PositionWriter.hpp"


class PlayService
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

        PlayService(bool color);
        bool setUserMove();
            void setUserMoveCoord();

        void run();


void yyy();



};
#endif //PLAY_SERVIVE_HPP

