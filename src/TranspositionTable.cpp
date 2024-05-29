#include "../include/TranspositionTable.hpp"

TranspositionTable::TranspositionTable(): zobristTable(12, std::vector<uint64_t>(64))
{
    initZobristTable();
}
void TranspositionTable::initZobristTable()
{
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<uint64_t> dis;
    for (int i = 0; i < 12; ++i)
        for (int j = 0; j < 64; ++j)
            zobristTable[i][j] = dis(gen);
}
uint64_t TranspositionTable::computeZobristKey(const gd::BitBoardPtr &ptr)
{
    uint64_t hash{};
    for (int i=0; i<64; i++)
        if (int index = positionConverter.getPieceIndex(ptr, i); index != gd::emptySquare)
            hash ^= zobristTable[index][i];
    return hash;
}

