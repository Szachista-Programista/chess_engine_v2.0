#include "include/SearchTree.hpp"


#include <chrono>////////////

//using namespace std::chrono;/////////////////


gd::BitBoardPtr initializeBitBoardPtr();
    gd::BitBoardPtr loadBitBoard();
        std::string readChessBoardFile();
        void rewriteFileContentToBitBoard(std::string fileContent, gd::BitBoardPtr &ptr);
    void fillExtraInfo(gd::BitBoardPtr &ptr);
void writeChessboard(gd::BitBoardPtr BBPtr);
    gd::ChessBoardPtr rewriteBitBoardTo8x8CharArray(gd::BitBoardPtr BBPtr);
void writeBitBoard(const std::bitset<64> &bs);
int evaluatePosition(gd::BitBoardPtr &ptr);

int main()
{
    gd::BitBoardPtr x = initializeBitBoardPtr();
    writeChessboard(x);
    std::cout<<std::endl;


/////////////

    WhiteChildren wc;
    BlackChildren bc;

    std::vector<gd::BitBoardPtr> wChildren;
    std::vector<gd::BitBoardPtr> bChildren;

    wChildren = wc.getMoves(x, wChildren);
    bChildren = bc.getMoves(x, bChildren);

    std::cout<<"BIALY  MA: "<<(wChildren).size()<<" RUCHOW."<<std::endl;
    std::cout<<"CZARNY MA: "<<bChildren.size()<<" RUCHOW."<<std::endl;

    wc.deleteChildren(wChildren);
    bc.deleteChildren(bChildren);

    wChildren.clear();
    bChildren.clear();

/*
    unsigned long long iterations = 0;    auto start = std::chrono::steady_clock::now();    const int time_limit_seconds = 2;
    while (true)
    {

    iterations++;    auto current = std::chrono::steady_clock::now(); if (std::chrono::duration_cast<std::chrono::seconds>(current - start).count() >= time_limit_seconds) break;
    }
    std::cout << "Program wykonano przez " << time_limit_seconds << " sekundy." << std::endl << "Liczba wykonanych iteracji: " << iterations << std::endl;
*/
    return 0;
}

gd::BitBoardPtr initializeBitBoardPtr()
{
    gd::BitBoardPtr bitBoard = loadBitBoard();
    fillExtraInfo(bitBoard);
    return bitBoard;
}
    gd::BitBoardPtr loadBitBoard()
{
    std::string fileContent = readChessBoardFile();
    gd::BitBoardPtr bitBoard;
    try {bitBoard = new std::bitset<64>[gd::bitBoardSize]{};}
    catch(const std::bad_alloc &e)
    {
        gd::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    rewriteFileContentToBitBoard(fileContent, bitBoard);
    PositionFiller(true, true).fillBitBoard(bitBoard);
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
        gd::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    reading.close();
    return content;
}
        void rewriteFileContentToBitBoard(std::string fileContent, gd::BitBoardPtr &ptr)
{
    try
    {
        for (int i = 0; i < 64; i++)
            switch (fileContent[63-i])
            {
                case '*': break;
                case 'P': ptr[gd::whitePawn  ].set(i); break;
                case 'N': ptr[gd::whiteKnight].set(i); break;
                case 'B': ptr[gd::whiteBishop].set(i); break;
                case 'R': ptr[gd::whiteRook  ].set(i); break;
                case 'Q': ptr[gd::whiteQueen ].set(i); break;
                case 'K': ptr[gd::whiteKing  ].set(i); break;
                case 'p': ptr[gd::blackPawn  ].set(i); break;
                case 'n': ptr[gd::blackKnight].set(i); break;
                case 'b': ptr[gd::blackBishop].set(i); break;
                case 'r': ptr[gd::blackRook  ].set(i); break;
                case 'q': ptr[gd::blackQueen ].set(i); break;
                case 'k': ptr[gd::blackKing  ].set(i); break;
                default: throw std::runtime_error("Wrong 'chessboard.txt' content.");
            }
    }
    catch(const std::runtime_error &e)
    {
        gd::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
}
    void fillExtraInfo(gd::BitBoardPtr &ptr)
{
    if(ptr[gd::whiteKing][3] == true)
    {
        if(ptr[gd::whiteRook][7] == true)
            ptr[gd::extraInfo][7] = 1;
        if(ptr[gd::whiteRook][0] == true)
            ptr[gd::extraInfo][0] = 1;
    }
    if(ptr[gd::blackKing][59] == true)
    {
        if(ptr[gd::blackRook][63] == true)
            ptr[gd::extraInfo][63] = 1;
        if(ptr[gd::blackRook][56] == true)
            ptr[gd::extraInfo][56] = 1;
    }
}
void writeChessboard(gd::BitBoardPtr BBPtr)
{
    gd::ChessBoardPtr CBPtr = rewriteBitBoardTo8x8CharArray(BBPtr);

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
    gd::ChessBoardPtr rewriteBitBoardTo8x8CharArray(gd::BitBoardPtr BBPtr)
{
    gd::ChessBoardPtr CBPtr;
    try {CBPtr = new char[8][8];}
    catch(const std::bad_alloc &e)
    {
        gd::errorType x;
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
                        case gd::whitePawn:   CBPtr[i][j] = 'P'; k = 12; break;
                        case gd::whiteKnight: CBPtr[i][j] = 'N'; k = 12; break;
                        case gd::whiteBishop: CBPtr[i][j] = 'B'; k = 12; break;
                        case gd::whiteRook:   CBPtr[i][j] = 'R'; k = 12; break;
                        case gd::whiteQueen:  CBPtr[i][j] = 'Q'; k = 12; break;
                        case gd::whiteKing:   CBPtr[i][j] = 'K'; k = 12; break;
                        case gd::blackPawn:   CBPtr[i][j] = 'p'; k = 12; break;
                        case gd::blackKnight: CBPtr[i][j] = 'n'; k = 12; break;
                        case gd::blackBishop: CBPtr[i][j] = 'b'; k = 12; break;
                        case gd::blackRook:   CBPtr[i][j] = 'r'; k = 12; break;
                        case gd::blackQueen:  CBPtr[i][j] = 'q'; k = 12; break;
                        case gd::blackKing:   CBPtr[i][j] = 'k'; k = 12; break;
                    }
                if(k == 11)
                    CBPtr[i][j] = '.';
            }
    return CBPtr;
}
void writeBitBoard(const std::bitset<64> &bs)
{
    for (int i = 63; i >= 0; i--)
    {
        std::cout << bs[i] << " ";
        if(i%8 == 0)
            std::cout << std::endl;
    }
}
int evaluatePosition(gd::BitBoardPtr &ptr)
{
    return
     ptr[gd::whitePawn].count() + 3*ptr[gd::whiteKnight].count() + 3*ptr[gd::whiteBishop].count() + 5*ptr[gd::whiteRook].count() + 9*ptr[gd::whiteQueen].count()
    -ptr[gd::blackPawn].count() - 3*ptr[gd::blackKnight].count() - 3*ptr[gd::blackBishop].count() - 5*ptr[gd::blackRook].count() - 9*ptr[gd::blackQueen].count();
}


