#include "../include/WhiteChildren.hpp"

WhiteChildren::WhiteChildren(gd::BitBoardPtr &mother): mother{mother}, positionFiller{false, true}
{
    getMoves();
}
void WhiteChildren::getMoves()
{
    for(; bit<63; bit++)
    {
        if(mother[gd::whitePiece][bit] == false)
            continue;
        if(mother[gd::whitePawn][bit] == true)
        {
            getPawnMoves();
            continue;
        }
        if(mother[gd::whiteKnight][bit] == true)
        {
            getKnightMoves();
            continue;
        }
        if(mother[gd::whiteBishop][bit] == true)
        {
            getBischopMoves();
            continue;
        }
        if(mother[gd::whiteRook][bit] == true)
        {
            getRookMoves();
            continue;
        }
        if(mother[gd::whiteQueen][bit] == true)
        {
            getQueenMoves();
            continue;
        }
        if(mother[gd::whiteKing][bit] == true)
        {
            getKingMoves();
            continue;
        }
    }
    numberOfChildren = children.size();
}
    void WhiteChildren::getPawnMoves()
{
    if(bit < 48)
    {
        getPawnComonMoves();
        return;
    }
    getPawnPromotionMoves();
}
        void WhiteChildren::getPawnComonMoves()
{
    getPawnComonForwardMoves();
    getPawnComonCaptureMoves();
}
            void WhiteChildren::getPawnComonForwardMoves()
{
    if(mother[gd::emptySquare][bit + gd::u] == true)
    {
        getNonCaptureMove(gd::whitePawn, bit + gd::u);
        if(bit < 16 && mother[gd::emptySquare][bit + gd::uu] == true)
            getNonCaptureMove(gd::whitePawn, bit + gd::uu);
    }
}
            void WhiteChildren::getPawnComonCaptureMoves()
{
    if(uint8_t targetBit = bit + gd::ul; mother[gd::blackPiece][targetBit] == true && bit%8 != 7)
    {
        if     (mother[gd::blackPawn  ][targetBit] == true) getCaptureMove(gd::whitePawn, gd::blackPawn,   targetBit);
        else if(mother[gd::blackKnight][targetBit] == true) getCaptureMove(gd::whitePawn, gd::blackKnight, targetBit);
        else if(mother[gd::blackBishop][targetBit] == true) getCaptureMove(gd::whitePawn, gd::blackBishop, targetBit);
        else if(mother[gd::blackRook  ][targetBit] == true) getCaptureMove(gd::whitePawn, gd::blackRook,   targetBit);
        else if(mother[gd::blackQueen ][targetBit] == true) getCaptureMove(gd::whitePawn, gd::blackQueen,  targetBit);
    }
    if(uint8_t targetBit = bit + gd::ur; mother[gd::blackPiece][targetBit] == true && bit%8 != 0)
    {
        if     (mother[gd::blackPawn  ][targetBit] == true) getCaptureMove(gd::whitePawn, gd::blackPawn,   targetBit);
        else if(mother[gd::blackKnight][targetBit] == true) getCaptureMove(gd::whitePawn, gd::blackKnight, targetBit);
        else if(mother[gd::blackBishop][targetBit] == true) getCaptureMove(gd::whitePawn, gd::blackBishop, targetBit);
        else if(mother[gd::blackRook  ][targetBit] == true) getCaptureMove(gd::whitePawn, gd::blackRook,   targetBit);
        else if(mother[gd::blackQueen ][targetBit] == true) getCaptureMove(gd::whitePawn, gd::blackQueen,  targetBit);
    }
}
        void WhiteChildren::getPawnPromotionMoves()
{
    getPawnForwardPromotionMoves();
    getPawnLeftCapturePromotionMove();
    getPawnRightCapturePromotionMove();
}
            void WhiteChildren::getPawnForwardPromotionMoves()
{
    if(mother[gd::emptySquare][bit + gd::u] == true)
    {
        getForwardPromotionMove(gd::whiteKnight);
        getForwardPromotionMove(gd::whiteBishop);
        getForwardPromotionMove(gd::whiteRook);
        getForwardPromotionMove(gd::whiteQueen);
    }
}
                void WhiteChildren::getForwardPromotionMove(gd::BitBoardIndex promotedPiece)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[gd::whitePawn][bit] = 0;
    child[promotedPiece][bit + gd::u] = 1;
    positionFiller.fillBitBoard(child);
    if(isWhiteKingChecked(child))
        delete[]child;
    else
        children.push_back(child);
}
            void WhiteChildren::getPawnLeftCapturePromotionMove()
{
    if(uint8_t targetBit = bit + gd::ul; mother[gd::blackPiece][targetBit] == true && bit%8 != 7)
    {
        if(mother[gd::blackKnight][targetBit] == true)
        {
            getCapturePromotionMove(gd::whiteKnight, gd::blackKnight, targetBit);
            getCapturePromotionMove(gd::whiteBishop, gd::blackKnight, targetBit);
            getCapturePromotionMove(gd::whiteRook,   gd::blackKnight, targetBit);
            getCapturePromotionMove(gd::whiteQueen,  gd::blackKnight, targetBit);
        }
        else if(mother[gd::blackBishop][targetBit] == true)
        {
            getCapturePromotionMove(gd::whiteKnight, gd::blackBishop, targetBit);
            getCapturePromotionMove(gd::whiteBishop, gd::blackBishop, targetBit);
            getCapturePromotionMove(gd::whiteRook,   gd::blackBishop, targetBit);
            getCapturePromotionMove(gd::whiteQueen,  gd::blackBishop, targetBit);
        }
        else if(mother[gd::blackRook  ][targetBit] == true)
        {
            getCapturePromotionMove(gd::whiteKnight, gd::blackRook, targetBit);
            getCapturePromotionMove(gd::whiteBishop, gd::blackRook, targetBit);
            getCapturePromotionMove(gd::whiteRook,   gd::blackRook, targetBit);
            getCapturePromotionMove(gd::whiteQueen,  gd::blackRook, targetBit);
        }
        else if(mother[gd::blackQueen ][targetBit] == true)
        {
            getCapturePromotionMove(gd::whiteKnight, gd::blackQueen, targetBit);
            getCapturePromotionMove(gd::whiteBishop, gd::blackQueen, targetBit);
            getCapturePromotionMove(gd::whiteRook,   gd::blackQueen, targetBit);
            getCapturePromotionMove(gd::whiteQueen,  gd::blackQueen, targetBit);
        }
    }
}
            void WhiteChildren::getPawnRightCapturePromotionMove()
{
    if(uint8_t targetBit = bit + gd::ur; mother[gd::blackPiece][targetBit] == true && bit%8 != 0)
    {
        if(mother[gd::blackKnight][targetBit] == true)
        {
            getCapturePromotionMove(gd::whiteKnight, gd::blackKnight, targetBit);
            getCapturePromotionMove(gd::whiteBishop, gd::blackKnight, targetBit);
            getCapturePromotionMove(gd::whiteRook,   gd::blackKnight, targetBit);
            getCapturePromotionMove(gd::whiteQueen,  gd::blackKnight, targetBit);
        }
        else if(mother[gd::blackBishop][targetBit] == true)
        {
            getCapturePromotionMove(gd::whiteKnight, gd::blackBishop, targetBit);
            getCapturePromotionMove(gd::whiteBishop, gd::blackBishop, targetBit);
            getCapturePromotionMove(gd::whiteRook,   gd::blackBishop, targetBit);
            getCapturePromotionMove(gd::whiteQueen,  gd::blackBishop, targetBit);
        }
        else if(mother[gd::blackRook][targetBit] == true)
        {
            getCapturePromotionMove(gd::whiteKnight, gd::blackRook, targetBit);
            getCapturePromotionMove(gd::whiteBishop, gd::blackRook, targetBit);
            getCapturePromotionMove(gd::whiteRook,   gd::blackRook, targetBit);
            getCapturePromotionMove(gd::whiteQueen,  gd::blackRook, targetBit);
        }
        else if(mother[gd::blackQueen][targetBit] == true)
        {
            getCapturePromotionMove(gd::whiteKnight, gd::blackQueen, targetBit);
            getCapturePromotionMove(gd::whiteBishop, gd::blackQueen, targetBit);
            getCapturePromotionMove(gd::whiteRook,   gd::blackQueen, targetBit);
            getCapturePromotionMove(gd::whiteQueen,  gd::blackQueen, targetBit);
        }
    }
}
                void WhiteChildren::getCapturePromotionMove(gd::BitBoardIndex promotedPiece, gd::BitBoardIndex capturedPiece, uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[gd::whitePawn][bit] = 0;
    child[promotedPiece][targetBit] = 1;
    child[capturedPiece][targetBit] = 0;
    positionFiller.fillBitBoard(child);
    if(isWhiteKingChecked(child))
        delete[]child;
    else
        children.push_back(child);
}


///////////
    void WhiteChildren::getKnightMoves()
{

}
    void WhiteChildren::getBischopMoves()
{

}
    void WhiteChildren::getRookMoves()
{

}
    void WhiteChildren::getQueenMoves()
{

}
    void WhiteChildren::getKingMoves()
{

}
///////////


void WhiteChildren::getCaptureMove(gd::BitBoardIndex movedPiece, gd::BitBoardIndex capturedPiece, uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[movedPiece][bit] = 0;
    child[movedPiece][targetBit] = 1;
    child[capturedPiece][targetBit] = 0;
    positionFiller.fillBitBoard(child);
    if(isWhiteKingChecked(child))
        delete[]child;
    else
        children.push_back(child);
}
void WhiteChildren::getNonCaptureMove(gd::BitBoardIndex movedPiece, uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[movedPiece][bit] = 0;
    child[movedPiece][targetBit] = 1;
    positionFiller.fillBitBoard(child);
    if(isWhiteKingChecked(child))
        delete[]child;
    else
        children.push_back(child);
}

bool WhiteChildren::isWhiteKingChecked(gd::BitBoardPtr &ptr)
{
    return (ptr[gd::whiteKing] & ptr[gd::blackCapturedSquare]).any();
}
    gd::BitBoardPtr WhiteChildren::copyMotherBitBoard()
    {
        gd::BitBoardPtr copy  = new std::bitset<64>[gd::bitBoardSize]{};
        copy[gd::whitePawn]   = mother[gd::whitePawn];
        copy[gd::whiteKnight] = mother[gd::whiteKnight];
        copy[gd::whiteBishop] = mother[gd::whiteBishop];
        copy[gd::whiteRook]   = mother[gd::whiteRook];
        copy[gd::whiteQueen]  = mother[gd::whiteQueen];
        copy[gd::whiteKing]   = mother[gd::whiteKing];
        copy[gd::blackPawn]   = mother[gd::blackPawn];
        copy[gd::blackKnight] = mother[gd::blackKnight];
        copy[gd::blackBishop] = mother[gd::blackBishop];
        copy[gd::blackRook]   = mother[gd::blackRook];
        copy[gd::blackQueen]  = mother[gd::blackQueen];
        copy[gd::blackKing]   = mother[gd::blackKing];
        return copy;
    }
    WhiteChildren::~WhiteChildren()
{
        deleteChildren();
}
        void WhiteChildren::deleteChildren()
{
    for(int i=0; i<numberOfChildren; i++)
        delete[]children[i];
}
