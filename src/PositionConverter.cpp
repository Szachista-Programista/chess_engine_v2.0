#include "../include/PositionConverter.hpp"




gd::ChessBoardPtr PositionConverter::convertBitBoardTo8x8CharArray(gd::BitBoardPtr BBPtr)
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
void PositionConverter::convertStringToBitBoard(std::string content, gd::BitBoardPtr &ptr)
{
    try
    {
        for (int i = 0; i < 64; i++)
            switch (content[63-i])
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
std::string PositionConverter::convertChessBoardFileContentToString()
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



gd::BitBoardPtr PositionConverter::initializeBitBoardPtr()
{
    gd::BitBoardPtr bitBoard = loadBitBoard();
    return bitBoard;
}
    gd::BitBoardPtr PositionConverter::loadBitBoard()
{
    std::string fileContent = convertChessBoardFileContentToString();
    gd::BitBoardPtr bitBoard;
    try {bitBoard = new std::bitset<64>[gd::bitBoardSize]{};}
    catch(const std::bad_alloc &e)
    {
        gd::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    convertStringToBitBoard(fileContent, bitBoard);
    PositionFiller(true, true).fillBitBoard(bitBoard);
    PositionFiller(true, true).fillExtraInfo(bitBoard);
    return bitBoard;
}






