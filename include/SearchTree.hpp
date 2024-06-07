#ifndef SEARCHTREE_HPP
#define SEARCHTREE_HPP

#include "Polyglot.hpp"

class SearchTree
{
        const bool black = 0;
        const bool white = 1;
        WhiteChildren whiteChildren;
        BlackChildren blackChildren;
        PositionEvaluator positionEvaluator;
        PositionFiller positionFiller;
        PositionSorter positionSorter;
        TranspositionTable transpositionTable;
        Polyglot polyglot;
        Movement movement;
        //********************
public: SearchTree();
        gd::BitBoardPtr iterativeDeepening(gd::BitBoardPtr position, const  bool color);
private:    std::vector<gd::EvaluedPosition> getPositions(const gd::BitBoardPtr position, const bool color);
            void deletePositions(std::vector<gd::EvaluedPosition> positions);
        int alphaBeta(const gd::BitBoardPtr position,const  uint8_t depth, int alpha, int beta, const bool color);


void yyy(const std::vector<gd::EvaluedPosition> &positions, int depth, std::chrono::milliseconds duration);
void xxx();


};
#endif //SEARCHTREE_HPP
