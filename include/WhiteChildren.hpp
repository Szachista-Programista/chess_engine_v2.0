#ifndef WHITECHILDREN_HPP
#define WHITECHILDREN_HPP

#include "PositionFiller.hpp"


class WhiteChildren
{
public:////

const gd::BitBoardPtr mother;
std::vector<gd::BitBoardPtr> children;
int numberOfChildren{};
uint8_t bit{};

PositionFiller positionFiller;

    WhiteChildren(gd::BitBoardPtr &mother);
    void getMoves();
        void getPawnMoves();
            void getPawnComonMoves();
                void getPawnComonForwardMoves();
                void getPawnComonCaptureMoves();
            void getPawnPromotionMoves();
                void getPawnForwardPromotionMoves();
                    void getForwardPromotionMove(gd::BitBoardIndex PromotedPiece);
                void getPawnLeftCapturePromotionMove();
                void getPawnRightCapturePromotionMove();
                    void getCapturePromotionMove(gd::BitBoardIndex PromotedPiece, gd::BitBoardIndex CapturedPiece, uint8_t targetBit);



        //////////////
        void getKnightMoves();
        void getBischopMoves();
        void getRookMoves();
        void getQueenMoves();
        void getKingMoves();
        //////////////




    void getCaptureMove(gd::BitBoardIndex MovedPiece, gd::BitBoardIndex CapturedPiece, uint8_t targetBit);
    void getNonCaptureMove(gd::BitBoardIndex MovedPiece, uint8_t targetBit);

    bool isWhiteKingChecked(gd::BitBoardPtr &ptr);
    gd::BitBoardPtr copyMotherBitBoard();
    ~WhiteChildren();
        void deleteChildren();

};
#endif //WHITECHILDREN_HPP


