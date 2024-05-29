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
void PositionSorter::sortEvaluatedPositions(std::vector<gd::EvaluedPosition> &positions, bool color)
{
    if(color)
        sortEvaluatedPositionsDescending(positions);
    else
        sortEvaluatedPositionsAscending(positions);
}
void PositionSorter::sortEvaluatedPositionsDescending(std::vector<gd::EvaluedPosition> &positions)
{
    std::sort
    (
        positions.begin(),
        positions.end(),
        [](const gd::EvaluedPosition &ptrA, const gd::EvaluedPosition &ptrB) {return ptrA.eval > ptrB.eval;}
    );
}
void PositionSorter::sortEvaluatedPositionsAscending(std::vector<gd::EvaluedPosition> &positions)
{
    std::sort
    (
        positions.begin(),
        positions.end(),
        [](const gd::EvaluedPosition &ptrA, const gd::EvaluedPosition &ptrB) {return ptrA.eval < ptrB.eval;}
    );
}
