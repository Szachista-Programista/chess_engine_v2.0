#include "../include/Movement.hpp"


bool Movement::makeMove(gd::BitBoardPtr &position, Move move)
{
    gd::BitBoardPtr movedPosition = gd::copyBitBoard(position);

    if(position[gd::extraInfo][gd::isWhiteTurn] == 1)
        makeWhiteMove(movedPosition, move);
    else
        makeBlackMove(movedPosition, move);

    if(isMoveAllowed(position, movedPosition))
    {
        check50MovesCounter(position, movedPosition);
        delete[]position;
        position = movedPosition;
        return true;
    }
    else
    {
        delete[]movedPosition;
        return false;
    }
}
    void Movement::makeWhiteMove(gd::BitBoardPtr &position, Move move)
{
    if(position[gd::whiteKing][move.from] == 1 && move.from == 3 && (move.to == 1 || move.to == 5))
        makeWhiteCastle(position, move);
    else if(move.promotion != 0)
        makeWhitePromotion(position, move);
    else if(position[gd::whitePawn][move.from] == 1 && position[gd::emptySquare][move.to] == 1 && (move.to - move.from == gd::ul || move.to - move.from == gd::ur))
        makeWhiteEnPassant(position, move);
    else if(position[gd::whitePawn][move.from] == 1 && move.to - move.from == gd::uu)
        makeWhiteDoublePush(position, move);
    else
        makeWhiteCommonMove(position, move);
    positionFiller.fillBitBoard(position);
    positionFiller.updateExtraInfoAfterWhiteMove(position);
}
        void Movement::makeWhiteCastle(gd::BitBoardPtr &position, Move move)
{
    if(move.to == 1)
    {
        position[gd::whiteKing][3] = 0;
        position[gd::whiteKing][1] = 1;
        position[gd::whiteRook][0] = 0;
        position[gd::whiteRook][2] = 1;
        return;
    }
    if(move.to == 5)
    {
        position[gd::whiteKing][3] = 0;
        position[gd::whiteKing][5] = 1;
        position[gd::whiteRook][7] = 0;
        position[gd::whiteRook][4] = 1;
        return;
    }
}
        void Movement::makeWhitePromotion(gd::BitBoardPtr &position, Move move)
{
    position[gd::whitePawn][move.from] = 0;
    position[positionConverter.getPieceIndex(position, move.to)][move.to] = 0;
    switch(move.promotion)
    {
        case 1: position[gd::whiteKnight][move.to] = 1; break;
        case 2: position[gd::whiteBishop][move.to] = 1; break;
        case 3: position[gd::whiteRook  ][move.to] = 1; break;
        case 4: position[gd::whiteQueen ][move.to] = 1; break;
    }
}
        void Movement::makeWhiteEnPassant(gd::BitBoardPtr &position, Move move)
{
    position[gd::whitePawn][move.from] = 0;
    position[gd::whitePawn][move.to] = 1;
    position[gd::blackPawn][move.to + gd::d] = 0;
}
        void Movement::makeWhiteDoublePush(gd::BitBoardPtr &position, Move move)
{
    position[gd::whitePawn][move.from] = 0;
    position[gd::whitePawn][move.to] = 1;
    position[gd::extraInfo][move.to + gd::d] = 1;
}
        void Movement::makeWhiteCommonMove(gd::BitBoardPtr &position, Move move)
{
    position[positionConverter.getPieceIndex(position, move.to  )][move.to] = 0;
    position[positionConverter.getPieceIndex(position, move.from)][move.to] = 1;
    position[positionConverter.getPieceIndex(position, move.from)][move.from] = 0;
}
    void Movement::makeBlackMove(gd::BitBoardPtr &position, Move move)
{
    if(position[gd::blackKing][move.from] == 1 && move.from == 59 && (move.to == 57 || move.to == 61))
        makeBlackCastle(position, move);
    else if(move.promotion != 0)
        makeBlackPromotion(position, move);
    else if(position[gd::blackPawn][move.from] == 1 && position[gd::emptySquare][move.to] == 1 &&(move.to - move.from == gd::dl || move.to - move.from == gd::dr))
        makeBlackEnPassant(position, move);
    else if(position[gd::blackPawn][move.from] == 1 && move.to - move.from == gd::dd)
        makeBlackDoublePush(position, move);
    else
        makeBlackCommonMove(position, move);
    positionFiller.fillBitBoard(position);
    positionFiller.updateExtraInfoAfterBlackMove(position);

}
        void Movement::makeBlackCastle(gd::BitBoardPtr &position, Move move)
{
    if(move.to == 57)
    {
        position[gd::blackKing][59] = 0;
        position[gd::blackKing][57] = 1;
        position[gd::blackRook][56] = 0;
        position[gd::blackRook][58] = 1;
        return;
    }
    if(move.to == 61)
    {
        position[gd::blackKing][59] = 0;
        position[gd::blackKing][61] = 1;
        position[gd::blackRook][63] = 0;
        position[gd::blackRook][60] = 1;
        return;
    }
}
        void Movement::makeBlackPromotion(gd::BitBoardPtr &position, Move move)
{
    position[gd::blackPawn][move.from] = 0;
    position[positionConverter.getPieceIndex(position, move.to)][move.to] = 0;
    switch(move.promotion)
    {
        case 1: position[gd::blackKnight][move.to] = 1; break;
        case 2: position[gd::blackBishop][move.to] = 1; break;
        case 3: position[gd::blackRook  ][move.to] = 1; break;
        case 4: position[gd::blackQueen ][move.to] = 1; break;
    }
}
        void Movement::makeBlackEnPassant(gd::BitBoardPtr &position, Move move)
{
    position[gd::blackPawn][move.from] = 0;
    position[gd::blackPawn][move.to] = 1;
    position[gd::whitePawn][move.to + gd::u] = 0;
}
        void Movement::makeBlackDoublePush(gd::BitBoardPtr &position, Move move)
{
    position[gd::blackPawn][move.from] = 0;
    position[gd::blackPawn][move.to] = 1;
    position[gd::extraInfo][move.to + gd::u] = 1;
}
        void Movement::makeBlackCommonMove(gd::BitBoardPtr &position, Move move)
{
    position[positionConverter.getPieceIndex(position, move.to  )][move.to] = 0;
    position[positionConverter.getPieceIndex(position, move.from)][move.to] = 1;
    position[positionConverter.getPieceIndex(position, move.from)][move.from] = 0;
}
Movement::Move Movement::getMove(const gd::BitBoardPtr &startPosition, const gd::BitBoardPtr &movedPosition)
{
    if(4 == (startPosition[gd::whitePiece] ^ movedPosition[gd::whitePiece]).count()) return getWhiteCastleMove(startPosition, movedPosition);
    if(4 == (startPosition[gd::blackPiece] ^ movedPosition[gd::blackPiece]).count()) return getBlackCastleMove(startPosition, movedPosition);
    if(1 == (startPosition[gd::whitePawn ] ^ movedPosition[gd::whitePawn ]).count()) return getWhitePromotionMove(startPosition, movedPosition);
    if(1 == (startPosition[gd::blackPawn ] ^ movedPosition[gd::blackPawn ]).count()) return getBlackPromotionMove(startPosition, movedPosition);
    if(2 == (startPosition[gd::whitePiece] ^ movedPosition[gd::whitePiece]).count()) return getWhiteEnPassantOrCommonMove(startPosition, movedPosition);
    if(2 == (startPosition[gd::blackPiece] ^ movedPosition[gd::blackPiece]).count()) return getBlackEnPassantOrCommonMove(startPosition, movedPosition);
    return Movement::Move{0, 0, 0};
}
    Movement::Move Movement::getWhiteCastleMove(const gd::BitBoardPtr &startPosition, const gd::BitBoardPtr &movedPosition)
{
    Movement::Move move;
    move.from = 3;
    if(movedPosition[gd::whiteKing][1])
        move.to = 1;
    if(movedPosition[gd::whiteKing][5])
        move.to = 5;
    move.promotion = 0;
    return move;
}
    Movement::Move Movement::getBlackCastleMove(const gd::BitBoardPtr &startPosition, const gd::BitBoardPtr &movedPosition)
{
    Movement::Move move;
    move.from = 59;
    if(movedPosition[gd::blackKing][57])
        move.to = 57;
    if(movedPosition[gd::blackKing][61])
        move.to = 61;
    move.promotion = 0;
    return move;
}
    Movement::Move Movement::getWhitePromotionMove(const gd::BitBoardPtr &startPosition, const gd::BitBoardPtr &movedPosition)
{
    Movement::Move move;
    move.from = findTrueBitIndex( startPosition[gd::whitePiece] & ~movedPosition[gd::whitePiece]);
    move.to   = findTrueBitIndex(~startPosition[gd::whitePiece] &  movedPosition[gd::whitePiece]);
    switch (positionConverter.getPieceIndex(movedPosition, move.to))
    {
        case gd::whiteKnight: move.promotion = 1; break;
        case gd::whiteBishop: move.promotion = 2; break;
        case gd::whiteRook:   move.promotion = 3; break;
        case gd::whiteQueen:  move.promotion = 4; break;
    }
    return move;
}
    Movement::Move Movement::getBlackPromotionMove(const gd::BitBoardPtr &startPosition, const gd::BitBoardPtr &movedPosition)
{
    Movement::Move move;
    move.from = findTrueBitIndex( startPosition[gd::blackPiece] & ~movedPosition[gd::blackPiece]);
    move.to   = findTrueBitIndex(~startPosition[gd::blackPiece] &  movedPosition[gd::blackPiece]);
    switch (positionConverter.getPieceIndex(movedPosition, move.to))
    {
        case gd::blackKnight: move.promotion = 1; break;
        case gd::blackBishop: move.promotion = 2; break;
        case gd::blackRook:   move.promotion = 3; break;
        case gd::blackQueen:  move.promotion = 4; break;
    }
    return move;
}
    Movement::Move Movement::getWhiteEnPassantOrCommonMove(const gd::BitBoardPtr &startPosition, const gd::BitBoardPtr &movedPosition)
{
    Movement::Move move;
    move.from = findTrueBitIndex( startPosition[gd::whitePiece] & ~movedPosition[gd::whitePiece]);
    move.to   = findTrueBitIndex(~startPosition[gd::whitePiece] &  movedPosition[gd::whitePiece]);
    move.promotion = 0;
    return move; 
}
    Movement::Move Movement::getBlackEnPassantOrCommonMove(const gd::BitBoardPtr &startPosition, const gd::BitBoardPtr &movedPosition)
{
    Movement::Move move;
    move.from = findTrueBitIndex( startPosition[gd::blackPiece] & ~movedPosition[gd::blackPiece]);
    move.to   = findTrueBitIndex(~startPosition[gd::blackPiece] &  movedPosition[gd::blackPiece]);
    move.promotion = 0;
    return move;
}
            uint8_t Movement::findTrueBitIndex(const std::bitset<64> &bitset)
{
    for (uint8_t i=0; i<64; i++)
        if (bitset[i])
            return i;
    return -1;
}
bool Movement::isMoveAllowed(gd::BitBoardPtr &startPosition, gd::BitBoardPtr &movedPosition)
{
    std::vector<gd::BitBoardPtr> children;
    children = whiteChildren.generateChildren(startPosition);
    for(auto element: children)
        if(transpositionTable.computeZobristKey(element) == transpositionTable.computeZobristKey(movedPosition))
        {
            whiteChildren.deleteChildren(children);
            return true;
        }
    whiteChildren.deleteChildren(children);
    children = blackChildren.generateChildren(startPosition);
    for(auto element: children)
        if(transpositionTable.computeZobristKey(element) == transpositionTable.computeZobristKey(movedPosition))
        {
            blackChildren.deleteChildren(children);
            return true;
        }
    blackChildren.deleteChildren(children);
    return false;
}
void Movement::check50MovesCounter(gd::BitBoardPtr &startPosition, gd::BitBoardPtr &movedPosition)
{
    if(startPosition[gd::emptySquare].count() != movedPosition[gd::emptySquare].count())
        movedPosition[gd::extraInfo] &= gd::RULE_OF_50_MOVES_MASK;
    else if(startPosition[gd::whitePawn] != movedPosition[gd::whitePawn] || startPosition[gd::blackPawn] != movedPosition[gd::blackPawn])
        movedPosition[gd::extraInfo] &= gd::RULE_OF_50_MOVES_MASK;
}

