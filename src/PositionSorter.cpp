#include "../include/PositionSorter.hpp"


void PositionSorter::sortPositionsDescending(std::vector<gd::BitBoardPtr> &positions)
{
    std::sort
    (
        positions.begin(),
        positions.end(),
        [this](const gd::BitBoardPtr &ptrA, const gd::BitBoardPtr &ptrB)
            {return positionEvaluator.evaluatePosition(ptrA) > positionEvaluator.evaluatePosition(ptrB);}
    );
}
void PositionSorter::sortPositionsAscending(std::vector<gd::BitBoardPtr> &positions)
{
    std::sort
    (
        positions.begin(),
        positions.end(),
        [this](const gd::BitBoardPtr &ptrA, const gd::BitBoardPtr &ptrB)
            {return positionEvaluator.evaluatePosition(ptrA) < positionEvaluator.evaluatePosition(ptrB);}
    );
}
void PositionSorter::sortEvaluatedPositionsDescending(std::vector<gd::EvaluedPosition> &positions)
{
    std::sort
    (
        positions.begin(),
        positions.end(),
        [/*this*/](const gd::EvaluedPosition &ptrA, const gd::EvaluedPosition &ptrB) {return ptrA.eval > ptrB.eval;}
    );
}
void PositionSorter::sortEvaluatedPositionsAscending(std::vector<gd::EvaluedPosition> &positions)
{
    std::sort
    (
        positions.begin(),
        positions.end(),
        [/*this*/](const gd::EvaluedPosition &ptrA, const gd::EvaluedPosition &ptrB) {return ptrA.eval < ptrB.eval;}
    );
}
