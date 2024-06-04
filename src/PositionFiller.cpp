#include "../include/PositionFiller.hpp"

void PositionFiller::fillBitBoard(gd::BitBoardPtr &ptr, bool white = true, bool black = true)
{
    ptr[gd::whitePiece]  = ptr[gd::whitePawn]  | ptr[gd::whiteKnight] | ptr[gd::whiteBishop] | ptr[gd::whiteRook] | ptr[gd::whiteQueen] | ptr[gd::whiteKing];
    ptr[gd::blackPiece]  = ptr[gd::blackPawn]  | ptr[gd::blackKnight] | ptr[gd::blackBishop] | ptr[gd::blackRook] | ptr[gd::blackQueen] | ptr[gd::blackKing];
    ptr[gd::emptySquare] = ~(ptr[gd::whitePiece] | ptr[gd::blackPiece]);
    if(white)
        computeSquareCapturedByWhite(ptr);
    if(black)
        computeSquareCapturedByBlack(ptr);
}
    void PositionFiller::computeSquareCapturedByWhite(gd::BitBoardPtr &ptr)
{
    fillBitBoard(ptr);
    ptr[gd::whiteCapturedSquare] = 0;
    computeSquareCapturedByWhitePawn(ptr);
    computeSquareCapturedByWhiteKnight(ptr);
    computeSquareCapturedByWhiteBishop(ptr);
    computeSquareCapturedByWhiteBishopRook(ptr);
    computeSquareCapturedByWhiteQueen(ptr);
    computeSquareCapturedByWhiteKing(ptr);
}
        void PositionFiller::computeSquareCapturedByWhitePawn(gd::BitBoardPtr &ptr)
{
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whitePawn] << gd::upLeft)  & gd::SINGLE_RIGHT_EDGE_MASK;
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whitePawn] << gd::upRight) & gd::SINGLE_LEFT_EDGE_MASK;
}
        void PositionFiller::computeSquareCapturedByWhiteKnight(gd::BitBoardPtr &ptr)
{
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKnight] << gd::upUpRight)      & gd::SINGLE_LEFT_EDGE_MASK;
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKnight] << gd::upRightRight)   & gd::DOUBLE_LEFT_EDGE_MASK;
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKnight] >> gd::downRightRight) & gd::DOUBLE_LEFT_EDGE_MASK;
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKnight] >> gd::downDownRight)  & gd::SINGLE_LEFT_EDGE_MASK;
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKnight] >> gd::downDownLeft)   & gd::SINGLE_RIGHT_EDGE_MASK;
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKnight] >> gd::downLeftLeft)   & gd::DOUBLE_RIGHT_EDGE_MASK;
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKnight] << gd::upLeftLeft)     & gd::DOUBLE_RIGHT_EDGE_MASK;
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKnight] << gd::upUpLeft)       & gd::SINGLE_RIGHT_EDGE_MASK;
}
        void PositionFiller::computeSquareCapturedByWhiteBishop(gd::BitBoardPtr &ptr)
{
    std::bitset<64> urMove = ptr[gd::whiteBishop]; //u-up/r-right/d-down/l-left
    std::bitset<64> drMove = ptr[gd::whiteBishop];
    std::bitset<64> dlMove = ptr[gd::whiteBishop];
    std::bitset<64> ulMove = ptr[gd::whiteBishop];

    while((urMove | drMove | dlMove | ulMove).any())
    {
        urMove = (urMove << gd::upRight)   & gd::SINGLE_LEFT_EDGE_MASK;
        drMove = (drMove >> gd::downRight) & gd::SINGLE_LEFT_EDGE_MASK;
        dlMove = (dlMove >> gd::downLeft)  & gd::SINGLE_RIGHT_EDGE_MASK;
        ulMove = (ulMove << gd::upLeft)    & gd::SINGLE_RIGHT_EDGE_MASK;

        ptr[gd::whiteCapturedSquare] |= urMove | drMove | dlMove | ulMove;

        urMove &= ptr[gd::emptySquare];
        drMove &= ptr[gd::emptySquare];
        dlMove &= ptr[gd::emptySquare];
        ulMove &= ptr[gd::emptySquare];
    }
}
        void PositionFiller::computeSquareCapturedByWhiteBishopRook(gd::BitBoardPtr &ptr)
{
    std::bitset<64> uMove = ptr[gd::whiteRook]; //u-up/r-right/d-down/l-left
    std::bitset<64> rMove = ptr[gd::whiteRook];
    std::bitset<64> dMove = ptr[gd::whiteRook];
    std::bitset<64> lMove = ptr[gd::whiteRook];

    while((uMove | rMove | dMove | lMove).any())
    {
        uMove = (uMove << gd::up);
        rMove = (rMove >> gd::rightt) & gd::SINGLE_LEFT_EDGE_MASK;
        dMove = (dMove >> gd::down);
        lMove = (lMove << gd::leftt)  & gd::SINGLE_RIGHT_EDGE_MASK;

        ptr[gd::whiteCapturedSquare] |= uMove | rMove | dMove | lMove;

        uMove &= ptr[gd::emptySquare];
        rMove &= ptr[gd::emptySquare];
        dMove &= ptr[gd::emptySquare];
        lMove &= ptr[gd::emptySquare];
    }
}
        void PositionFiller::computeSquareCapturedByWhiteQueen(gd::BitBoardPtr &ptr)
{
    std::bitset<64> uMove  = ptr[gd::whiteQueen]; //u-up/r-right/d-down/l-left
    std::bitset<64> urMove = ptr[gd::whiteQueen];
    std::bitset<64> rMove  = ptr[gd::whiteQueen];
    std::bitset<64> drMove = ptr[gd::whiteQueen];
    std::bitset<64> dMove  = ptr[gd::whiteQueen];
    std::bitset<64> dlMove = ptr[gd::whiteQueen];
    std::bitset<64> lMove  = ptr[gd::whiteQueen];
    std::bitset<64> ulMove = ptr[gd::whiteQueen];

    while((uMove | urMove | rMove | drMove | dMove | dlMove | lMove | ulMove).any())
    {
        uMove  = (uMove  << gd::up);
        urMove = (urMove << gd::upRight)   & gd::SINGLE_LEFT_EDGE_MASK;
        rMove  = (rMove  >> gd::rightt)    & gd::SINGLE_LEFT_EDGE_MASK;
        drMove = (drMove >> gd::downRight) & gd::SINGLE_LEFT_EDGE_MASK;
        dMove  = (dMove  >> gd::down);
        dlMove = (dlMove >> gd::downLeft)  & gd::SINGLE_RIGHT_EDGE_MASK;
        lMove  = (lMove  << gd::leftt)     & gd::SINGLE_RIGHT_EDGE_MASK;
        ulMove = (ulMove << gd::upLeft)    & gd::SINGLE_RIGHT_EDGE_MASK;

        ptr[gd::whiteCapturedSquare] |= uMove | urMove | rMove | drMove | dMove | dlMove | lMove | ulMove;

        uMove  &= ptr[gd::emptySquare];
        urMove &= ptr[gd::emptySquare];
        rMove  &= ptr[gd::emptySquare];
        drMove &= ptr[gd::emptySquare];
        dMove  &= ptr[gd::emptySquare];
        dlMove &= ptr[gd::emptySquare];
        lMove  &= ptr[gd::emptySquare];
        ulMove &= ptr[gd::emptySquare];
    }
}
        void PositionFiller::computeSquareCapturedByWhiteKing(gd::BitBoardPtr &ptr)
{
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKing] << gd::up);
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKing] << gd::upRight)   & gd::SINGLE_LEFT_EDGE_MASK;
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKing] >> gd::rightt)    & gd::SINGLE_LEFT_EDGE_MASK;
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKing] >> gd::downRight) & gd::SINGLE_LEFT_EDGE_MASK;
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKing] >> gd::down);
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKing] >> gd::downLeft)  & gd::SINGLE_RIGHT_EDGE_MASK;
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKing] << gd::leftt)     & gd::SINGLE_RIGHT_EDGE_MASK;
    ptr[gd::whiteCapturedSquare] |= (ptr[gd::whiteKing] << gd::upLeft)    & gd::SINGLE_RIGHT_EDGE_MASK;
}
    void PositionFiller::computeSquareCapturedByBlack(gd::BitBoardPtr &ptr)
{
    fillBitBoard(ptr);
    ptr[gd::blackCapturedSquare] = 0;
    computeSquareCapturedByBlackPawn(ptr);
    computeSquareCapturedByBlackKnight(ptr);
    computeSquareCapturedByBlackBishop(ptr);
    computeSquareCapturedByBlackBishopRook(ptr);
    computeSquareCapturedByBlackQueen(ptr);
    computeSquareCapturedByBlackKing(ptr);
}
        void PositionFiller::computeSquareCapturedByBlackPawn(gd::BitBoardPtr &ptr)
{
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackPawn] >> gd::downRight) & gd::SINGLE_LEFT_EDGE_MASK;
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackPawn] >> gd::downLeft) & gd::SINGLE_RIGHT_EDGE_MASK;
}
        void PositionFiller::computeSquareCapturedByBlackKnight(gd::BitBoardPtr &ptr)
{
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKnight] << gd::upUpRight)      & gd::SINGLE_LEFT_EDGE_MASK;
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKnight] << gd::upRightRight)   & gd::DOUBLE_LEFT_EDGE_MASK;
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKnight] >> gd::downRightRight) & gd::DOUBLE_LEFT_EDGE_MASK;
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKnight] >> gd::downDownRight)  & gd::SINGLE_LEFT_EDGE_MASK;
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKnight] >> gd::downDownLeft)   & gd::SINGLE_RIGHT_EDGE_MASK;
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKnight] >> gd::downLeftLeft)   & gd::DOUBLE_RIGHT_EDGE_MASK;
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKnight] << gd::upLeftLeft)     & gd::DOUBLE_RIGHT_EDGE_MASK;
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKnight] << gd::upUpLeft)       & gd::SINGLE_RIGHT_EDGE_MASK;
}
        void PositionFiller::computeSquareCapturedByBlackBishop(gd::BitBoardPtr &ptr)
{
    std::bitset<64> urMove = ptr[gd::blackBishop]; //u-up/r-right/d-down/l-left
    std::bitset<64> drMove = ptr[gd::blackBishop];
    std::bitset<64> dlMove = ptr[gd::blackBishop];
    std::bitset<64> ulMove = ptr[gd::blackBishop];

    while((urMove | drMove | dlMove | ulMove).any())
    {
        urMove = (urMove << gd::upRight)   & gd::SINGLE_LEFT_EDGE_MASK;
        drMove = (drMove >> gd::downRight) & gd::SINGLE_LEFT_EDGE_MASK;
        dlMove = (dlMove >> gd::downLeft)  & gd::SINGLE_RIGHT_EDGE_MASK;
        ulMove = (ulMove << gd::upLeft)    & gd::SINGLE_RIGHT_EDGE_MASK;

        ptr[gd::blackCapturedSquare] |= urMove | drMove | dlMove | ulMove;

        urMove &= ptr[gd::emptySquare];
        drMove &= ptr[gd::emptySquare];
        dlMove &= ptr[gd::emptySquare];
        ulMove &= ptr[gd::emptySquare];
    }
}
        void PositionFiller::computeSquareCapturedByBlackBishopRook(gd::BitBoardPtr &ptr)
{
    std::bitset<64> uMove = ptr[gd::blackRook]; //u-up/r-right/d-down/l-left
    std::bitset<64> rMove = ptr[gd::blackRook];
    std::bitset<64> dMove = ptr[gd::blackRook];
    std::bitset<64> lMove = ptr[gd::blackRook];

    while((uMove | rMove | dMove | lMove).any())
    {
        uMove = (uMove << gd::up);
        rMove = (rMove >> gd::rightt) & gd::SINGLE_LEFT_EDGE_MASK;
        dMove = (dMove >> gd::down);
        lMove = (lMove << gd::leftt)  & gd::SINGLE_RIGHT_EDGE_MASK;

        ptr[gd::blackCapturedSquare] |= uMove | rMove | dMove | lMove;

        uMove &= ptr[gd::emptySquare];
        rMove &= ptr[gd::emptySquare];
        dMove &= ptr[gd::emptySquare];
        lMove &= ptr[gd::emptySquare];
    }
}
        void PositionFiller::computeSquareCapturedByBlackQueen(gd::BitBoardPtr &ptr)
{
    std::bitset<64> uMove  = ptr[gd::blackQueen]; //u-up/r-right/d-down/l-left
    std::bitset<64> urMove = ptr[gd::blackQueen];
    std::bitset<64> rMove  = ptr[gd::blackQueen];
    std::bitset<64> drMove = ptr[gd::blackQueen];
    std::bitset<64> dMove  = ptr[gd::blackQueen];
    std::bitset<64> dlMove = ptr[gd::blackQueen];
    std::bitset<64> lMove  = ptr[gd::blackQueen];
    std::bitset<64> ulMove = ptr[gd::blackQueen];

    while((uMove | urMove | rMove | drMove | dMove | dlMove | lMove | ulMove).any())
    {
        uMove  = (uMove  << gd::up);
        urMove = (urMove << gd::upRight)   & gd::SINGLE_LEFT_EDGE_MASK;
        rMove  = (rMove  >> gd::rightt)    & gd::SINGLE_LEFT_EDGE_MASK;
        drMove = (drMove >> gd::downRight) & gd::SINGLE_LEFT_EDGE_MASK;
        dMove  = (dMove  >> gd::down);
        dlMove = (dlMove >> gd::downLeft)  & gd::SINGLE_RIGHT_EDGE_MASK;
        lMove  = (lMove  << gd::leftt)     & gd::SINGLE_RIGHT_EDGE_MASK;
        ulMove = (ulMove << gd::upLeft)    & gd::SINGLE_RIGHT_EDGE_MASK;

        ptr[gd::blackCapturedSquare] |= uMove | urMove | rMove | drMove | dMove | dlMove | lMove | ulMove;

        uMove  &= ptr[gd::emptySquare];
        urMove &= ptr[gd::emptySquare];
        rMove  &= ptr[gd::emptySquare];
        drMove &= ptr[gd::emptySquare];
        dMove  &= ptr[gd::emptySquare];
        dlMove &= ptr[gd::emptySquare];
        lMove  &= ptr[gd::emptySquare];
        ulMove &= ptr[gd::emptySquare];
    }
}
        void PositionFiller::computeSquareCapturedByBlackKing(gd::BitBoardPtr &ptr)
{
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKing] << gd::up);
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKing] << gd::upRight) & gd::SINGLE_LEFT_EDGE_MASK;
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKing] >> gd::rightt) & gd::SINGLE_LEFT_EDGE_MASK;
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKing] >> gd::downRight) & gd::SINGLE_LEFT_EDGE_MASK;
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKing] >> gd::down);
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKing] >> gd::downLeft) & gd::SINGLE_RIGHT_EDGE_MASK;
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKing] << gd::leftt) & gd::SINGLE_RIGHT_EDGE_MASK;
    ptr[gd::blackCapturedSquare] |= (ptr[gd::blackKing] << gd::upLeft) & gd::SINGLE_RIGHT_EDGE_MASK;
}
void PositionFiller::fillExtraInfo(gd::BitBoardPtr &ptr)
{
    if(ptr[gd::whiteKing][3] == true)
    {
        if(ptr[gd::whiteRook][7] == true)
            ptr[gd::extraInfo][7] = 1;
        if(ptr[gd::whiteRook][0] == true)
            ptr[gd::extraInfo][0] = 1;
    }
    if(ptr[gd::blackKing][59] == true)
    {
        if(ptr[gd::blackRook][63] == true)
            ptr[gd::extraInfo][63] = 1;
        if(ptr[gd::blackRook][56] == true)
            ptr[gd::extraInfo][56] = 1;
    }
}
void PositionFiller::updateBitBoardBeforeBlackMove(gd::BitBoardPtr &ptr)
{
    fillBitBoard(ptr, true, false);
    updateExtraInfoBeforeBlackMove(ptr);
}
    void PositionFiller::updateExtraInfoBeforeBlackMove(gd::BitBoardPtr &ptr)
{
    ptr[gd::extraInfo] &= gd::WHITE_EN_PASSANT_MASK;
    ptr[gd::extraInfo][15] = 1;
    checkWhiteCastles(ptr);
    updateMovesCounter(ptr);
}
        void checkWhiteCastles(gd::BitBoardPtr &ptr)
{
    if(ptr[gd::extraInfo][0] == true || ptr[gd::extraInfo][7] == true)
    {
        if(ptr[gd::whiteKing][3] == false)
        {
            ptr[gd::extraInfo][0] = 0;
            ptr[gd::extraInfo][7] = 0;
        }
        else
        {
            if(ptr[gd::whiteRook][7] == false)
                ptr[gd::extraInfo][7] = 0;
            if(ptr[gd::whiteRook][0] == false)
                ptr[gd::extraInfo][0] = 0;
        }
    }    
}
        void PositionFiller::updateMovesCounter(gd::BitBoardPtr &ptr)
{
    uint64_t moveNumber{};
    uint64_t ruleOf50Moves{};
    for(uint8_t i=39; i>31; i--)
    {
        moveNumber <<= 1;
        if(ptr[gd::extraInfo][i])
            moveNumber += 1;
    }
    for(uint8_t i=31; i>23; i--)
    {
        ruleOf50Moves <<= 1;
        if(ptr[gd::extraInfo][i])
            ruleOf50Moves += 1;
    }
    moveNumber++;
    ruleOf50Moves++;
    moveNumber <<= 32;
    ruleOf50Moves <<= 24;
    ptr[gd::extraInfo] &= gd::MOVE_NUMBER_MASK;
    ptr[gd::extraInfo] &= gd::RULE_OF_50_MOVES_MASK;
    ptr[gd::extraInfo] |= moveNumber;
    ptr[gd::extraInfo] |= ruleOf50Moves;
}
void PositionFiller::updateBitBoardBeforeWhiteMove(gd::BitBoardPtr &ptr)
{
    fillBitBoard(ptr, false, true);
    updateExtraInfoBeforeWhiteMove(ptr);
}
    void PositionFiller::updateExtraInfoBeforeWhiteMove(gd::BitBoardPtr &ptr)
{
    ptr[gd::extraInfo] &= gd::BLACK_EN_PASSANT_MASK;
    ptr[gd::extraInfo][15] = 0;
    checkBlackCastles(ptr);
    updateMovesCounter(ptr);
}
        void checkBlackCastles(gd::BitBoardPtr &ptr)
{
    if(ptr[gd::extraInfo][56] == true || ptr[gd::extraInfo][63] == true)
    {
        if(ptr[gd::blackKing][59] == false)
        {
            ptr[gd::extraInfo][56] = 0;
            ptr[gd::extraInfo][63] = 0;
        }
        else
        {
            if(ptr[gd::blackRook][63] == false)
                ptr[gd::extraInfo][63] = 0;
            if(ptr[gd::blackRook][56] == false)
                ptr[gd::extraInfo][56] = 0;
        }
    }
}
