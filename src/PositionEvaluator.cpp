#include "../include/PositionEvaluator.hpp"

float PositionEvaluator::evaluatePosition(const gd::BitBoardPtr &ptr)const
{
    return
     ptr[gd::whitePawn].count() + 3*ptr[gd::whiteKnight].count() + 3*ptr[gd::whiteBishop].count() + 5*ptr[gd::whiteRook].count() + 9*ptr[gd::whiteQueen].count()
    -ptr[gd::blackPawn].count() - 3*ptr[gd::blackKnight].count() - 3*ptr[gd::blackBishop].count() - 5*ptr[gd::blackRook].count() - 9*ptr[gd::blackQueen].count();
}

