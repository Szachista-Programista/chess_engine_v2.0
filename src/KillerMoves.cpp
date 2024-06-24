#include "../include/KillerMoves.hpp"


bool KillerMoves::isKiller(const gd::BitBoardPtr &startPosition, const gd::BitBoardPtr &movedPosition, uint8_t depth)
{
    Movement::Move move = movement.getMove(startPosition, movedPosition);
    if(killers[depth][0] == move || killers[depth][1] == move)
        return true;
    else
        return false;
}
void KillerMoves::addKillerMove(Movement::Move move, uint8_t depth)
{
    if(killers[depth][0] != move && killers[depth][1] != move)
    {
        killers[depth][1] = killers[depth][0];
        killers[depth][0] = move;
    }
    
}





