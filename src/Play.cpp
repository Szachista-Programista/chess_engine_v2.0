#include "../include/Play.hpp"

Play::Play(bool color): color{color}, position{positionConverter.FEN_ToBitBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")}
{
    positionFiller.fillBitBoard(position);
}
bool Play::setUserMove()
{
    setUserMoveCoord();
    return movement.makeMove(position, move);
}
    void Play::setUserMoveCoord()
{
    std::cout<<std::endl<<"RUSZASZ SIE  : ";

    int from, to, promotion;
    std::cin>>from>>to>>promotion;

    move.from = from;
    move.to = to;
    move.promotion = promotion;
    if(!color)
    {
        move.from = 63 - move.from;
        move.to   = 63 - move.to;
    }
}

void Play::run()
{
    system("pause");
    positionWriter.writeChessboard(positionConverter.bitBoardToString(position), color); yyy();
    if(!color)
    {
        position = searchTree.iterativeDeepening(position, !color);
        positionWriter.writeChessboard(positionConverter.bitBoardToString(position), color); yyy();
    }
    while(true)
    {
        while(! setUserMove()){};
        positionWriter.writeChessboard(positionConverter.bitBoardToString(position), color); yyy();
        position = searchTree.iterativeDeepening(position, !color);
        positionWriter.writeChessboard(positionConverter.bitBoardToString(position), color); yyy();
    }
}




void Play::yyy()
{
    std::ofstream file("txt/abc.txt", std::ios::app);
    file<<positionConverter.bitBoardToFEN(position);
    file<<std::endl;
    file.close();
}