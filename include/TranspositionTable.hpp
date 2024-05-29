#ifndef TRANSPOSITION_TABLE_HPP
#define TRANSPOSITION_TABLE_HPP

#include "PositionConverter.hpp"

class TranspositionTable
{public:///////////

        std::vector<std::vector<uint64_t>> zobristTable;
        PositionConverter positionConverter;
        //********************
        TranspositionTable();
        void initZobristTable();
uint64_t computeZobristKey(const gd::BitBoardPtr &ptr);
};
#endif //TRANSPOSITION_TABLE_HPP

