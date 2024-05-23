#ifndef SEARCHTREE_HPP
#define SEARCHTREE_HPP

#include "WhiteChildren.hpp"
#include "BlackChildren.hpp"

class SearchTree
{
public://///

    const bool black = 0;
    const bool white = 1;


    WhiteChildren whiteChildren;
    BlackChildren blackChildren;
    PositionEvaluator positionEvaluator;
    PositionSorter positionSorter;
    //********************
    gd::BitBoardPtr iterativeDeepening(const gd::BitBoardPtr position, const  uint8_t maxDepth, const  bool color);
        std::vector<gd::EvaluedPosition> getPositions(const gd::BitBoardPtr position, const bool color);
        void deletePositions(std::vector<gd::EvaluedPosition> positions);
    float alphaBeta(const gd::BitBoardPtr position,const  uint8_t depth, float alpha, float beta, const bool color);
    gd::BitBoardPtr copyBitBoard(const gd::BitBoardPtr orginal)const;






    gd::BitBoardPtr findByAlphaBeta(const gd::BitBoardPtr position,const  uint8_t depth,const  bool color);
        float alphaBetaX(const gd::BitBoardPtr position, const uint8_t depth, float alpha, float beta, const bool color);
    gd::BitBoardPtr findByMinimax(const gd::BitBoardPtr position,const  uint8_t depth,const  bool color);
        float minimax(const gd::BitBoardPtr position,const  uint8_t depth, const bool color);


};
#endif //SEARCHTREE_HPP
