#ifndef POSITIONSORTER_HPP
#define POSITIONSORTER_HPP

#include "GlobalDefinitions.hpp"

class PositionSorter
{
        //********************
public: void sortPositionsDescending(std::vector<gd::BitBoardPtr> &positions);
        void sortPositionsAscending(std::vector<gd::BitBoardPtr> &positions);
private:float evaluatePosition(const gd::BitBoardPtr &ptr)const;

};
#endif //POSITIONSORTER_HPP
