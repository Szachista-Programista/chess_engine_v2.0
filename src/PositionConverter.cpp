#include "../include/PositionConverter.hpp"


gd::ChessBoardPtr PositionConverter::convertBitBoardTo8x8CharArray(gd::BitBoardPtr &ptr)
{
    gd::ChessBoardPtr CBPtr;
    char piece;
    try {CBPtr = new char[8][8];}
    catch(const std::bad_alloc &e)
    {
        gd::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
        {
            piece = getPieceChar(getPieceIndex(ptr, i*8+j));
            if(piece == ' ')
                CBPtr[i][j] = '.';
            else
                CBPtr[i][j] = piece;
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
                case ' ': break;
                case 'P': ptr[gd::whitePawn  ].set(i); break;
                //case 'S':
                case 'N': ptr[gd::whiteKnight].set(i); break;
                //case 'G':
                case 'B': ptr[gd::whiteBishop].set(i); break;
                //case 'W':
                case 'R': ptr[gd::whiteRook  ].set(i); break;
                //case 'H':
                case 'Q': ptr[gd::whiteQueen ].set(i); break;
                case 'K': ptr[gd::whiteKing  ].set(i); break;
                case 'p': ptr[gd::blackPawn  ].set(i); break;
                //case 's':
                case 'n': ptr[gd::blackKnight].set(i); break;
                //case 'g':
                case 'b': ptr[gd::blackBishop].set(i); break;
                //case 'w':
                case 'r': ptr[gd::blackRook  ].set(i); break;
                //case 'h':
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
std::string PositionConverter::convertBitBoardTo_FEN_Notation(gd::BitBoardPtr &ptr)
{
    std::string FEN;
    FEN = getPieces(ptr) +' '+ 
          getTurnOfColor(ptr) +' '+
          getCastles(ptr) +' '+
          getEnPassant(ptr) +' '+
          getValueOf50MovesRule(ptr) +' '+
          getNumberOfMove(ptr);
    return FEN;
}
    std::string PositionConverter::getPieces(gd::BitBoardPtr &ptr)
{
    std::string notation{};
    int numberOfEmptySquare{};
    char piece;
    for (int i=63; i>=0; i--)
    {
        piece = getPieceChar(getPieceIndex(ptr, i));
        if (63>i && (63-i)%8 == 0)
        {
            if(numberOfEmptySquare)
            {
                notation += std::to_string(numberOfEmptySquare);
                numberOfEmptySquare = 0;
            }
            notation += '/';
        }
        if(piece == ' ')
            numberOfEmptySquare++;
        else
        {
            if(numberOfEmptySquare)
            {
                notation += std::to_string(numberOfEmptySquare);
                numberOfEmptySquare = 0;
            }
            notation += piece;
        }
    }
    if(numberOfEmptySquare)
        notation += std::to_string(numberOfEmptySquare);
    return notation;
}
        char PositionConverter::getPieceChar(gd::BitBoardIndex index)
{
    switch (index)
    {
        case gd::whitePawn:   return 'P';
        case gd::whiteKnight: return 'N';
        case gd::whiteBishop: return 'B';
        case gd::whiteRook:   return 'R';
        case gd::whiteQueen:  return 'Q';
        case gd::whiteKing:   return 'K';
        case gd::blackPawn:   return 'p';
        case gd::blackKnight: return 'n';
        case gd::blackBishop: return 'b';
        case gd::blackRook:   return 'r';
        case gd::blackQueen:  return 'q';
        case gd::blackKing:   return 'k';
        case gd::emptySquare: return ' ';
    }    
}
            gd::BitBoardIndex PositionConverter::getPieceIndex(gd::BitBoardPtr &ptr, uint8_t bit)
{
    for(auto element:{gd::whitePawn,
                      gd::whiteKnight,
                      gd::whiteBishop,
                      gd::whiteRook,
                      gd::whiteQueen,
                      gd::whiteKing,
                      gd::blackPawn,
                      gd::blackKnight,
                      gd::blackBishop,
                      gd::blackRook,
                      gd::blackQueen,
                      gd::blackKing,
                      gd::emptySquare,})

        if(ptr[element][bit])
            return element;
}
    char PositionConverter::getTurnOfColor(gd::BitBoardPtr &ptr)
{
    if(ptr[gd::extraInfo][15] == 1)
        return 'w';
    else
        return 'b';
}
    std::string PositionConverter::getCastles(gd::BitBoardPtr &ptr)
{
    std::string castles{};

    if(ptr[gd::extraInfo][0] == 1)
        castles += 'K';
    if(ptr[gd::extraInfo][7] == 1)
        castles += 'Q';
    if(ptr[gd::extraInfo][56] == 1)
        castles += 'k';
    if(ptr[gd::extraInfo][63] == 1)
        castles += 'q';
    if(castles.empty())
        castles += '-';
    return castles;
}
    std::string PositionConverter::getEnPassant(gd::BitBoardPtr &ptr)
{
    std::string enPassant{};
    uint8_t bit{};
    if((ptr[gd::extraInfo] & ~gd::WHITE_EN_PASSANT_MASK).any())
    {
        for(uint8_t i=47; i>39; i--)
            if(ptr[gd::extraInfo][i] == 1)
                bit = i;
    }
    else if((ptr[gd::extraInfo] & ~gd::BLACK_EN_PASSANT_MASK).any())
    {
        for(uint8_t i=23; i>15; i--)
            if(ptr[gd::extraInfo][i] == 1)
                bit = i;
    }
    if(bit)
    {
    char letter = 'a' + 7-bit%8;
    char digit  = ((bit/8 == 2)? '3': '6');
    enPassant += letter;
    enPassant += digit;
    }
    else
        enPassant = '-';
    return enPassant;
}
    std::string PositionConverter::getValueOf50MovesRule(gd::BitBoardPtr &ptr)
{
    uint64_t value{};
    for(uint8_t i=31; i>23; i--)
    {
        value <<= 1;
        if(ptr[gd::extraInfo][i])
            value += 1;
    }
    return std::to_string(value);
}
    std::string PositionConverter::getNumberOfMove(gd::BitBoardPtr &ptr)
{
    uint64_t value{};
    for(uint8_t i=39; i>31; i--)
    {
        value <<= 1;
        if(ptr[gd::extraInfo][i])
            value += 1;
    }
    value = value/2 + 1;
    return std::to_string(value);
}
gd::BitBoardPtr PositionConverter::convert_FEN_NotationToBitBoard(std::string FEN)
{
    gd::BitBoardPtr bitBoard;
    try {bitBoard = new std::bitset<64>[gd::bitBoardSize]{};}
    catch(const std::bad_alloc &e)
    {
        gd::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    std::string FEN_parts[6];
    for(int i=0; i<6; i++)
    {
        FEN_parts[i] = FEN.substr(0, FEN.find(' '));
        FEN.erase(0, FEN.find(' ')+1);
    }
    setPieces(bitBoard, FEN_parts[0]);
    setTurnOfColor(bitBoard, FEN_parts[1]);
    setCastles(bitBoard, FEN_parts[2]);
    setEnPassant(bitBoard, FEN_parts[3]);
    setValueOf50MovesRule(bitBoard, FEN_parts[4]);
    setNumberOfMove(bitBoard, FEN_parts[5]);
    positionFiller.fillBitBoard(bitBoard);
    return bitBoard;
}
    void PositionConverter::setPieces(gd::BitBoardPtr &ptr, std::string FEN_part)
{
    for(int i=0, bit=63; i<FEN_part.size(); i++)
    {
        switch(FEN_part[i])
        {
        case 'P':case 'N':case 'B':case 'R':case 'Q':case 'K':case 'p':case 'n':case 'b':case 'r':case 'q':case 'k':
            setPiece(ptr, bit, FEN_part[i]);
            bit--;
            break;
        case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':
            bit -= (int)FEN_part[i] - (int)'0';
            break;
        case '/':
            break;
        }
    }
}
        void PositionConverter::setPiece(gd::BitBoardPtr &ptr, uint8_t bit, char piece)
{
    switch (piece)
    {
        case 'P': ptr[gd::whitePawn  ].set(bit); break;
        case 'N': ptr[gd::whiteKnight].set(bit); break;
        case 'B': ptr[gd::whiteBishop].set(bit); break;
        case 'R': ptr[gd::whiteRook  ].set(bit); break;
        case 'Q': ptr[gd::whiteQueen ].set(bit); break;
        case 'K': ptr[gd::whiteKing  ].set(bit); break;
        case 'p': ptr[gd::blackPawn  ].set(bit); break;
        case 'n': ptr[gd::blackKnight].set(bit); break;
        case 'b': ptr[gd::blackBishop].set(bit); break;
        case 'r': ptr[gd::blackRook  ].set(bit); break;
        case 'q': ptr[gd::blackQueen ].set(bit); break;
        case 'k': ptr[gd::blackKing  ].set(bit); break;
    }
}
    void PositionConverter::setTurnOfColor(gd::BitBoardPtr &ptr, std::string FEN_part)
{
    if(FEN_part[0] == 'w')
        ptr[gd::extraInfo][15] = 1;
}
    void PositionConverter::setCastles(gd::BitBoardPtr &ptr, std::string FEN_part)
{
    if(FEN_part[0] == '-')
        return;
    for(int i=0; i<FEN_part.size(); i++)
        switch(FEN_part[i])
        {
        case 'K':
            ptr[gd::extraInfo][0] = 1;
            break;
        case 'Q':
            ptr[gd::extraInfo][7] = 1;
            break;
        case 'k':
            ptr[gd::extraInfo][56] = 1;
            break;
        case 'q':
            ptr[gd::extraInfo][63] = 1;
            break;
        }
}
    void PositionConverter::setEnPassant(gd::BitBoardPtr &ptr, std::string FEN_part)
{
    if(FEN_part[0] == '-')
        return;
    uint8_t bit{};
    uint8_t letterValue = FEN_part[0]-'a';
    uint8_t digitValue  = FEN_part[1]-'0';
    bit = digitValue*8 - 1 - letterValue;
    ptr[gd::extraInfo][bit] = 1;
}
    void PositionConverter::setValueOf50MovesRule(gd::BitBoardPtr &ptr, std::string FEN_part)
{
    uint64_t value = stoull(FEN_part);
    value &= 0xff;
    value <<= 24;
    ptr[gd::extraInfo] |= value;
}
    void PositionConverter::setNumberOfMove(gd::BitBoardPtr &ptr, std::string FEN_part)
{
    uint64_t value = stoull(FEN_part);
    if(ptr[gd::extraInfo][15] == 1)
        value = 2*value - 2;
    else
        value = 2*value - 1;
    value &= 0xff;
    value <<= 32;
    ptr[gd::extraInfo] |= value;
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
    positionFiller.fillBitBoard(bitBoard);
    positionFiller.fillExtraInfo(bitBoard);
    return bitBoard;
}
