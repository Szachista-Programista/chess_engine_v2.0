#ifndef POSITION_EVALUATOR_HPP
#define POSITION_EVALUATOR_HPP

#include "GlobalDefinitions.hpp"
#include "PiecePositionPoints.hpp"



class PositionEvaluator
{
        uint8_t bit;
        //********************
public: int evaluatePosition(const gd::BitBoardPtr &ptr);

};
#endif //POSITION_EVALUATOR_HPP

