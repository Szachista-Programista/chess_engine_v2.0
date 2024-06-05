#include "../include/Polyglot.hpp"


Polyglot::Polyglot(std::string filename): polyglotBookFileName{filename}
{
    initPolyglotBook();
}
    void Polyglot::initPolyglotBook()
{
    loadPolyglotBook();
    swabPolyglotBookByteOrder();
}
        void Polyglot::loadPolyglotBook()
{
    std::ifstream file(polyglotBookFileName, std::ios::binary);
    /*if (!file) {
        std::cerr << "Failed to open book file: " << filename << std::endl;
        return;
    }*/
    PolyglotEntry entry;
    while (file.read(reinterpret_cast<char*>(&entry), sizeof(PolyglotEntry)))
        polyglotBook.push_back(entry);
    file.close();
}
        void Polyglot::swabPolyglotBookByteOrder()
{
    for(auto &element: polyglotBook)
    {
        swapByteOrder(element.key);
        swapByteOrder(element.move);
        swapByteOrder(element.weight);
    }
}
            void Polyglot::swapByteOrder(uint16_t &u16)
{
    u16 = (u16>>8) |
          (u16<<8);
}
            void Polyglot::swapByteOrder(uint32_t &u32)
{
    u32 = (u32>>24) |
         ((u32<< 8) & 0x00FF0000) |
         ((u32>> 8) & 0x0000FF00) |
          (u32<<24);
}
            void Polyglot::swapByteOrder(uint64_t &u64)
{
    u64 = (u64>>56) |
         ((u64<<40) & 0x00FF000000000000) |
         ((u64<<24) & 0x0000FF0000000000) |
         ((u64<< 8) & 0x000000FF00000000) |
         ((u64>> 8) & 0x00000000FF000000) |
         ((u64>>24) & 0x0000000000FF0000) |
         ((u64>>40) & 0x000000000000FF00) |
          (u64<<56);
}
bool Polyglot::checkPolyglotBook(const gd::BitBoardPtr &position, gd::BitBoardPtr &movedPosition)
{
    Movement::Move move;
    if(searchPolyglotBook(position, move))
    {
        movedPosition = gd::copyBitBoard(position);
        movement.makeMove(movedPosition, move);
        return true;
    }
    else
        return false;
}
    bool Polyglot::searchPolyglotBook(const gd::BitBoardPtr &ptr, Movement::Move &move)
{
    uint64_t key = generateKey(ptr);
    int bestMoveWeight{};
    for(int i=0; i<polyglotBook.size(); i++)
        if(polyglotBook[i].key == key)
            if(polyglotBook[i].weight > bestMoveWeight)
            {
                bestMoveWeight = polyglotBook[i].weight;
                move = getPolyglotMove(i);
            }
    if(bestMoveWeight > 0)
        return true;
    else
        return false;
}
        uint64_t Polyglot::generateKey(const gd::BitBoardPtr &ptr)
{
    uint64_t polyglotKey{};
    polyglotKey ^= generatePositionKey(ptr);
    polyglotKey ^= generateCastleKey(ptr);
    polyglotKey ^= generateEnPassantKey(ptr);
    polyglotKey ^= generateCurrentTurnKey(ptr);
    return polyglotKey;
}
            uint64_t Polyglot::generatePositionKey(const gd::BitBoardPtr &ptr)
{
    uint64_t key{};
    for (uint8_t bit=0; bit<64; bit++)
        if (ptr[gd::emptySquare][bit] == false)
            key ^= POLYGLOT_RANDOM[getPolyglotPieceIndex(ptr, bit)];
    return key;
}
                uint64_t Polyglot::getPolyglotPieceIndex(const gd::BitBoardPtr &ptr, uint8_t bit)
{
    return 64*getPieceNumber(ptr, bit) + 
            8*getRowNumber(bit)        + 
              getColumnNumber(bit);
}
                    uint64_t Polyglot::getPieceNumber(const gd::BitBoardPtr &ptr, uint8_t bit)
{
    switch (positionConverter.getPieceIndex(ptr, bit))
    {
        case gd::whitePawn:   return  1; break;
        case gd::whiteKnight: return  3; break;
        case gd::whiteBishop: return  5; break;
        case gd::whiteRook:   return  7; break;
        case gd::whiteQueen:  return  9; break;
        case gd::whiteKing:   return 11; break;
        case gd::blackPawn:   return  0; break;
        case gd::blackKnight: return  2; break;
        case gd::blackBishop: return  4; break;
        case gd::blackRook:   return  6; break;
        case gd::blackQueen:  return  8; break;
        case gd::blackKing:   return 10; break;
    }
}
                    uint64_t Polyglot::getRowNumber(uint8_t bit)
{
    return bit/8;
}
                    uint64_t Polyglot::getColumnNumber(uint8_t bit)
{
    return 7-bit%8;
}
            uint64_t Polyglot::generateCastleKey(const gd::BitBoardPtr &ptr)
{
    uint64_t key{};
    if (ptr[gd::extraInfo][ 0]) key ^= POLYGLOT_RANDOM[768];
    if (ptr[gd::extraInfo][ 7]) key ^= POLYGLOT_RANDOM[769];
    if (ptr[gd::extraInfo][56]) key ^= POLYGLOT_RANDOM[770];
    if (ptr[gd::extraInfo][63]) key ^= POLYGLOT_RANDOM[771];
    return key;
}
            uint64_t Polyglot::generateEnPassantKey(const gd::BitBoardPtr &ptr)
{
    uint64_t key{};
    for(uint8_t column=0; column<8; column++)
        if(ptr[gd::extraInfo][47-column] || ptr[gd::extraInfo][23-column])
        {
            key ^= POLYGLOT_RANDOM[772 + column];
            break;
        }
    return key;
}
            uint64_t Polyglot::generateCurrentTurnKey(const gd::BitBoardPtr &ptr)
{
    uint64_t key{};
    if(ptr[gd::extraInfo][15])
        key ^= POLYGLOT_RANDOM[780];
    return key;
}
        Movement::Move Polyglot::getPolyglotMove(int index)
{
    Movement::Move move;
    uint16_t polyglotMove = polyglotBook[index].move;

    uint8_t lineFrom   = polyglotMove>>9 & 7;
    uint8_t columnFrom = polyglotMove>>6 & 7;
    uint8_t lineTo     = polyglotMove>>3 & 7;
    uint8_t columnTo   = polyglotMove>>0 & 7;

    move.from = lineFrom*8 + 7-columnFrom;
    move.to   = lineTo  *8 + 7-columnTo;
    move.promotion = polyglotMove>>12 & 7;

    return move;
}



