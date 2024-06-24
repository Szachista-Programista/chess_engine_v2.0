#ifndef POSITIONSORTER_HPP
#define POSITIONSORTER_HPP

#include "Polyglot.hpp"

class PositionSorter
{
        PositionEvaluator positionEvaluator;
        KillerMoves killerMoves;

        //********************
public: void sortPositionsDescending(std::vector<gd::BitBoardPtr> &positions);
        void sortPositionsAscending(std::vector<gd::BitBoardPtr> &positions);
        void extractKillerMoves(const gd::BitBoardPtr &startPosition, std::vector<gd::BitBoardPtr> &positions, uint8_t depth);
        void sortEvaluatedPositions(std::vector<gd::EvaluedPosition> &positions, bool color);
            void sortEvaluatedPositionsDescending(std::vector<gd::EvaluedPosition> &positions);
            void sortEvaluatedPositionsAscending(std::vector<gd::EvaluedPosition> &positions);


};
#endif //POSITIONSORTER_HPP
