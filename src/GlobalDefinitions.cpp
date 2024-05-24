#include "../include/GlobalDefinitions.hpp"


gd::BitBoardPtr gd::copyBitBoard(const gd::BitBoardPtr orginal)
{
    gd::BitBoardPtr copy  = new std::bitset<64>[gd::bitBoardSize]{};
    for(uint8_t i=0; i<gd::bitBoardSize; i++)
        copy[i] = orginal[i];
    return copy;
}
