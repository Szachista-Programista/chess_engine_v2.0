#include "../include/TranspositionTable.hpp"

TranspositionTable::TranspositionTable(): zobristTable(12, std::vector<uint64_t>(64))
{
    initZobristTable();
    transpositionTable = new TTEntry[TABLE_SIZE];
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
TranspositionTable::~TranspositionTable()
{
    delete[]transpositionTable;
}
uint64_t TranspositionTable::computeZobristKey(const gd::BitBoardPtr &ptr)
{
    uint64_t hash{};
    for (int i=0; i<64; i++)
        if (int index = positionConverter.getPieceIndex(ptr, i); index != gd::emptySquare)
            hash ^= zobristTable[index][i];
    return hash;
}
void TranspositionTable::storeTTEntry(uint64_t key, int depth, int score)
{
    int index = key % TABLE_SIZE;
    transpositionTable[index] = {key, depth, score};
}
bool TranspositionTable::probeTTEntry(uint64_t key, int depth, int &score)
{
    int index = key % TABLE_SIZE;
    if (transpositionTable[index].key == key  && transpositionTable[index].depth > depth)
    {
        //std::cout<<1;
        score = transpositionTable[index].score;
        return true;
    }        //std::cout<<0;

    return false;
}

