#ifndef POSITIONSORTER_HPP
#define POSITIONSORTER_HPP

#include "PositionEvaluator.hpp"

class PositionSorter
{
        PositionEvaluator positionEvaluator;
        //********************
public: void sortPositionsDescending(std::vector<gd::BitBoardPtr> &positions);
        void sortPositionsAscending(std::vector<gd::BitBoardPtr> &positions);
        void sortEvaluatedPositions(std::vector<gd::EvaluedPosition> &positions, bool color);
            void sortEvaluatedPositionsDescending(std::vector<gd::EvaluedPosition> &positions);
            void sortEvaluatedPositionsAscending(std::vector<gd::EvaluedPosition> &positions);


};
#endif //POSITIONSORTER_HPP
