#include <iostream>
#include <bitset>
#include <fstream>

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
    blackPiece,
    anyPiece
};

struct errorType{std::string errorMessage;};
using BitBoardPtr = std::bitset<64>*;
using ChessBoardPtr = char(*)[8];

BitBoardPtr initializeBitBoardPtr();
    BitBoardPtr loadBitBoard();
        std::string readChessBoardFile();
        void rewriteFileContentToBitBoard(std::string fileContent, BitBoardPtr ptr);
    void computeBitBoard(BitBoardPtr ptr);
void writeChessboard(BitBoardPtr BBPtr);
    ChessBoardPtr rewriteBitBoardTo8x8CharArray(BitBoardPtr BBPtr);

int main()
{
    BitBoardPtr x = initializeBitBoardPtr();
    computeBitBoard(x);
    writeChessboard(x);
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
    try {bitBoard = new std::bitset<64>[20]{};}
    catch(const std::bad_alloc &e)
    {
        errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    rewriteFileContentToBitBoard(fileContent, bitBoard);
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
            switch (fileContent[i])
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
    ptr[whitePiece] = ptr[whitePawn]  | ptr[whiteKnight] | ptr[whiteBishop] | ptr[whiteRook] | ptr[whiteQueen] | ptr[whiteKing];
    ptr[blackPiece] = ptr[blackPawn]  | ptr[blackKnight] | ptr[blackBishop] | ptr[blackRook] | ptr[blackQueen] | ptr[blackKing];
    ptr[anyPiece]   = ptr[whitePiece] | ptr[blackPiece];
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
                if(BBPtr[k].test(63-i*8-j) == true)
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
