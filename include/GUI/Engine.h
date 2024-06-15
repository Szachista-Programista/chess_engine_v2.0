#ifndef ENGINE_H
#define ENGINE_H
#include <cmath>
#include "GlobalDefinitionsPrevious.h"
#include "../PlayService.hpp"

class Engine{
    bool color;

    int promotionCode;
    int movementNumber = 0;

    PlayService playService;
    PositionConverter positionConverter;
    PositionFiller positionFiller;
    PositionWriter positionWriter;
    SearchTree searchTree;
    Movement movement;
    Movement::Move move;
    std::vector<globalType::chessboardPointer>arrangements;
    std::vector<uint64_t>controlNumbersOfArrangements;

    std::string userPiecesMovedInOpening;

    globalType::chessboardPointer comparativeChessboardPointer;
    globalType::chessboardPointer workingChessboardPointer;

//********************************************************************************
public: Engine(bool k);
private:    globalType::chessboardPointer loadPiecesArrangement();
public:~Engine()noexcept;
private:    void clearArrangements()noexcept;
public: bool canUserMakeSuchMove(int userMoveCode);

public: int makeMove(int userMoveCode);
            void decipherUserMove(int userMoveCode);
private:    void getEngineReadyForMove(int userMoveCode);
                void markUserMoveOnChessboard(int userMoveCode);
            void arrangeServiceAfterUserMove(int userMoveCode);
                void setArrangements(globalType::chessboardPointer ptr_X);
                bool isArrangementRepeatedThirdTime();
                    bool isControlNumberRepeatedThirdTime();
                    bool compareChessboards(globalType::chessboardPointer ptr_A, globalType::chessboardPointer ptr_B);
            void arrangeServiceAfterEngineMove();

            int engineMoveCoding()noexcept;
                void findEngineMove()noexcept;
                int  encodeEngineMove()noexcept;
                void markEngineMoveOnChessboard()noexcept;
                int  isItGameOver()noexcept;

gd::ChessBoardPtr flipBoard(gd::ChessBoardPtr ptr);

Movement::Move codeToMove(int code);
globalType::chessboardPointer copyChessboard(const globalType::chessboardPointer oryginal);

//********************************************************************************************
    struct Movement{
        int fromX,
            fromY,
            toX,
            toY;
    }u,e;//user/engine
};
#endif//ENGINE_H
