#include "../include/BlackChildren.hpp"

BlackChildren::BlackChildren(gd::BitBoardPtr &mother): mother{mother}, positionFiller{true, false}
{
    getMoves();
}
void BlackChildren::getMoves()
{
    for(; bit<63; bit++)
    {
        if(mother[gd::blackPiece][bit] == false)
            continue;
        if(mother[gd::blackPawn][bit] == true)
        {
            getPawnMoves();
            continue;
        }
        if(mother[gd::blackKnight][bit] == true)
        {
            getKnightMoves();
            continue;
        }
        if(mother[gd::blackBishop][bit] == true)
        {
            getBischopMoves();
            continue;
        }
        if(mother[gd::blackRook][bit] == true)
        {
            getRookMoves();
            continue;
        }
        if(mother[gd::blackQueen][bit] == true)
        {
            getQueenMoves();
            continue;
        }
        if(mother[gd::blackKing][bit] == true)
        {
            getKingMoves();
            continue;
        }
    }
    numberOfChildren = children.size();
}
    void BlackChildren::getPawnMoves()
{
    if(bit > 15)
    {
        getPawnComonMoves();
        return;
    }
    getPawnPromotionMoves();
}
        void BlackChildren::getPawnComonMoves()
{
    getPawnComonForwardMoves();
    getPawnComonCaptureMoves();
}
            void BlackChildren::getPawnComonForwardMoves()
{
    if(mother[gd::emptySquare][bit + gd::d] == true)
    {
        getNonCaptureMove(gd::blackPawn, bit + gd::d);
        if(bit > 47 && mother[gd::emptySquare][bit + gd::dd] == true)
            getNonCaptureMove(gd::blackPawn, bit + gd::dd);
    }
}
            void BlackChildren::getPawnComonCaptureMoves()
{
    if(uint8_t targetBit = bit + gd::dl; mother[gd::whitePiece][targetBit] == true && bit%8 != 7)
    {
        if     (mother[gd::whitePawn  ][targetBit] == true) getCaptureMove(gd::blackPawn, gd::whitePawn,   targetBit);
        else if(mother[gd::whiteKnight][targetBit] == true) getCaptureMove(gd::blackPawn, gd::whiteKnight, targetBit);
        else if(mother[gd::whiteBishop][targetBit] == true) getCaptureMove(gd::blackPawn, gd::whiteBishop, targetBit);
        else if(mother[gd::whiteRook  ][targetBit] == true) getCaptureMove(gd::blackPawn, gd::whiteRook,   targetBit);
        else if(mother[gd::whiteQueen ][targetBit] == true) getCaptureMove(gd::blackPawn, gd::whiteQueen,  targetBit);
    }
    if(uint8_t targetBit = bit + gd::dr; mother[gd::whitePiece][targetBit] == true && bit%8 != 0)
    {
        if     (mother[gd::whitePawn  ][targetBit] == true) getCaptureMove(gd::blackPawn, gd::whitePawn,   targetBit);
        else if(mother[gd::whiteKnight][targetBit] == true) getCaptureMove(gd::blackPawn, gd::whiteKnight, targetBit);
        else if(mother[gd::whiteBishop][targetBit] == true) getCaptureMove(gd::blackPawn, gd::whiteBishop, targetBit);
        else if(mother[gd::whiteRook  ][targetBit] == true) getCaptureMove(gd::blackPawn, gd::whiteRook,   targetBit);
        else if(mother[gd::whiteQueen ][targetBit] == true) getCaptureMove(gd::blackPawn, gd::whiteQueen,  targetBit);
    }
}
        void BlackChildren::getPawnPromotionMoves()
{
    getPawnForwardPromotionMoves();
    getPawnLeftCapturePromotionMove();
    getPawnRightCapturePromotionMove();
}
            void BlackChildren::getPawnForwardPromotionMoves()
{
    if(mother[gd::emptySquare][bit + gd::d] == true)
    {
        getForwardPromotionMove(gd::blackKnight);
        getForwardPromotionMove(gd::blackBishop);
        getForwardPromotionMove(gd::blackRook);
        getForwardPromotionMove(gd::blackQueen);
    }
}
                void BlackChildren::getForwardPromotionMove(gd::BitBoardIndex promotedPiece)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[gd::blackPawn][bit] = 0;
    child[promotedPiece][bit + gd::d] = 1;
    positionFiller.fillBitBoard(child);
    if(isBlackKingChecked(child))
        delete[]child;
    else
        children.push_back(child);
}
            void BlackChildren::getPawnLeftCapturePromotionMove()
{
    if(uint8_t targetBit = bit + gd::dl; mother[gd::whitePiece][targetBit] == true && bit%8 != 7)
    {
        if(mother[gd::whiteKnight][targetBit] == true)
        {
            getCapturePromotionMove(gd::blackKnight, gd::whiteKnight, targetBit);
            getCapturePromotionMove(gd::blackBishop, gd::whiteKnight, targetBit);
            getCapturePromotionMove(gd::blackRook,   gd::whiteKnight, targetBit);
            getCapturePromotionMove(gd::blackQueen,  gd::whiteKnight, targetBit);
        }
        else if(mother[gd::whiteBishop][targetBit] == true)
        {
            getCapturePromotionMove(gd::blackKnight, gd::whiteBishop, targetBit);
            getCapturePromotionMove(gd::blackBishop, gd::whiteBishop, targetBit);
            getCapturePromotionMove(gd::blackRook,   gd::whiteBishop, targetBit);
            getCapturePromotionMove(gd::blackQueen,  gd::whiteBishop, targetBit);
        }
        else if(mother[gd::whiteRook  ][targetBit] == true)
        {
            getCapturePromotionMove(gd::blackKnight, gd::whiteRook, targetBit);
            getCapturePromotionMove(gd::blackBishop, gd::whiteRook, targetBit);
            getCapturePromotionMove(gd::blackRook,   gd::whiteRook, targetBit);
            getCapturePromotionMove(gd::blackQueen,  gd::whiteRook, targetBit);
        }
        else if(mother[gd::whiteQueen ][targetBit] == true)
        {
            getCapturePromotionMove(gd::blackKnight, gd::whiteQueen, targetBit);
            getCapturePromotionMove(gd::blackBishop, gd::whiteQueen, targetBit);
            getCapturePromotionMove(gd::blackRook,   gd::whiteQueen, targetBit);
            getCapturePromotionMove(gd::blackQueen,  gd::whiteQueen, targetBit);
        }
    }
}
            void BlackChildren::getPawnRightCapturePromotionMove()
{
    if(uint8_t targetBit = bit + gd::dr; mother[gd::whitePiece][targetBit] == true && bit%8 != 0)
    {
        if(mother[gd::whiteKnight][targetBit] == true)
        {
            getCapturePromotionMove(gd::blackKnight, gd::whiteKnight, targetBit);
            getCapturePromotionMove(gd::blackBishop, gd::whiteKnight, targetBit);
            getCapturePromotionMove(gd::blackRook,   gd::whiteKnight, targetBit);
            getCapturePromotionMove(gd::blackQueen,  gd::whiteKnight, targetBit);
        }
        else if(mother[gd::whiteBishop][targetBit] == true)
        {
            getCapturePromotionMove(gd::blackKnight, gd::whiteBishop, targetBit);
            getCapturePromotionMove(gd::blackBishop, gd::whiteBishop, targetBit);
            getCapturePromotionMove(gd::blackRook,   gd::whiteBishop, targetBit);
            getCapturePromotionMove(gd::blackQueen,  gd::whiteBishop, targetBit);
        }
        else if(mother[gd::whiteRook][targetBit] == true)
        {
            getCapturePromotionMove(gd::blackKnight, gd::whiteRook, targetBit);
            getCapturePromotionMove(gd::blackBishop, gd::whiteRook, targetBit);
            getCapturePromotionMove(gd::blackRook,   gd::whiteRook, targetBit);
            getCapturePromotionMove(gd::blackQueen,  gd::whiteRook, targetBit);
        }
        else if(mother[gd::whiteQueen][targetBit] == true)
        {
            getCapturePromotionMove(gd::blackKnight, gd::whiteQueen, targetBit);
            getCapturePromotionMove(gd::blackBishop, gd::whiteQueen, targetBit);
            getCapturePromotionMove(gd::blackRook,   gd::whiteQueen, targetBit);
            getCapturePromotionMove(gd::blackQueen,  gd::whiteQueen, targetBit);
        }
    }
}
                void BlackChildren::getCapturePromotionMove(gd::BitBoardIndex promotedPiece, gd::BitBoardIndex capturedPiece, uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[gd::blackPawn][bit] = 0;
    child[promotedPiece][targetBit] = 1;
    child[capturedPiece][targetBit] = 0;
    positionFiller.fillBitBoard(child);
    if(isBlackKingChecked(child))
        delete[]child;
    else
        children.push_back(child);
}


///////////
    void BlackChildren::getKnightMoves()
{

}
    void BlackChildren::getBischopMoves()
{

}
    void BlackChildren::getRookMoves()
{

}
    void BlackChildren::getQueenMoves()
{

}
    void BlackChildren::getKingMoves()
{

}
///////////


void BlackChildren::getCaptureMove(gd::BitBoardIndex movedPiece, gd::BitBoardIndex capturedPiece, uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[movedPiece][bit] = 0;
    child[movedPiece][targetBit] = 1;
    child[capturedPiece][targetBit] = 0;
    positionFiller.fillBitBoard(child);
    if(isBlackKingChecked(child))
        delete[]child;
    else
        children.push_back(child);
}
void BlackChildren::getNonCaptureMove(gd::BitBoardIndex movedPiece, uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[movedPiece][bit] = 0;
    child[movedPiece][targetBit] = 1;
    positionFiller.fillBitBoard(child);
    if(isBlackKingChecked(child))
        delete[]child;
    else
        children.push_back(child);
}

bool BlackChildren::isBlackKingChecked(gd::BitBoardPtr &ptr)
{
    return (ptr[gd::blackKing] & ptr[gd::whiteCapturedSquare]).any();
}
    gd::BitBoardPtr BlackChildren::copyMotherBitBoard()
    {
        gd::BitBoardPtr copy  = new std::bitset<64>[gd::bitBoardSize]{};
        copy[gd::blackPawn]   = mother[gd::blackPawn];
        copy[gd::blackKnight] = mother[gd::blackKnight];
        copy[gd::blackBishop] = mother[gd::blackBishop];
        copy[gd::blackRook]   = mother[gd::blackRook];
        copy[gd::blackQueen]  = mother[gd::blackQueen];
        copy[gd::blackKing]   = mother[gd::blackKing];
        copy[gd::whitePawn]   = mother[gd::whitePawn];
        copy[gd::whiteKnight] = mother[gd::whiteKnight];
        copy[gd::whiteBishop] = mother[gd::whiteBishop];
        copy[gd::whiteRook]   = mother[gd::whiteRook];
        copy[gd::whiteQueen]  = mother[gd::whiteQueen];
        copy[gd::whiteKing]   = mother[gd::whiteKing];
        return copy;
    }
    BlackChildren::~BlackChildren()
{
        deleteChildren();
}
        void BlackChildren::deleteChildren()
{
    for(int i=0; i<numberOfChildren; i++)
        delete[]children[i];
}

