#include "../include/Play.hpp"

Play::Play(bool color): color{color}, position{positionConverter.initializeBitBoardPtr()}
{}
bool Play::isMoveAllowed(gd::BitBoardPtr &startPosition, gd::BitBoardPtr &targetPosition)
{
    std::vector<gd::BitBoardPtr> children;
    children = whiteChildren.generateChildren(startPosition);
    for(auto element: children)
        if(transpositionTable.computeZobristKey(element) == transpositionTable.computeZobristKey(targetPosition))
        {
            whiteChildren.deleteChildren(children);
            return true;
        }
    whiteChildren.deleteChildren(children);
    children = blackChildren.generateChildren(startPosition);
    for(auto element: children)
        if(transpositionTable.computeZobristKey(element) == transpositionTable.computeZobristKey(targetPosition))
        {
            blackChildren.deleteChildren(children);
            return true;
        }
    blackChildren.deleteChildren(children);
    return false;
}




bool Play::setUserMove()
{
    setUserMoveCoord();
    return generateNewPosition();
}
    void Play::setUserMoveCoord()
{
    std::cout<<std::endl<<"RUSZASZ SIE  : ";
    std::cin>>from>>to;
    if(from == 99 || from == 77)
        return;
    if(!color)
    {
        from = 63 - from;
        to   = 63 - to;
    }
}
    bool Play::generateNewPosition()
{
    gd::BitBoardPtr newPosition = gd::copyBitBoard(position);
    if(from == 99)
    {
        if(color)
        {
            newPosition[gd::whiteKing][3] = 0;
            newPosition[gd::whiteKing][1] = 1;
            newPosition[gd::whiteRook][0] = 0;
            newPosition[gd::whiteRook][2] = 1;
        }
        else
        {
            newPosition[gd::blackKing][59] = 0;
            newPosition[gd::blackKing][61] = 1;
            newPosition[gd::blackRook][63] = 0;
            newPosition[gd::blackRook][60] = 1;
        }
    }
    else if(from == 77)
    {
        if(color)
        {
            newPosition[gd::whiteKing][3] = 0;
            newPosition[gd::whiteKing][5] = 1;
            newPosition[gd::whiteRook][7] = 0;
            newPosition[gd::whiteRook][4] = 1;
        }
        else
        {
            newPosition[gd::blackKing][59] = 0;
            newPosition[gd::blackKing][57] = 1;
            newPosition[gd::blackRook][56] = 0;
            newPosition[gd::blackRook][58] = 1;
        }
    }
    else
    {
        if(color && position[gd::whitePiece][from] == false || !color && position[gd::blackPiece][from] == false)
            return false;
        if(color)
        {
            for(auto element: {gd::whitePawn, gd::whiteKnight, gd::whiteBishop, gd::whiteRook, gd::whiteQueen, gd::whiteKing})
                if(newPosition[element][from] == true)
                {
                    newPosition[element][from] = 0;
                    newPosition[element][to]   = 1;
                    break;
                }
            for(auto element: {gd::blackPawn, gd::blackKnight, gd::blackBishop, gd::blackRook, gd::blackQueen, gd::blackKing})
                if(newPosition[element][to] == true)
                {
                    newPosition[element][to] = 0;
                    break;
                }
        }
        else
        {
            for(auto element: {gd::blackPawn, gd::blackKnight, gd::blackBishop, gd::blackRook, gd::blackQueen, gd::blackKing})
                if(newPosition[element][from] == true)
                {
                    newPosition[element][from] = 0;
                    newPosition[element][to]   = 1;
                    break;
                }
            for(auto element: {gd::whitePawn, gd::whiteKnight, gd::whiteBishop, gd::whiteRook, gd::whiteQueen, gd::whiteKing})
                if(newPosition[element][to] == true)
                {
                    newPosition[element][to] = 0;
                    break;
                }
        }
    }
    positionFiller.fillBitBoard(newPosition);
    if(isMoveAllowed(position, newPosition))
    {
        delete[]position;
        position = newPosition;
        return true;
    }
    else
    {
        delete[]newPosition;
        return false;
    }

}

void Play::run()
{    
    system("pause");
    positionWriter.writeChessboard(positionConverter.convertBitBoardToString(position), color);
    if(!color)
    {
        position = searchTree.iterativeDeepening(position, !color);
        positionWriter.writeChessboard(positionConverter.convertBitBoardToString(position), color);
    }
    while(true)
    {
        while(! setUserMove()){};
        positionWriter.writeChessboard(positionConverter.convertBitBoardToString(position), color);
        position = searchTree.iterativeDeepening(position, !color);
        positionWriter.writeChessboard(positionConverter.convertBitBoardToString(position), color);
    }


}




