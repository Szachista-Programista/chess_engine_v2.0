#include "../include/PositionEvaluator.hpp"

float PositionEvaluator::evaluatePosition(const gd::BitBoardPtr &ptr)const
{
    return
    +1.0f*static_cast<float>(ptr[gd::whitePawn  ].count()) 
    +3.0f*static_cast<float>(ptr[gd::whiteKnight].count())
    +3.0f*static_cast<float>(ptr[gd::whiteBishop].count())
    +5.0f*static_cast<float>(ptr[gd::whiteRook  ].count())
    +9.0f*static_cast<float>(ptr[gd::whiteQueen ].count())
    -1.0f*static_cast<float>(ptr[gd::blackPawn  ].count())
    -3.0f*static_cast<float>(ptr[gd::blackKnight].count())
    -3.0f*static_cast<float>(ptr[gd::blackBishop].count())
    -5.0f*static_cast<float>(ptr[gd::blackRook  ].count())
    -9.0f*static_cast<float>(ptr[gd::blackQueen ].count());
}
