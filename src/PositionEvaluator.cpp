#include "../include/PositionEvaluator.hpp"

int PositionEvaluator::evaluatePosition(const gd::BitBoardPtr &ptr)
{
    int evaluation{};

    for(bit = 0; bit<64; bit++)
    {
        if(ptr[gd::emptySquare][bit] == true)
            continue;
        if(ptr[gd::whitePawn][bit] == true)
        {
            evaluation += 200 + ppp::whitePawn[63-bit];
            continue;
        }
        if(ptr[gd::whiteKnight][bit] == true)
        {
            evaluation += 600 + ppp::whiteKnight[63-bit];
            continue;
        }
        if(ptr[gd::whiteBishop][bit] == true)
        {
            evaluation += 600 + ppp::whiteBishop[63-bit];
            continue;
        }
        if(ptr[gd::whiteRook][bit] == true)
        {
            evaluation += 1000 + ppp::whiteRook[63-bit];
            continue;
        }
        if(ptr[gd::whiteQueen][bit] == true)
        {
            evaluation += 1800 + ppp::whiteQueen[63-bit];
            continue;
        }
        if(ptr[gd::whiteKing][bit] == true)
        {
            evaluation += ppp::whiteKing[63-bit];
            continue;
        }
        if(ptr[gd::blackPawn][bit] == true)
        {
            evaluation -= 200 + ppp::blackPawn[63-bit];
            continue;
        }
        if(ptr[gd::blackKnight][bit] == true)
        {
            evaluation -= 600 + ppp::blackKnight[63-bit];
            continue;
        }
        if(ptr[gd::blackBishop][bit] == true)
        {
            evaluation -= 600 + ppp::blackBishop[63-bit];
            continue;
        }
        if(ptr[gd::blackRook][bit] == true)
        {
            evaluation -= 1000 + ppp::blackRook[63-bit];
            continue;
        }
        if(ptr[gd::blackQueen][bit] == true)
        {
            evaluation -= 1800 + ppp::blackQueen[63-bit];
            continue;
        }
        if(ptr[gd::blackKing][bit] == true)
        {
            evaluation -= ppp::blackKing[63-bit];
            continue;
        }
    }
    return evaluation;
}
