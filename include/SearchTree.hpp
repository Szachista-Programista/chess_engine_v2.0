#ifndef SEARCHTREE_HPP
#define SEARCHTREE_HPP

#include "WhiteChildren.hpp"
#include "BlackChildren.hpp"

class SearchTree
{
public://///

    const bool black = 0;
    const bool white = 1;

    int licznik{};//////////

    WhiteChildren whiteChildren;
    BlackChildren blackChildren;
    PositionEvaluator positionEvaluator;
    PositionSorter positionSorter;
    //********************
    gd::BitBoardPtr findBestMove(const gd::BitBoardPtr position,const  uint8_t depth,const  bool color);
    gd::BitBoardPtr iterativeDeepening(const gd::BitBoardPtr position, const  uint8_t maxDepth, const  bool color);
        std::vector<gd::EvaluedPosition> generatePositions(const gd::BitBoardPtr position, const bool color);
    float alphaBeta(const gd::BitBoardPtr position,const  uint8_t depth, float alpha, float beta,const  bool color);
    gd::BitBoardPtr copyBitBoard(const gd::BitBoardPtr orginal)const;


};
#endif //SEARCHTREE_HPP
