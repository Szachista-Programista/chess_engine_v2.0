#ifndef BLACKCHILDREN_HPP
#define BLACKCHILDREN_HPP

#include "PositionFiller.hpp"


class BlackChildren
{
public:////

const gd::BitBoardPtr mother;
std::vector<gd::BitBoardPtr> children;
int numberOfChildren{};
uint8_t bit{};

PositionFiller positionFiller;

    BlackChildren(gd::BitBoardPtr &mother);
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

    bool isBlackKingChecked(gd::BitBoardPtr &ptr);
    gd::BitBoardPtr copyMotherBitBoard();
    ~BlackChildren();
        void deleteChildren();

};
#endif //BLACKCHILDREN_HPP



