#include "../include/WhiteChildren.hpp"

std::vector<gd::BitBoardPtr> WhiteChildren::generateChildren(const gd::BitBoardPtr position)
{
    mother = gd::copyBitBoard(position);
    positionFiller.updateBitBoardBeforeWhiteMove(mother);
    getMoves();
    positionSorter.sortPositionsDescending(children);
    delete[]mother;
    return children;
}
    void WhiteChildren::getMoves()
{
    children.clear();
    for(bit = 0; bit<64; bit++)
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
            getBishopMoves();
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
}
        void WhiteChildren::getPawnMoves()
{
    if(bit < 48)
    {
        getPawnCommonMoves();
        return;
    }
    getPawnPromotionMoves();
}
            void WhiteChildren::getPawnCommonMoves()
{
    getPawnCommonForwardMoves();
    getPawnCommonCaptureMoves();
    getEnPassantMoves();
}
                void WhiteChildren::getPawnCommonForwardMoves()
{
    if(mother[gd::emptySquare][bit + gd::u] == true)
    {
        getNonCaptureMove(gd::whitePawn, bit + gd::u);
        if(bit < 16 && mother[gd::emptySquare][bit + gd::uu] == true)
            getDoublePawnPush();
    }
}
                    void WhiteChildren::getDoublePawnPush()
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[gd::whitePawn][bit] = 0;
    child[gd::whitePawn][bit + gd::uu] = 1;
    child[gd::extraInfo][bit + gd::u] = 1;
    if(isWhiteKingChecked(child))
        delete[]child;
    else
        children.push_back(child);
}
                void WhiteChildren::getPawnCommonCaptureMoves()
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
                void WhiteChildren::getEnPassantMoves()
{
    if(31 < bit && bit < 40)
    {
        if     (mother[gd::extraInfo][bit + gd::ul] == true && bit%8 != 7) getEnPassantMove(bit + gd::ul);
        else if(mother[gd::extraInfo][bit + gd::ur] == true && bit%8 != 0) getEnPassantMove(bit + gd::ur);
    }
}
                    void WhiteChildren::getEnPassantMove(const uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[gd::whitePawn][bit] = 0;
    child[gd::whitePawn][targetBit] = 1;
    child[gd::blackPawn][targetBit + gd::d] = 0;
    if(isWhiteKingChecked(child))
        delete[]child;
    else
        children.push_back(child);
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
                    void WhiteChildren::getForwardPromotionMove(const gd::BitBoardIndex promotedPiece)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[gd::whitePawn][bit] = 0;
    child[promotedPiece][bit + gd::u] = 1;
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
                    void WhiteChildren::getCapturePromotionMove(const gd::BitBoardIndex promotedPiece, const gd::BitBoardIndex capturedPiece, const uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[gd::whitePawn][bit] = 0;
    child[promotedPiece][targetBit] = 1;
    child[capturedPiece][targetBit] = 0;
    if(isWhiteKingChecked(child))
        delete[]child;
    else
        children.push_back(child);
}
        void WhiteChildren::getKnightMoves()
{
    getKnightMoves(getKnightMoveDirections());
}
            std::bitset<8> WhiteChildren::getKnightMoveDirections()
{
    std::bitset<8> directions;
    switch (bit%8)
    {
        case 0:  directions = 0b00001111; break;
        case 1:  directions = 0b10011111; break;
        case 6:  directions = 0b11111001; break;
        case 7:  directions = 0b11110000; break;
        default: directions = 0b11111111; break;
    }
    switch (bit/8)
    {
        case 0: directions &= 0b11000011; break;
        case 1: directions &= 0b11100111; break;
        case 6: directions &= 0b01111110; break;
        case 7: directions &= 0b00111100; break;
    }
    return directions;
}
            void WhiteChildren::getKnightMoves(const std::bitset<8> directions)
{
    if(directions[7]) getKnightMove(bit + gd::uur);
    if(directions[6]) getKnightMove(bit + gd::urr);
    if(directions[5]) getKnightMove(bit + gd::drr);
    if(directions[4]) getKnightMove(bit + gd::ddr);
    if(directions[3]) getKnightMove(bit + gd::ddl);
    if(directions[2]) getKnightMove(bit + gd::dll);
    if(directions[1]) getKnightMove(bit + gd::ull);
    if(directions[0]) getKnightMove(bit + gd::uul);
}
                void WhiteChildren::getKnightMove(const uint8_t targetBit)
{
    if(mother[gd::emptySquare][targetBit] == true)
        getNonCaptureMove(gd::whiteKnight, targetBit);
    else if(mother[gd::blackPiece][targetBit] == true)
    {
        if     (mother[gd::blackPawn  ][targetBit] == true) getCaptureMove(gd::whiteKnight, gd::blackPawn,   targetBit);
        else if(mother[gd::blackKnight][targetBit] == true) getCaptureMove(gd::whiteKnight, gd::blackKnight, targetBit);
        else if(mother[gd::blackBishop][targetBit] == true) getCaptureMove(gd::whiteKnight, gd::blackBishop, targetBit);
        else if(mother[gd::blackRook  ][targetBit] == true) getCaptureMove(gd::whiteKnight, gd::blackRook,   targetBit);
        else if(mother[gd::blackQueen ][targetBit] == true) getCaptureMove(gd::whiteKnight, gd::blackQueen,  targetBit);
    }
}
        void WhiteChildren::getBishopMoves()
{
    if(bit%8 != 0)
    {
        if(bit/8 != 7)
            getSlantMoves(gd::whiteBishop, gd::ur);
        if(bit/8 != 0)
            getSlantMoves(gd::whiteBishop, gd::dr);
    }
    if(bit%8 != 7)
    {
        if(bit/8 != 0)
            getSlantMoves(gd::whiteBishop, gd::dl);
        if(bit/8 != 7)
            getSlantMoves(gd::whiteBishop, gd::ul);
    }
}
        void WhiteChildren::getRookMoves()
{
    if(bit%8 != 0)
        getHorizontalMoves(gd::whiteRook, gd::r);
    if(bit/8 != 0)
        getVerticalMoves(gd::whiteRook, gd::d);
    if(bit%8 != 7)
        getHorizontalMoves(gd::whiteRook, gd::l);
    if(bit/8 != 7)
        getVerticalMoves(gd::whiteRook, gd::u);
}
        void WhiteChildren::getQueenMoves()
{
    if(bit%8 != 0)
    {
        if(bit/8 != 7)
            getSlantMoves(gd::whiteQueen, gd::ur);
        getHorizontalMoves(gd::whiteQueen, gd::r);
        if(bit/8 != 0)
            getSlantMoves(gd::whiteQueen, gd::dr);
    }
    if(bit/8 != 0)
        getVerticalMoves(gd::whiteQueen, gd::d);
    if(bit%8 != 7)
    {
        if(bit/8 != 0)
            getSlantMoves(gd::whiteQueen, gd::dl);
        getHorizontalMoves(gd::whiteQueen, gd::l);
        if(bit/8 != 7)
            getSlantMoves(gd::whiteQueen, gd::ul);
    }
    if(bit/8 != 7)
        getVerticalMoves(gd::whiteQueen, gd::u);
}
                void WhiteChildren::getSlantMoves(const gd::BitBoardIndex movedPiece, const gd::Movements direction)
{
    uint8_t targetBit = bit;
    while(true)
    {
        targetBit += direction;
        if(mother[gd::whitePiece][targetBit] == true)
            return;
        else if(mother[gd::emptySquare][targetBit] == true)
        {
            if(targetBit%8 == 0 || targetBit%8 == 7 || targetBit/8 == 0 || targetBit/8 == 7)
            {
                getNonCaptureMove(movedPiece, targetBit);
                return;
            }
            else
                getNonCaptureMove(movedPiece, targetBit);
        }
        else
        {
            if     (mother[gd::blackPawn  ][targetBit] == true) getCaptureMove(movedPiece, gd::blackPawn,   targetBit);
            else if(mother[gd::blackKnight][targetBit] == true) getCaptureMove(movedPiece, gd::blackKnight, targetBit);
            else if(mother[gd::blackBishop][targetBit] == true) getCaptureMove(movedPiece, gd::blackBishop, targetBit);
            else if(mother[gd::blackRook  ][targetBit] == true) getCaptureMove(movedPiece, gd::blackRook,   targetBit);
            else if(mother[gd::blackQueen ][targetBit] == true) getCaptureMove(movedPiece, gd::blackQueen,  targetBit);
            return;
        }
    }
}
                void WhiteChildren::getHorizontalMoves(const gd::BitBoardIndex movedPiece, const gd::Movements direction)
{
    uint8_t targetBit = bit;
    while(true)
    {
        targetBit += direction;
        if(mother[gd::whitePiece][targetBit] == true)
            return;
        else if(mother[gd::emptySquare][targetBit] == true)
        {
            if(targetBit%8 == 0 || targetBit%8 == 7)
            {
                getNonCaptureMove(movedPiece, targetBit);
                return;
            }
            else
                getNonCaptureMove(movedPiece, targetBit);
        }
        else
        {
            if     (mother[gd::blackPawn  ][targetBit] == true) getCaptureMove(movedPiece, gd::blackPawn,   targetBit);
            else if(mother[gd::blackKnight][targetBit] == true) getCaptureMove(movedPiece, gd::blackKnight, targetBit);
            else if(mother[gd::blackBishop][targetBit] == true) getCaptureMove(movedPiece, gd::blackBishop, targetBit);
            else if(mother[gd::blackRook  ][targetBit] == true) getCaptureMove(movedPiece, gd::blackRook,   targetBit);
            else if(mother[gd::blackQueen ][targetBit] == true) getCaptureMove(movedPiece, gd::blackQueen,  targetBit);
            return;
        }
    }
}
                void WhiteChildren::getVerticalMoves(const gd::BitBoardIndex movedPiece, const gd::Movements direction)
{
    uint8_t targetBit = bit;
    while(true)
    {
        targetBit += direction;
        if(mother[gd::whitePiece][targetBit] == true)
            return;
        else if(mother[gd::emptySquare][targetBit] == true)
        {
            if(targetBit/8 == 0 || targetBit/8 == 7)
            {
                getNonCaptureMove(movedPiece, targetBit);
                return;
            }
            else
                getNonCaptureMove(movedPiece, targetBit);
        }
        else
        {
            if     (mother[gd::blackPawn  ][targetBit] == true) getCaptureMove(movedPiece, gd::blackPawn,   targetBit);
            else if(mother[gd::blackKnight][targetBit] == true) getCaptureMove(movedPiece, gd::blackKnight, targetBit);
            else if(mother[gd::blackBishop][targetBit] == true) getCaptureMove(movedPiece, gd::blackBishop, targetBit);
            else if(mother[gd::blackRook  ][targetBit] == true) getCaptureMove(movedPiece, gd::blackRook,   targetBit);
            else if(mother[gd::blackQueen ][targetBit] == true) getCaptureMove(movedPiece, gd::blackQueen,  targetBit);
            return;
        }
    }
}
        void WhiteChildren::getKingMoves()
{
    getKingCommonMoves(getKingMoveDirections());
    if(mother[gd::extraInfo][7] == true)
        getLongCastle();
    if(mother[gd::extraInfo][0] == true)
        getShortCastle();
}
            std::bitset<8> WhiteChildren::getKingMoveDirections()
{
    std::bitset<8> directions;
    switch (bit%8)
    {
        case 0:  directions = 0b00011111; break;
        case 7:  directions = 0b11110001; break;
        default: directions = 0b11111111; break;
    }
    switch (bit/8)
    {
        case 0: directions &= 0b11000111; break;
        case 7: directions &= 0b01111100; break;
    }
    return directions;
}
            void WhiteChildren::getKingCommonMoves(const std::bitset<8> directions)
{
    if(directions[7]) getKingCommonMove(bit + gd::ur);
    if(directions[6]) getKingCommonMove(bit + gd::r);
    if(directions[5]) getKingCommonMove(bit + gd::dr);
    if(directions[4]) getKingCommonMove(bit + gd::d);
    if(directions[3]) getKingCommonMove(bit + gd::dl);
    if(directions[2]) getKingCommonMove(bit + gd::l);
    if(directions[1]) getKingCommonMove(bit + gd::ul);
    if(directions[0]) getKingCommonMove(bit + gd::u);
}
                void WhiteChildren::getKingCommonMove(const uint8_t targetBit)
{
    if(mother[gd::emptySquare][targetBit] == true)
        getNonCaptureMove(gd::whiteKing, targetBit);
    else if(mother[gd::blackPiece][targetBit] == true)
    {
        if     (mother[gd::blackPawn  ][targetBit] == true) getCaptureMove(gd::whiteKing, gd::blackPawn,   targetBit);
        else if(mother[gd::blackKnight][targetBit] == true) getCaptureMove(gd::whiteKing, gd::blackKnight, targetBit);
        else if(mother[gd::blackBishop][targetBit] == true) getCaptureMove(gd::whiteKing, gd::blackBishop, targetBit);
        else if(mother[gd::blackRook  ][targetBit] == true) getCaptureMove(gd::whiteKing, gd::blackRook,   targetBit);
        else if(mother[gd::blackQueen ][targetBit] == true) getCaptureMove(gd::whiteKing, gd::blackQueen,  targetBit);
    }
}
            void WhiteChildren::getLongCastle()
{
    if(mother[gd::emptySquare][4] && mother[gd::emptySquare][5] && mother[gd::emptySquare][6])
        if(!mother[gd::blackCapturedSquare][3] && !mother[gd::blackCapturedSquare][4] && !mother[gd::blackCapturedSquare][5])
        {
            gd::BitBoardPtr child = copyMotherBitBoard();
            child[gd::whiteKing][3] = 0;
            child[gd::whiteKing][5] = 1;
            child[gd::whiteRook][7] = 0;
            child[gd::whiteRook][4] = 1;
            children.push_back(child);
        }
}
            void WhiteChildren::getShortCastle()
{
    if(mother[gd::emptySquare][1] && mother[gd::emptySquare][2])
        if(!mother[gd::blackCapturedSquare][1] && !mother[gd::blackCapturedSquare][2] && !mother[gd::blackCapturedSquare][3])
        {
            gd::BitBoardPtr child = copyMotherBitBoard();
            child[gd::whiteKing][3] = 0;
            child[gd::whiteKing][1] = 1;
            child[gd::whiteRook][0] = 0;
            child[gd::whiteRook][2] = 1;
            children.push_back(child);
        }
}
    void WhiteChildren::getCaptureMove(const gd::BitBoardIndex movedPiece, const gd::BitBoardIndex capturedPiece, const uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[movedPiece][bit] = 0;
    child[movedPiece][targetBit] = 1;
    child[capturedPiece][targetBit] = 0;
    if(isWhiteKingChecked(child))
        delete[]child;
    else
        children.push_back(child);
}
    void WhiteChildren::getNonCaptureMove(const gd::BitBoardIndex movedPiece, const uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[movedPiece][bit] = 0;
    child[movedPiece][targetBit] = 1;
    if(isWhiteKingChecked(child))
        delete[]child;
    else
        children.push_back(child);
}
    bool WhiteChildren::isWhiteKingChecked(gd::BitBoardPtr &ptr)
{
    positionFiller.fillBitBoard(ptr, false, true);
    return (ptr[gd::whiteKing] & ptr[gd::blackCapturedSquare]).any();
}
    gd::BitBoardPtr WhiteChildren::copyMotherBitBoard()
    {
        gd::BitBoardPtr copy  = new std::bitset<64>[gd::bitBoardSize]{};
        for(uint8_t i=0; i<gd::bitBoardSize; i++)
            copy[i] = mother[i];
        return copy;
    }
void WhiteChildren::deleteChildren(std::vector<gd::BitBoardPtr> &children)
{
    for(uint8_t i=0; i<children.size(); i++)
        delete[]children[i];
}

