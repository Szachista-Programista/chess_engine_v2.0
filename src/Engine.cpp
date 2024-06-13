#include "../include/Engine.h"

Engine::Engine(bool k): color{k}, playService{k}
{
    globalType::gameStage        = globalType::opening;
    comparativeChessboardPointer = loadPiecesArrangement();
    workingChessboardPointer     = loadPiecesArrangement();
    setArrangements(workingChessboardPointer);
}
    globalType::chessboardPointer Engine::loadPiecesArrangement()
{
    std::ifstream reading;
    std::string line;
    globalType::chessboardPointer chessboard;
    try
    {
        chessboard = new char[8][8];
    }
    catch(const std::bad_alloc &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    try
    {
        reading.open("resources/chessboard.txt");
        if (!reading.is_open())
            throw std::ifstream::failure("The file 'chessboard.txt' cannot be opened .");

        for(int i=0; i<8; i++)
        {
            if (!getline(reading, line))
                throw std::ifstream::failure("Error reading character from 'chessboard.txt' file .");
            for(int j=0; j<8; j++)
                if(line[j] == '*')
                    chessboard[i][j] = ' ';
                else if(line[j] == '.')
                {
                    if(i==0) {
                        if(j==3) chessboard[i][j] = color?'k':'q';
                        if(j==4) chessboard[i][j] = color?'q':'k';
                    }
                    if(i==7) {
                        if(j==3) chessboard[i][j] = color?'K':'Q';
                        if(j==4) chessboard[i][j] = color?'Q':'K';
                    }
                }
                else
                    chessboard[i][j] = line[j];
        }
    }
    catch(const std::ifstream::failure &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    reading.close();
    return chessboard;
}
Engine::~Engine()noexcept
{
    delete[]comparativeChessboardPointer;
    delete[]workingChessboardPointer;
    clearArrangements();
}
    void Engine::clearArrangements()noexcept
{
    for(auto& element: arrangements)
        delete[]element;
    controlNumbersOfArrangements.clear();
    arrangements.clear();
}
bool Engine::canUserMakeSuchMove(int userMoveCode)
{
     Movement::Move move = codeToMove(userMoveCode)
    positionConverter.



}

int Engine::makeMove                         (int userMoveCode)
{
    getEngineReadyForMove(userMoveCode);
    arrangeServiceAfterUserMove(userMoveCode);
    if( ! movement.gameOver)
        switch(globalType::gameStage)
        {
            case globalType::opening:     makeOpeningMove();    break;
            case globalType::middlegame:  makeMiddlegameMove(); break;
            case globalType::endgame:     makeEndgameMove();    break;
        }
    if( ! movement.gameOver)
        arrangeServiceAfterEngineMove();
    return engineMoveCoding();
}
    void Engine::getEngineReadyForMove       (int userMoveCode)
{
    movementNumber++;
    decipherUserMove(userMoveCode); // changes e.g. 4456 into u.fromY u.toY u.fromX u.toX
    markUserMoveOnChessboard(userMoveCode); // marks u.fromY u.toY u.fromX u.toX into comparativeChessboardPointer and workingChessboardPointer
}
        void Engine::markUserMoveOnChessboard(int userMoveCode)
{
    try
    {
        if (u.fromX < 0 || 7 < u.fromX || u.fromY < 0 || 7 < u.fromY || u.toX < 0 || 7 < u.toX || u.toY < 0 || 7 < u.toY)
            throw std::runtime_error("User movement coordinates out of range.");
        if (comparativeChessboardPointer == nullptr || workingChessboardPointer == nullptr)
            throw std::runtime_error("Nullptr of the chessboard.");
    }
    catch(const std::runtime_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    if(userMoveCode == 10000)
        return;
    char movedPiece = workingChessboardPointer[u.fromY][u.fromX];

    if(movedPiece == 'p' && u.fromY == 4 && u.fromX != u.toX && workingChessboardPointer[u.toY][u.toX] == ' ') //maby en passant
        comparativeChessboardPointer[u.fromY][u.toX] = workingChessboardPointer[u.fromY][u.toX] = ' ';

    comparativeChessboardPointer[u.toY][u.toX]     = workingChessboardPointer[u.toY][u.toX]     = workingChessboardPointer[u.fromY][u.fromX];
    comparativeChessboardPointer[u.fromY][u.fromX] = workingChessboardPointer[u.fromY][u.fromX] = ' ';

    if(promotionCode)
        switch(promotionCode)
        {
            case 1: comparativeChessboardPointer[u.toY][u.toX] = workingChessboardPointer[u.toY][u.toX] = 'n'; break;
            case 2: comparativeChessboardPointer[u.toY][u.toX] = workingChessboardPointer[u.toY][u.toX] = 'b'; break;
            case 3: comparativeChessboardPointer[u.toY][u.toX] = workingChessboardPointer[u.toY][u.toX] = 'r'; break;
            case 4: comparativeChessboardPointer[u.toY][u.toX] = workingChessboardPointer[u.toY][u.toX] = 'q'; break;
            default: break;
        }

    if(movedPiece == 'k')//maby it comes to castles
    {
        if(u.fromX == 3 && u.toX == 1) // O-O of wfite
        {
            comparativeChessboardPointer[0][0] = workingChessboardPointer[0][0] = ' ';
            comparativeChessboardPointer[0][2] = workingChessboardPointer[0][2] = 'r';
        }
        if(u.fromX == 3 && u.toX == 5) // O-O-O of wfite
        {
            comparativeChessboardPointer[0][7] = workingChessboardPointer[0][7] = ' ';
            comparativeChessboardPointer[0][4] = workingChessboardPointer[0][4] = 'r';
        }
        if(u.fromX == 4 && u.toX == 2) // O-O-O of black
        {
            comparativeChessboardPointer[0][0] = workingChessboardPointer[0][0] = ' ';
            comparativeChessboardPointer[0][3] = workingChessboardPointer[0][3] = 'r';
        }
        if(u.fromX == 4 && u.toX == 6) // O-O of black
        {
            comparativeChessboardPointer[0][7] = workingChessboardPointer[0][7] = ' ';
            comparativeChessboardPointer[0][5] = workingChessboardPointer[0][5] = 'r';
        }
    }
}
    void Engine::arrangeServiceAfterUserMove (int userMoveCode)
{
    if(userMoveCode == 10000)
        return;
    setArrangements(workingChessboardPointer);
    if(isArrangementRepeatedThirdTime())
    {
        movement.gameOver = true;
        movement.gameOverStalemateByUser = true;
        delete[]workingChessboardPointer;
        workingChessboardPointer = nullptr;
    }
}
        void Engine::setArrangements(globalType::chessboardPointer ptr_X)
{
    try
    {
        if(ptr_X == nullptr)
            throw std::invalid_argument("Nullptr of the chessboard.");
    }
    catch(const std::invalid_argument &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    uint64_t controlNumber{};

    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            if(ptr_X[i][j] != ' ')
            {
                controlNumber <<= 1;
                controlNumber  += 1;
            }
            else
                controlNumber <<= 1;
        }
    controlNumbersOfArrangements.push_back(controlNumber);
    arrangements.push_back(movement.copyChessboard(ptr_X));
}
        bool Engine::isArrangementRepeatedThirdTime()
{
    try
    {
        if(arrangements.size() == 0 || controlNumbersOfArrangements.size() == 0)
            throw std::length_error("Empty vector.");
    }
    catch(const std::length_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    globalType::chessboardPointer currentArrangement = arrangements.back();
    uint64_t currentControlNumber = controlNumbersOfArrangements.back();
    int occurrenceNumber{};

    for(int i=0; i<controlNumbersOfArrangements.size(); i++)
        if(controlNumbersOfArrangements[i] == currentControlNumber)
            if(compareChessboards(arrangements[i], currentArrangement))
                occurrenceNumber++;

    if(occurrenceNumber >= 3)
        return true;
    else
        return false;
}
            bool Engine::isControlNumberRepeatedThirdTime()
{
    try
    {
        if(controlNumbersOfArrangements.size() == 0)
            throw std::length_error("Empty vector.");
    }
    catch(const std::length_error &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    uint64_t currentControlNumber = controlNumbersOfArrangements.back();
    int occurrenceNumber{};

    for(auto& element: controlNumbersOfArrangements)
        if(currentControlNumber == element)
            occurrenceNumber++;
    if(occurrenceNumber >= 3)
        return true;
    else
        return false;
}
            bool Engine::compareChessboards(globalType::chessboardPointer ptr_A, globalType::chessboardPointer ptr_B)
{
    try
    {
        if(ptr_A == nullptr || ptr_B == nullptr)
            throw std::invalid_argument("Nullptr of the chessboard.");
    }
    catch(const std::invalid_argument &e)
    {
        globalType::errorType x;
        x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
        throw x;
    }
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            if(ptr_A[i][j] == ptr_B[i][j])
                continue;
            else
                return false;
    return true;
}
    void Engine::arrangeServiceAfterEngineMove()
{
    setArrangements(workingChessboardPointer);
    if(isArrangementRepeatedThirdTime())
    {
        movement.gameOver = true;
        movement.gameOverStalemateByEngine = true;
    }
}

    int  Engine::engineMoveCoding()noexcept
{
    findEngineMove(); //  finds e.fromY e.toY e.fromX e.toX by comparing workingChessboardPointer and comparativeChessboardPointer
    int engineMoveCode = encodeEngineMove(); // changes e.fromY e.toY e.fromX e.toX into e.g. 1526
    markEngineMoveOnChessboard(); //          comparativeChessboardPointer = workingChessboardPointer
    return engineMoveCode + isItGameOver();
}
        void Engine::findEngineMove()noexcept
{
    if(workingChessboardPointer == nullptr)
        return;
    bool castle = false;
    for(int i=0,x=0; i<8; i++) //checking whether castling has taken place
    {
        if(workingChessboardPointer[7][i] != comparativeChessboardPointer[7][i])
            x++;
        if(i==7 && x==4)
        castle = true;
    }
    if(castle == false)
    {
        for(int i=0; i<8; i++)
            for(int j=0; j<8; j++)
            {
                if(workingChessboardPointer[i][j] == comparativeChessboardPointer[i][j]) //square where nothing has changed
                    continue;
                else if(workingChessboardPointer[i][j] == ' ') //square from which the engine moved
                {
                    e.fromX = j;
                    e.fromY = i;
                }
                else //square into which the engine moved
                {
                    e.toX = j;
                    e.toY = i;
                }
            }
    }
    if(castle == true)
    {
        e.fromY = e.toY = 7;
        if(color == false)
        {
            e.fromX = 4;
            if(workingChessboardPointer[7][2] == 'K')
                e.toX = 2;
            else
                e.toX = 6;
        }
        if(color == true)
        {
            e.fromX = 3;
            if(workingChessboardPointer[7][1] == 'K')
                e.toX = 1;
            else
                e.toX = 5;
        }
    }
}
        int  Engine::encodeEngineMove()noexcept
{
    if(workingChessboardPointer == nullptr)
        return 0;
    int promotionCode{};
    if(workingChessboardPointer[e.toY][e.toX] != comparativeChessboardPointer[e.fromY][e.fromX])// a pawn was promoted
        switch(workingChessboardPointer[e.toY][e.toX])
        {
            case 'N': promotionCode = 10000; break;
            case 'B': promotionCode = 20000; break;
            case 'R': promotionCode = 30000; break;
            case 'Q': promotionCode = 40000; break;
            default: break;
        }
    return e.fromX*1000+e.fromY*100+e.toX*10+e.toY*1 + promotionCode;
}
        void Engine::markEngineMoveOnChessboard()noexcept
{
    if(workingChessboardPointer == nullptr)
        return;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            comparativeChessboardPointer[i][j] = workingChessboardPointer[i][j];
}
        int  Engine::isItGameOver()noexcept
{
    if(movement.gameOverUserWin)
        return 100000;
    if(movement.gameOverStalemateByUser)
        return 200000;
    if(movement.gameOverEngineWin)
        return 300000;
    if(movement.gameOverStalemateByEngine)
        return 400000;
    return 0;
}



int Engine::moveToCode( Movement::Move move)
{
    u.toY = 7-(move.to/8);
    u.toX = 7-(move.to%8);
    u.fromY = 7-(move.to/8);
    u.fromX = 7-(move.to%8);

    int code = move.promotion;
    code *= 10;
    code += u.fromX;
    code *= 10;
    code += u.fromY;
    code *= 10;
    code += u.toX;
    code *= 10;
    code += u.toY;

    rerurn code;
}
Movement::Move Engine::codeToMove(int code)
{
 Movement::Move move;

    if(code == 10000)
        u.toY = u.toX = u.fromY = u.fromX = promotionCode = 0;
    else
    {
    u.toY = code    % 10;
    code /=10;
    u.toX = code    % 10;
    code /=10;
    u.fromY  = code % 10;
    code /=10;
    u.fromX  = code % 10;
    code /=10;
    move.promotion = code;
    }

    move.from = (7 - u.fromY) * 8 + 7 - u.fromX;
    move.to   =  (7 - u.toY) * 8 + 7 - u.toX;
    return move;
}
