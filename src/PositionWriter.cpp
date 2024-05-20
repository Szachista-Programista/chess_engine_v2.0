#include "../include/PositionWriter.hpp"



void PositionWriter::writeBitBoard(const std::bitset<64> &bs)
{
    for (int i = 63; i >= 0; i--)
    {
        std::cout << bs[i] << " ";
        if(i%8 == 0)
            std::cout << std::endl;
    }
}
void PositionWriter::writeBitBoard(const gd::BitBoardPtr &ptr)
{
    std::cout<<std::string(85,'^')<<std::endl<<std::endl;
    for(int i=0; i<gd::bitBoardSize; i++)
    {
        std::cout<<std::setw(2)<<(int)i<<"    >>> ";
        for (int j=63; j>=0; j--)
        {
            if (63>j && (63-j)%8 == 0)
                std::cout << '\'';
            std::cout << ptr[i][j];
        }
        std::cout<<" <<<"<<std::endl;
        if(i == 5 || i == 11)
            std::cout<<std::endl;
    }
    std::cout<<std::endl<<std::string(85,'^')<<std::endl;
}
void PositionWriter::writeChessboard(gd::BitBoardPtr BBPtr)
{
    gd::ChessBoardPtr CBPtr = positionConverter.convertBitBoardTo8x8CharArray(BBPtr);

    std::cout<<std::string(27,'\333')<<std::endl;
    std::cout<<std::string( 5,'\333')<<" 1 2 3 4 5 6 7 8 "<<std::string(5,'\333')<<std::endl;
    std::cout<<std::string(27,'\333')<<std::endl;
    for(int i=7; i>=0; i--)
    {
        std::cout<<std::string( 2,'\333')<<i+1<<std::string( 2,'\333');
        for(int j=7; j>=0; j--)
            std::cout<<' '<<CBPtr[i][j];
        std::cout<<' ';
        std::cout<<std::string( 2,'\333')<<i+1<<std::string( 2,'\333')<<std::endl;
    }
    std::cout<<std::string(27,'\333')<<std::endl;
    std::cout<<std::string( 5,'\333')<<" 1 2 3 4 5 6 7 8 "<<std::string(5,'\333')<<std::endl;
    std::cout<<std::string(27,'\333')<<std::endl;
    delete[]CBPtr;
}