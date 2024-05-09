#include <iostream>
#include <bitset>
#include <fstream>
//#include <thread>////////////
//#include <mutex>//////////
//#include <future>///////////////
#include <chrono>////////////


using namespace std;///////////////
using namespace std::chrono;/////////////////
//std::mutex whiteMutex;///////////////
//std::mutex blackMutex;/////////////////

enum BitBoardIndex
{
    whitePawn,
    whiteKnight,
    whiteBishop,
    whiteRook,
    whiteQueen,
    whiteKing,

    blackPawn,
    blackKnight,
    blackBishop,
    blackRook,
    blackQueen,
    blackKing,

    whitePiece,
    whiteCapturedSquare,
    blackPiece,
    blackCapturedSquare,
    anyPiece,
    emptySquare,
    bitBoardSize
};
enum Movements
{
    up = 8,
    upRight = 7,
    rightt = 1,
    downRight = 9,
    down = 8,
    downLeft = 7,
    leftt = 1,
    upLeft = 9,

    upUp = 16,
    downDown = 16,

    upUpRight = 15,
    upRightRight = 6,
    downRightRight = 10,
    downDownRight = 17,
    downDownLeft = 15,
    downLeftLeft = 6,
    upLeftLeft = 10,
    upUpLeft = 17
};


struct errorType{std::string errorMessage;};
using BitBoardPtr = std::bitset<64>*;
using ChessBoardPtr = char(*)[8];
const std::bitset<64> SINGLE_RIGHT_EDGE_MASK = 0xfefefefefefefefe;
const std::bitset<64> DOUBLE_RIGHT_EDGE_MASK = 0xfcfcfcfcfcfcfcfc;
const std::bitset<64> SINGLE_LEFT_EDGE_MASK  = 0x7f7f7f7f7f7f7f7f;
const std::bitset<64> DOUBLE_LEFT_EDGE_MASK  = 0x3f3f3f3f3f3f3f3f;

BitBoardPtr initializeBitBoardPtr();
    BitBoardPtr loadBitBoard();
        std::string readChessBoardFile();
        void rewriteFileContentToBitBoard(std::string fileContent, BitBoardPtr ptr);
void computeBitBoard(BitBoardPtr ptr);
    void computeSquareCapturedByWhite(BitBoardPtr ptr);
        void computeSquareCapturedByWhitePawn(BitBoardPtr ptr);
        void computeSquareCapturedByWhiteKnight(BitBoardPtr ptr);
        void computeSquareCapturedByWhiteBishop(BitBoardPtr ptr);
        void computeSquareCapturedByWhiteBishopRook(BitBoardPtr ptr);
        void computeSquareCapturedByWhiteQueen(BitBoardPtr ptr);
        void computeSquareCapturedByWhiteKing(BitBoardPtr ptr);
    void computeSquareCapturedByBlack(BitBoardPtr ptr);
        void computeSquareCapturedByBlackPawn(BitBoardPtr ptr);
        void computeSquareCapturedByBlackKnight(BitBoardPtr ptr);
        void computeSquareCapturedByBlackBishop(BitBoardPtr ptr);
        void computeSquareCapturedByBlackBishopRook(BitBoardPtr ptr);
        void computeSquareCapturedByBlackQueen(BitBoardPtr ptr);
        void computeSquareCapturedByBlackKing(BitBoardPtr ptr);
void writeChessboard(BitBoardPtr BBPtr);
    ChessBoardPtr rewriteBitBoardTo8x8CharArray(BitBoardPtr BBPtr);
void writeBitSet(const std::bitset<64> &bs);
bool isWhiteKingChecked(BitBoardPtr ptr);
bool isBlackKingChecked(BitBoardPtr ptr);


int main()
{
    BitBoardPtr x = initializeBitBoardPtr();
    writeChessboard(x);

   /*
    unsigned long long iterations = 0;    auto start = std::chrono::steady_clock::now();    const int time_limit_seconds = 2;
    while (true)
    {
        computeBitBoard(x);

    iterations++;    auto current = std::chrono::steady_clock::now(); if (std::chrono::duration_cast<std::chrono::seconds>(current - start).count() >= time_limit_seconds) break;
    }
    std::cout << "Program wykonano przez " << time_limit_seconds << " sekundy." << std::endl << "Liczba wykonanych iteracji: " << iterations << std::endl;
    */

 /* for(int i=0; i<bitBoardSize; i++)
    {
        std::cout<<"//////////////////////////////////////////////"<<std::endl<<">>>   "<<i<<"   <<<"<<std::endl;
        writeBitSet(x[i]);

    }*/



    return 0;
}

BitBoardPtr initializeBitBoardPtr()
{
    BitBoardPtr bitBoard = loadBitBoard();


    return bitBoard;
}
    BitBoardPtr loadBitBoard()
{
    std::string fileContent = readChessBoardFile();
    BitBoardPtr bitBoard;
    try {bitBoard = new std::bitset<64>[bitBoardSize]{};}
    catch(const std::bad_alloc &e)
    {
        errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    rewriteFileContentToBitBoard(fileContent, bitBoard);
    computeBitBoard(bitBoard);
    return bitBoard;
}
        std::string readChessBoardFile()
{
    std::ifstream reading;
    std::string line;
    std::string content{};
    reading.open("chessboard.txt");
    try
    {
        if (!reading.is_open())
            throw std::ifstream::failure("The file 'chessboard.txt' cannot be opened .");
        for(int i=0; i<8; i++)
        {
            if (!getline(reading, line))
                throw std::ifstream::failure("Error reading character from 'chessboard.txt' file .");
            content += line;
        }
    }
    catch(const std::ifstream::failure &e)
    {
        errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    reading.close();
    return content;
}
        void rewriteFileContentToBitBoard(std::string fileContent, BitBoardPtr ptr)
{
    try
    {
        for (int i = 0; i < 64; i++)
            switch (fileContent[63-i])
            {
                case '*': break;
                case 'P': ptr[whitePawn  ].set(i); break;
                case 'N': ptr[whiteKnight].set(i); break;
                case 'B': ptr[whiteBishop].set(i); break;
                case 'R': ptr[whiteRook  ].set(i); break;
                case 'Q': ptr[whiteQueen ].set(i); break;
                case 'K': ptr[whiteKing  ].set(i); break;
                case 'p': ptr[blackPawn  ].set(i); break;
                case 'n': ptr[blackKnight].set(i); break;
                case 'b': ptr[blackBishop].set(i); break;
                case 'r': ptr[blackRook  ].set(i); break;
                case 'q': ptr[blackQueen ].set(i); break;
                case 'k': ptr[blackKing  ].set(i); break;
                default: throw std::runtime_error("Wrong 'chessboard.txt' content.");
            }
    }
    catch(const std::runtime_error &e)
    {
        errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
}
void computeBitBoard(BitBoardPtr ptr)
{
    ptr[whitePiece]  = ptr[whitePawn]  | ptr[whiteKnight] | ptr[whiteBishop] | ptr[whiteRook] | ptr[whiteQueen] | ptr[whiteKing];
    ptr[blackPiece]  = ptr[blackPawn]  | ptr[blackKnight] | ptr[blackBishop] | ptr[blackRook] | ptr[blackQueen] | ptr[blackKing];
    ptr[anyPiece]    = ptr[whitePiece] | ptr[blackPiece];
    ptr[emptySquare] = ~ptr[anyPiece];

    computeSquareCapturedByWhite(ptr);
    computeSquareCapturedByBlack(ptr);
}
    void computeSquareCapturedByWhite(BitBoardPtr ptr)
{
    computeSquareCapturedByWhitePawn(ptr);
    computeSquareCapturedByWhiteKnight(ptr);
    computeSquareCapturedByWhiteBishop(ptr);
    computeSquareCapturedByWhiteBishopRook(ptr);
    computeSquareCapturedByWhiteQueen(ptr);
    computeSquareCapturedByWhiteKing(ptr);
}
        void computeSquareCapturedByWhitePawn(BitBoardPtr ptr)
{
    ptr[whiteCapturedSquare] |= (ptr[whitePawn] << upLeft)  & SINGLE_RIGHT_EDGE_MASK;
    ptr[whiteCapturedSquare] |= (ptr[whitePawn] << upRight) & SINGLE_LEFT_EDGE_MASK;
}
        void computeSquareCapturedByWhiteKnight(BitBoardPtr ptr)
{
    ptr[whiteCapturedSquare] |= (ptr[whiteKnight] << upUpRight)      & SINGLE_LEFT_EDGE_MASK;
    ptr[whiteCapturedSquare] |= (ptr[whiteKnight] << upRightRight)   & DOUBLE_LEFT_EDGE_MASK;
    ptr[whiteCapturedSquare] |= (ptr[whiteKnight] >> downRightRight) & DOUBLE_LEFT_EDGE_MASK;
    ptr[whiteCapturedSquare] |= (ptr[whiteKnight] >> downDownRight)  & SINGLE_LEFT_EDGE_MASK;
    ptr[whiteCapturedSquare] |= (ptr[whiteKnight] >> downDownLeft)   & SINGLE_RIGHT_EDGE_MASK;
    ptr[whiteCapturedSquare] |= (ptr[whiteKnight] >> downLeftLeft)   & DOUBLE_RIGHT_EDGE_MASK;
    ptr[whiteCapturedSquare] |= (ptr[whiteKnight] << upLeftLeft)     & DOUBLE_RIGHT_EDGE_MASK;
    ptr[whiteCapturedSquare] |= (ptr[whiteKnight] << upUpLeft)       & SINGLE_RIGHT_EDGE_MASK;
}
        void computeSquareCapturedByWhiteBishop(BitBoardPtr ptr)
{
    std::bitset<64> urMove = ptr[whiteBishop]; //u-up/r-right/d-down/l-left
    std::bitset<64> drMove = ptr[whiteBishop];
    std::bitset<64> dlMove = ptr[whiteBishop];
    std::bitset<64> ulMove = ptr[whiteBishop];

    while((urMove | drMove | dlMove | ulMove).any())
    {
        urMove = (urMove << upRight)   & SINGLE_LEFT_EDGE_MASK;
        drMove = (drMove >> downRight) & SINGLE_LEFT_EDGE_MASK;
        dlMove = (dlMove >> downLeft)  & SINGLE_RIGHT_EDGE_MASK;
        ulMove = (ulMove << upLeft)    & SINGLE_RIGHT_EDGE_MASK;

        ptr[whiteCapturedSquare] |= urMove | drMove | dlMove | ulMove;

        urMove &= ptr[emptySquare];
        drMove &= ptr[emptySquare];
        dlMove &= ptr[emptySquare];
        ulMove &= ptr[emptySquare];
    }
}
        void computeSquareCapturedByWhiteBishopRook(BitBoardPtr ptr)
{
    std::bitset<64> uMove = ptr[whiteRook]; //u-up/r-right/d-down/l-left
    std::bitset<64> rMove = ptr[whiteRook];
    std::bitset<64> dMove = ptr[whiteRook];
    std::bitset<64> lMove = ptr[whiteRook];

    while((uMove | rMove | dMove | lMove).any())
    {
        uMove = (uMove << up);
        rMove = (rMove >> rightt) & SINGLE_LEFT_EDGE_MASK;
        dMove = (dMove >> down);
        lMove = (lMove << leftt)  & SINGLE_RIGHT_EDGE_MASK;

        ptr[whiteCapturedSquare] |= uMove | rMove | dMove | lMove;

        uMove &= ptr[emptySquare];
        rMove &= ptr[emptySquare];
        dMove &= ptr[emptySquare];
        lMove &= ptr[emptySquare];
    }
}
        void computeSquareCapturedByWhiteQueen(BitBoardPtr ptr)
{
    std::bitset<64> uMove  = ptr[whiteQueen]; //u-up/r-right/d-down/l-left
    std::bitset<64> urMove = ptr[whiteQueen];
    std::bitset<64> rMove  = ptr[whiteQueen];
    std::bitset<64> drMove = ptr[whiteQueen];
    std::bitset<64> dMove  = ptr[whiteQueen];
    std::bitset<64> dlMove = ptr[whiteQueen];
    std::bitset<64> lMove  = ptr[whiteQueen];
    std::bitset<64> ulMove = ptr[whiteQueen];

    while((uMove | urMove | rMove | drMove | dMove | dlMove | lMove | ulMove).any())
    {
        uMove  = (uMove  << up);
        urMove = (urMove << upRight)   & SINGLE_LEFT_EDGE_MASK;
        rMove  = (rMove  >> rightt)    & SINGLE_LEFT_EDGE_MASK;
        drMove = (drMove >> downRight) & SINGLE_LEFT_EDGE_MASK;
        dMove  = (dMove  >> down);
        dlMove = (dlMove >> downLeft)  & SINGLE_RIGHT_EDGE_MASK;
        lMove  = (lMove  << leftt)     & SINGLE_RIGHT_EDGE_MASK;
        ulMove = (ulMove << upLeft)    & SINGLE_RIGHT_EDGE_MASK;

        ptr[whiteCapturedSquare] |= uMove | urMove | rMove | drMove | dMove | dlMove | lMove | ulMove;

        uMove  &= ptr[emptySquare];
        urMove &= ptr[emptySquare];
        rMove  &= ptr[emptySquare];
        drMove &= ptr[emptySquare];
        dMove  &= ptr[emptySquare];
        dlMove &= ptr[emptySquare];
        lMove  &= ptr[emptySquare];
        ulMove &= ptr[emptySquare];
    }
}
        void computeSquareCapturedByWhiteKing(BitBoardPtr ptr)
{
    ptr[whiteCapturedSquare] |= (ptr[whiteKing] << up);
    ptr[whiteCapturedSquare] |= (ptr[whiteKing] << upRight)   & SINGLE_LEFT_EDGE_MASK;
    ptr[whiteCapturedSquare] |= (ptr[whiteKing] >> rightt)    & SINGLE_LEFT_EDGE_MASK;
    ptr[whiteCapturedSquare] |= (ptr[whiteKing] >> downRight) & SINGLE_LEFT_EDGE_MASK;
    ptr[whiteCapturedSquare] |= (ptr[whiteKing] >> down);
    ptr[whiteCapturedSquare] |= (ptr[whiteKing] >> downLeft)  & SINGLE_RIGHT_EDGE_MASK;
    ptr[whiteCapturedSquare] |= (ptr[whiteKing] << leftt)     & SINGLE_RIGHT_EDGE_MASK;
    ptr[whiteCapturedSquare] |= (ptr[whiteKing] << upLeft)    & SINGLE_RIGHT_EDGE_MASK;
}
    void computeSquareCapturedByBlack(BitBoardPtr ptr)
{
    computeSquareCapturedByBlackPawn(ptr);
    computeSquareCapturedByBlackKnight(ptr);
    computeSquareCapturedByBlackBishop(ptr);
    computeSquareCapturedByBlackBishopRook(ptr);
    computeSquareCapturedByBlackQueen(ptr);
    computeSquareCapturedByBlackKing(ptr);
}
        void computeSquareCapturedByBlackPawn(BitBoardPtr ptr)
{
    ptr[blackCapturedSquare] |= (ptr[blackPawn] >> downRight) & SINGLE_LEFT_EDGE_MASK;
    ptr[blackCapturedSquare] |= (ptr[blackPawn] >> downLeft) & SINGLE_RIGHT_EDGE_MASK;
}
        void computeSquareCapturedByBlackKnight(BitBoardPtr ptr)
{
    ptr[blackCapturedSquare] |= (ptr[blackKnight] << upUpRight)      & SINGLE_LEFT_EDGE_MASK;
    ptr[blackCapturedSquare] |= (ptr[blackKnight] << upRightRight)   & DOUBLE_LEFT_EDGE_MASK;
    ptr[blackCapturedSquare] |= (ptr[blackKnight] >> downRightRight) & DOUBLE_LEFT_EDGE_MASK;
    ptr[blackCapturedSquare] |= (ptr[blackKnight] >> downDownRight)  & SINGLE_LEFT_EDGE_MASK;
    ptr[blackCapturedSquare] |= (ptr[blackKnight] >> downDownLeft)   & SINGLE_RIGHT_EDGE_MASK;
    ptr[blackCapturedSquare] |= (ptr[blackKnight] >> downLeftLeft)   & DOUBLE_RIGHT_EDGE_MASK;
    ptr[blackCapturedSquare] |= (ptr[blackKnight] << upLeftLeft)     & DOUBLE_RIGHT_EDGE_MASK;
    ptr[blackCapturedSquare] |= (ptr[blackKnight] << upUpLeft)       & SINGLE_RIGHT_EDGE_MASK;
}
        void computeSquareCapturedByBlackBishop(BitBoardPtr ptr)
{
    std::bitset<64> urMove = ptr[blackBishop]; //u-up/r-right/d-down/l-left
    std::bitset<64> drMove = ptr[blackBishop];
    std::bitset<64> dlMove = ptr[blackBishop];
    std::bitset<64> ulMove = ptr[blackBishop];

    while((urMove | drMove | dlMove | ulMove).any())
    {
        urMove = (urMove << upRight)   & SINGLE_LEFT_EDGE_MASK;
        drMove = (drMove >> downRight) & SINGLE_LEFT_EDGE_MASK;
        dlMove = (dlMove >> downLeft)  & SINGLE_RIGHT_EDGE_MASK;
        ulMove = (ulMove << upLeft)    & SINGLE_RIGHT_EDGE_MASK;

        ptr[blackCapturedSquare] |= urMove | drMove | dlMove | ulMove;

        urMove &= ptr[emptySquare];
        drMove &= ptr[emptySquare];
        dlMove &= ptr[emptySquare];
        ulMove &= ptr[emptySquare];
    }
}
        void computeSquareCapturedByBlackBishopRook(BitBoardPtr ptr)
{
    std::bitset<64> uMove = ptr[blackRook]; //u-up/r-right/d-down/l-left
    std::bitset<64> rMove = ptr[blackRook];
    std::bitset<64> dMove = ptr[blackRook];
    std::bitset<64> lMove = ptr[blackRook];

    while((uMove | rMove | dMove | lMove).any())
    {
        uMove = (uMove << up);
        rMove = (rMove >> rightt) & SINGLE_LEFT_EDGE_MASK;
        dMove = (dMove >> down);
        lMove = (lMove << leftt)  & SINGLE_RIGHT_EDGE_MASK;

        ptr[blackCapturedSquare] |= uMove | rMove | dMove | lMove;

        uMove &= ptr[emptySquare];
        rMove &= ptr[emptySquare];
        dMove &= ptr[emptySquare];
        lMove &= ptr[emptySquare];
    }
}
        void computeSquareCapturedByBlackQueen(BitBoardPtr ptr)
{
    std::bitset<64> uMove  = ptr[blackQueen]; //u-up/r-right/d-down/l-left
    std::bitset<64> urMove = ptr[blackQueen];
    std::bitset<64> rMove  = ptr[blackQueen];
    std::bitset<64> drMove = ptr[blackQueen];
    std::bitset<64> dMove  = ptr[blackQueen];
    std::bitset<64> dlMove = ptr[blackQueen];
    std::bitset<64> lMove  = ptr[blackQueen];
    std::bitset<64> ulMove = ptr[blackQueen];

    while((uMove | urMove | rMove | drMove | dMove | dlMove | lMove | ulMove).any())
    {
        uMove  = (uMove  << up);
        urMove = (urMove << upRight)   & SINGLE_LEFT_EDGE_MASK;
        rMove  = (rMove  >> rightt)    & SINGLE_LEFT_EDGE_MASK;
        drMove = (drMove >> downRight) & SINGLE_LEFT_EDGE_MASK;
        dMove  = (dMove  >> down);
        dlMove = (dlMove >> downLeft)  & SINGLE_RIGHT_EDGE_MASK;
        lMove  = (lMove  << leftt)     & SINGLE_RIGHT_EDGE_MASK;
        ulMove = (ulMove << upLeft)    & SINGLE_RIGHT_EDGE_MASK;

        ptr[blackCapturedSquare] |= uMove | urMove | rMove | drMove | dMove | dlMove | lMove | ulMove;

        uMove  &= ptr[emptySquare];
        urMove &= ptr[emptySquare];
        rMove  &= ptr[emptySquare];
        drMove &= ptr[emptySquare];
        dMove  &= ptr[emptySquare];
        dlMove &= ptr[emptySquare];
        lMove  &= ptr[emptySquare];
        ulMove &= ptr[emptySquare];
    }
}
        void computeSquareCapturedByBlackKing(BitBoardPtr ptr)
{
    ptr[blackCapturedSquare] |= (ptr[blackKing] << up);
    ptr[blackCapturedSquare] |= (ptr[blackKing] << upRight) & SINGLE_LEFT_EDGE_MASK;
    ptr[blackCapturedSquare] |= (ptr[blackKing] >> rightt) & SINGLE_LEFT_EDGE_MASK;
    ptr[blackCapturedSquare] |= (ptr[blackKing] >> downRight) & SINGLE_LEFT_EDGE_MASK;
    ptr[blackCapturedSquare] |= (ptr[blackKing] >> down);
    ptr[blackCapturedSquare] |= (ptr[blackKing] >> downLeft) & SINGLE_RIGHT_EDGE_MASK;
    ptr[blackCapturedSquare] |= (ptr[blackKing] << leftt) & SINGLE_RIGHT_EDGE_MASK;
    ptr[blackCapturedSquare] |= (ptr[blackKing] << upLeft) & SINGLE_RIGHT_EDGE_MASK;
}
void writeChessboard(BitBoardPtr BBPtr)
{
    ChessBoardPtr CBPtr = rewriteBitBoardTo8x8CharArray(BBPtr);

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
    ChessBoardPtr rewriteBitBoardTo8x8CharArray(BitBoardPtr BBPtr)
{
    ChessBoardPtr CBPtr;
    try {CBPtr = new char[8][8];}
    catch(const std::bad_alloc &e)
    {
        errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 12; k++)
            {
                if(BBPtr[k].test(i*8+j) == true)
                    switch (k)
                    {
                        case whitePawn:   CBPtr[i][j] = 'P'; k = 12; break;
                        case whiteKnight: CBPtr[i][j] = 'N'; k = 12; break;
                        case whiteBishop: CBPtr[i][j] = 'B'; k = 12; break;
                        case whiteRook:   CBPtr[i][j] = 'R'; k = 12; break;
                        case whiteQueen:  CBPtr[i][j] = 'Q'; k = 12; break;
                        case whiteKing:   CBPtr[i][j] = 'K'; k = 12; break;
                        case blackPawn:   CBPtr[i][j] = 'p'; k = 12; break;
                        case blackKnight: CBPtr[i][j] = 'n'; k = 12; break;
                        case blackBishop: CBPtr[i][j] = 'b'; k = 12; break;
                        case blackRook:   CBPtr[i][j] = 'r'; k = 12; break;
                        case blackQueen:  CBPtr[i][j] = 'q'; k = 12; break;
                        case blackKing:   CBPtr[i][j] = 'k'; k = 12; break;
                    }
                if(k == 11)
                    CBPtr[i][j] = '.';
            }
    return CBPtr;
}
void writeBitSet(const std::bitset<64> &bs)
{
    for (int i = 63; i >= 0; i--)
    {
        std::cout << bs[i] << " ";
        if(i%8 == 0)
            std::cout << std::endl;
    }
}
bool isWhiteKingChecked(BitBoardPtr ptr)
{
    return (ptr[whiteKing] & ptr[blackCapturedSquare]).any();
}
bool isBlackKingChecked(BitBoardPtr ptr)
{
    return (ptr[blackKing] & ptr[whiteCapturedSquare]).any();
}
