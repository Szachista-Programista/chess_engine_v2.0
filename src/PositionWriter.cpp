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
void PositionWriter::writeChessboard(std::string position, bool side)
{
    system("cls");
    writeBoard();
    writeBitNumbers();
    writePieces(position, side);
}
    void PositionWriter::writeBoard()
{   
    std::string a = "\033[48;2;163;91;23m" + std::string(11, ' ') + "\033[0m";
    std::string b = "\033[48;2;120;67;21m" + std::string(11, ' ') + "\033[0m";
    std::string abababab = a+b+a+b+a+b+a+b;
    std::string babababa = b+a+b+a+b+a+b+a;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<5; j++) std::cout<<abababab<<std::endl;
        for(int j=0; j<5; j++) std::cout<<babababa<<std::endl;
    }
}
    void PositionWriter::writeBitNumbers()
{
    int x;
    int y;
    int number;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            x = j*11+1;
            y = i*5+1;
            number = 63-i*8-j;
            std::cout<<"\033["<<y<<";"<<x<<"H";
            if((i+j)%2)
                std::cout<<"\033[48;2;120;67;21m";
            else
                std::cout<<"\033[48;2;163;91;23m";
            std::cout<<number;


        }

    std::cout<<"\033[0m";
}
    void PositionWriter::writePieces(std::string position, bool side)
{
    for(int i=0; i<64; i++)
        writePiece(position[side? i: 63-i], i%8, i/8);
    std::cout<<"\033[40;0H";}
        void PositionWriter::writePiece(char piece, int x, int y)
{

    if('A' <= piece && piece <= 'Z')
        std::cout<<"\033[7m";
    else if('a' <= piece && piece <= 'z')
        {}
    else
        return;
    x = x*11 + 3;
    y = y*5  + 2;
    for(int i=0; i<3; i++)
    {
        std::cout<<"\033["<<y+i<<";"<<x<<"H";
        std::cout<<std::string(7, ' ');
    }
    std::cout<<"\033["<<y+1<<";"<<x+3<<"H";
    std::cout<<piece;
    std::cout<<"\033[0m";
}


