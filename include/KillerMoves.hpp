#ifndef KILLERMOVES_HPP
#define KILLERMOVES_HPP

#include "Movement.hpp"

class KillerMoves
{
        Movement movement;
        Movement::Move killers[gd::MAX_DEPTH][2];
        //********************
public: bool isKiller(const gd::BitBoardPtr &startPosition, const gd::BitBoardPtr &movedPosition, uint8_t depth);
        void addKillerMove(Movement::Move move, uint8_t depth);
};
#endif //KILLERMOVES_HPP

