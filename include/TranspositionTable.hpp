#ifndef TRANSPOSITION_TABLE_HPP
#define TRANSPOSITION_TABLE_HPP

#include "PositionConverter.hpp"
#include "WhiteChildren.hpp"
#include "BlackChildren.hpp"

class TranspositionTable
{
        const int TABLE_SIZE = 1<<20;
        struct TTEntry{uint64_t key; int depth; int score;};
        TTEntry* transpositionTable;
        std::vector<std::vector<uint64_t>> zobristTable;
        PositionConverter positionConverter;
        //********************
public: TranspositionTable();
            void initZobristTable();
        ~TranspositionTable();
        uint64_t computeZobristKey(const gd::BitBoardPtr &ptr);
        void storeTTEntry(uint64_t key, int depth, int score);
        bool probeTTEntry(uint64_t key, int depth, int &score);
};
#endif //TRANSPOSITION_TABLE_HPP




/*
int alphaBeta(Position &pos, int depth, int alpha, int beta) {
    int score;
    int flag;
    Move bestMove;

    // Sprawdzenie w transpozycyjnej tablicy
    if (probeTTEntry(pos.zobristKey(), depth, score, flag, bestMove)) {
        if (flag == EXACT) {
            return score;
        } else if (flag == LOWERBOUND && score >= beta) {
            return score;
        } else if (flag == UPPERBOUND && score <= alpha) {
            return score;
        }
    }

    if (depth == 0) {
        return evaluate(pos);
    }

    vector<Move> moves = generateMoves(pos);
    int bestScore = -INFINITY;
    Move bestMoveLocal;

    for (Move move : moves) {
        pos.makeMove(move);
        int score = -alphaBeta(pos, depth - 1, -beta, -alpha);
        pos.undoMove(move);

        if (score > bestScore) {
            bestScore = score;
            bestMoveLocal = move;
        }

        alpha = max(alpha, score);
        if (alpha >= beta) {
            break;
        }
    }

    // Zapis do transpozycyjnej tablicy
    flag = (bestScore <= alpha) ? UPPERBOUND : (bestScore >= beta) ? LOWERBOUND : EXACT;
    storeTTEntry(pos.zobristKey(), depth, bestScore, flag, bestMoveLocal);

    return bestScore;
}
*/