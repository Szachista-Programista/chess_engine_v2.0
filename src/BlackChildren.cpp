#include "../include/BlackChildren.hpp"

std::vector<gd::BitBoardPtr> BlackChildren::generateChildren(gd::BitBoardPtr position)
{
    positionFiller.fillBitBoard(position, true, false);
    mother = gd::copyBitBoard(position);
    mother[gd::extraInfo] &= gd::WHITE_EN_PASSANT_MASK;
    if((mother[gd::blackKing] & mother[gd::whiteCapturedSquare]).any())
        mother[gd::extraInfo][gd::isCheck] = 1;
    positionFiller.checkCastles(mother);
    getMoves();
    positionSorter.sortPositionsAscending(children);
    delete[]mother;
    return children;
}
    void BlackChildren::getMoves()
{
    children.clear();
    for(bit = 0; bit<64; bit++)
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
            getBishopMoves();
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
}
        void BlackChildren::getPawnMoves()
{
    if(bit > 15)
    {
        getPawnCommonMoves();
        return;
    }
    getPawnPromotionMoves();
}
            void BlackChildren::getPawnCommonMoves()
{
    getPawnCommonForwardMoves();
    getPawnCommonCaptureMoves();
    getEnPassantMoves();
}
                void BlackChildren::getPawnCommonForwardMoves()
{
    if(mother[gd::emptySquare][bit + gd::d] == true)
    {
        getNonCaptureMove(gd::blackPawn, bit + gd::d);
        if(bit > 47 && mother[gd::emptySquare][bit + gd::dd] == true)
            getDoublePawnPush();
    }
}
                    void BlackChildren::getDoublePawnPush()
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[gd::blackPawn][bit] = 0;
    child[gd::blackPawn][bit + gd::dd] = 1;
    child[gd::extraInfo][bit + gd::d] = 1;
    validateMove(child);
}
                void BlackChildren::getPawnCommonCaptureMoves()
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
                void BlackChildren::getEnPassantMoves()
{
    if(23 < bit && bit < 32)
    {
        if     (mother[gd::extraInfo][bit + gd::dl] == true && bit%8 != 7) getEnPassantMove(bit + gd::dl);
        else if(mother[gd::extraInfo][bit + gd::dr] == true && bit%8 != 0) getEnPassantMove(bit + gd::dr);
    }
}
                    void BlackChildren::getEnPassantMove(const uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[gd::blackPawn][bit] = 0;
    child[gd::blackPawn][targetBit] = 1;
    child[gd::whitePawn][targetBit + gd::u] = 0;
    validateMove(child);
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
                    void BlackChildren::getForwardPromotionMove(const gd::BitBoardIndex promotedPiece)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[gd::blackPawn][bit] = 0;
    child[promotedPiece][bit + gd::d] = 1;
    validateMove(child);
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
                    void BlackChildren::getCapturePromotionMove(const gd::BitBoardIndex promotedPiece, const gd::BitBoardIndex capturedPiece, const uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[gd::blackPawn][bit] = 0;
    child[promotedPiece][targetBit] = 1;
    child[capturedPiece][targetBit] = 0;
    validateMove(child);
}
        void BlackChildren::getKnightMoves()
{
    getKnightMoves(getKnightMoveDirections());
}
            std::bitset<8> BlackChildren::getKnightMoveDirections()
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
            void BlackChildren::getKnightMoves(const std::bitset<8> directions)
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
                void BlackChildren::getKnightMove(const uint8_t targetBit)
{
    if(mother[gd::emptySquare][targetBit] == true)
        getNonCaptureMove(gd::blackKnight, targetBit);
    else if(mother[gd::whitePiece][targetBit] == true)
    {
        if     (mother[gd::whitePawn  ][targetBit] == true) getCaptureMove(gd::blackKnight, gd::whitePawn,   targetBit);
        else if(mother[gd::whiteKnight][targetBit] == true) getCaptureMove(gd::blackKnight, gd::whiteKnight, targetBit);
        else if(mother[gd::whiteBishop][targetBit] == true) getCaptureMove(gd::blackKnight, gd::whiteBishop, targetBit);
        else if(mother[gd::whiteRook  ][targetBit] == true) getCaptureMove(gd::blackKnight, gd::whiteRook,   targetBit);
        else if(mother[gd::whiteQueen ][targetBit] == true) getCaptureMove(gd::blackKnight, gd::whiteQueen,  targetBit);
    }
}
        void BlackChildren::getBishopMoves()
{
    if(bit%8 != 0)
    {
        if(bit/8 != 7)
            getSlantMoves(gd::blackBishop, gd::ur);
        if(bit/8 != 0)
            getSlantMoves(gd::blackBishop, gd::dr);
    }
    if(bit%8 != 7)
    {
        if(bit/8 != 0)
            getSlantMoves(gd::blackBishop, gd::dl);
        if(bit/8 != 7)
            getSlantMoves(gd::blackBishop, gd::ul);
    }
}
        void BlackChildren::getRookMoves()
{
    if(bit%8 != 0)
        getHorizontalMoves(gd::blackRook, gd::r);
    if(bit/8 != 0)
        getVerticalMoves(gd::blackRook, gd::d);
    if(bit%8 != 7)
        getHorizontalMoves(gd::blackRook, gd::l);
    if(bit/8 != 7)
        getVerticalMoves(gd::blackRook, gd::u);
}
        void BlackChildren::getQueenMoves()
{
    if(bit%8 != 0)
    {
        if(bit/8 != 7)
            getSlantMoves(gd::blackQueen, gd::ur);
        getHorizontalMoves(gd::blackQueen, gd::r);
        if(bit/8 != 0)
            getSlantMoves(gd::blackQueen, gd::dr);
    }
    if(bit/8 != 0)
        getVerticalMoves(gd::blackQueen, gd::d);
    if(bit%8 != 7)
    {
        if(bit/8 != 0)
            getSlantMoves(gd::blackQueen, gd::dl);
        getHorizontalMoves(gd::blackQueen, gd::l);
        if(bit/8 != 7)
            getSlantMoves(gd::blackQueen, gd::ul);
    }
    if(bit/8 != 7)
        getVerticalMoves(gd::blackQueen, gd::u);
}
                void BlackChildren::getSlantMoves(const gd::BitBoardIndex movedPiece, const gd::Movements direction)
{
    uint8_t targetBit = bit;
    while(true)
    {
        targetBit += direction;
        if(mother[gd::blackPiece][targetBit] == true)
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
            if     (mother[gd::whitePawn  ][targetBit] == true) getCaptureMove(movedPiece, gd::whitePawn,   targetBit);
            else if(mother[gd::whiteKnight][targetBit] == true) getCaptureMove(movedPiece, gd::whiteKnight, targetBit);
            else if(mother[gd::whiteBishop][targetBit] == true) getCaptureMove(movedPiece, gd::whiteBishop, targetBit);
            else if(mother[gd::whiteRook  ][targetBit] == true) getCaptureMove(movedPiece, gd::whiteRook,   targetBit);
            else if(mother[gd::whiteQueen ][targetBit] == true) getCaptureMove(movedPiece, gd::whiteQueen,  targetBit);
            return;
        }
    }
}
                void BlackChildren::getHorizontalMoves(const gd::BitBoardIndex movedPiece, const gd::Movements direction)
{
    uint8_t targetBit = bit;
    while(true)
    {
        targetBit += direction;
        if(mother[gd::blackPiece][targetBit] == true)
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
            if     (mother[gd::whitePawn  ][targetBit] == true) getCaptureMove(movedPiece, gd::whitePawn,   targetBit);
            else if(mother[gd::whiteKnight][targetBit] == true) getCaptureMove(movedPiece, gd::whiteKnight, targetBit);
            else if(mother[gd::whiteBishop][targetBit] == true) getCaptureMove(movedPiece, gd::whiteBishop, targetBit);
            else if(mother[gd::whiteRook  ][targetBit] == true) getCaptureMove(movedPiece, gd::whiteRook,   targetBit);
            else if(mother[gd::whiteQueen ][targetBit] == true) getCaptureMove(movedPiece, gd::whiteQueen,  targetBit);
            return;
        }
    }
}
                void BlackChildren::getVerticalMoves(const gd::BitBoardIndex movedPiece, const gd::Movements direction)
{
    uint8_t targetBit = bit;
    while(true)
    {
        targetBit += direction;
        if(mother[gd::blackPiece][targetBit] == true)
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
            if     (mother[gd::whitePawn  ][targetBit] == true) getCaptureMove(movedPiece, gd::whitePawn,   targetBit);
            else if(mother[gd::whiteKnight][targetBit] == true) getCaptureMove(movedPiece, gd::whiteKnight, targetBit);
            else if(mother[gd::whiteBishop][targetBit] == true) getCaptureMove(movedPiece, gd::whiteBishop, targetBit);
            else if(mother[gd::whiteRook  ][targetBit] == true) getCaptureMove(movedPiece, gd::whiteRook,   targetBit);
            else if(mother[gd::whiteQueen ][targetBit] == true) getCaptureMove(movedPiece, gd::whiteQueen,  targetBit);
            return;
        }
    }
}
        void BlackChildren::getKingMoves()
{
    getKingCommonMoves(getKingMoveDirections());
    if(mother[gd::extraInfo][63] == true)
        getLongCastle();
    if(mother[gd::extraInfo][56] == true)
        getShortCastle();
}
            std::bitset<8> BlackChildren::getKingMoveDirections()
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
            void BlackChildren::getKingCommonMoves(const std::bitset<8> directions)
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
                void BlackChildren::getKingCommonMove(const uint8_t targetBit)
{
    if(mother[gd::whiteCapturedSquare][targetBit] == true)
        return;
    if(mother[gd::emptySquare][targetBit] == true)
        getNonCaptureMove(gd::blackKing, targetBit);
    else if(mother[gd::whitePiece][targetBit] == true)
    {
        if     (mother[gd::whitePawn  ][targetBit] == true) getCaptureMove(gd::blackKing, gd::whitePawn,   targetBit);
        else if(mother[gd::whiteKnight][targetBit] == true) getCaptureMove(gd::blackKing, gd::whiteKnight, targetBit);
        else if(mother[gd::whiteBishop][targetBit] == true) getCaptureMove(gd::blackKing, gd::whiteBishop, targetBit);
        else if(mother[gd::whiteRook  ][targetBit] == true) getCaptureMove(gd::blackKing, gd::whiteRook,   targetBit);
        else if(mother[gd::whiteQueen ][targetBit] == true) getCaptureMove(gd::blackKing, gd::whiteQueen,  targetBit);
    }
}
            void BlackChildren::getLongCastle()
{
    if(mother[gd::emptySquare][60] && mother[gd::emptySquare][61] && mother[gd::emptySquare][62])
        if(!mother[gd::whiteCapturedSquare][59] && !mother[gd::whiteCapturedSquare][60] && !mother[gd::whiteCapturedSquare][61])
        {
            gd::BitBoardPtr child = copyMotherBitBoard();
            child[gd::blackKing][59] = 0;
            child[gd::blackKing][61] = 1;
            child[gd::blackRook][63] = 0;
            child[gd::blackRook][60] = 1;
            children.push_back(child);
        }
}
            void BlackChildren::getShortCastle()
{
    if(mother[gd::emptySquare][57] && mother[gd::emptySquare][58])
        if(!mother[gd::whiteCapturedSquare][57] && !mother[gd::whiteCapturedSquare][58] && !mother[gd::whiteCapturedSquare][59])
        {
            gd::BitBoardPtr child = copyMotherBitBoard();
            child[gd::blackKing][59] = 0;
            child[gd::blackKing][57] = 1;
            child[gd::blackRook][56] = 0;
            child[gd::blackRook][58] = 1;
            children.push_back(child);
        }
}
    void BlackChildren::getCaptureMove(const gd::BitBoardIndex movedPiece, const gd::BitBoardIndex capturedPiece, const uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[movedPiece][bit] = 0;
    child[movedPiece][targetBit] = 1;
    child[capturedPiece][targetBit] = 0;
    validateMove(child);
}
    void BlackChildren::getNonCaptureMove(const gd::BitBoardIndex movedPiece, const uint8_t targetBit)
{
    gd::BitBoardPtr child = copyMotherBitBoard();
    child[movedPiece][bit] = 0;
    child[movedPiece][targetBit] = 1;
    validateMove(child);
}
    void BlackChildren::validateMove(gd::BitBoardPtr &ptr)
{
    if((mother[gd::extraInfo][gd::isCheck] || mother[gd::blackCapturedSquare][bit]) && isBlackKingChecked(ptr))
        delete[]ptr;
    else
        children.push_back(ptr);
}
        bool BlackChildren::isBlackKingChecked(gd::BitBoardPtr &ptr)
{
    positionFiller.fillBitBoard(ptr, true, false);
    return (ptr[gd::blackKing] & ptr[gd::whiteCapturedSquare]).any();
}
    gd::BitBoardPtr BlackChildren::copyMotherBitBoard()
    {
        gd::BitBoardPtr copy  = new std::bitset<64>[gd::bitBoardSize]{};
        for(uint8_t i=0; i<gd::bitBoardSize; i++)
            copy[i] = mother[i];
        return copy;
    }
    void BlackChildren::deleteChildren(std::vector<gd::BitBoardPtr> &children)
{
    for(uint8_t i=0; i<children.size(); i++)
        delete[]children[i];
}



