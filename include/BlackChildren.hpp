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
            void getPawnCommonMoves();
                void getPawnCommonForwardMoves();
                    void getDoublePawnPush();
                void getPawnCommonCaptureMoves();
                void getEnPassantMoves();
                    void getEnPassantMove(uint8_t targetBit);
            void getPawnPromotionMoves();
                void getPawnForwardPromotionMoves();
                    void getForwardPromotionMove(gd::BitBoardIndex PromotedPiece);
                void getPawnLeftCapturePromotionMove();
                void getPawnRightCapturePromotionMove();
                    void getCapturePromotionMove(gd::BitBoardIndex PromotedPiece, gd::BitBoardIndex CapturedPiece, uint8_t targetBit);
        void getKnightMoves();
            std::bitset<8> getKnightMoveDirections();
            void getKnightMoves(std::bitset<8> directions);
                void getKnightMove(uint8_t targetBit);
        void getBishopMoves();
        void getRookMoves();
        void getQueenMoves();
                void getSlantMoves(gd::BitBoardIndex movedPiece, gd::Movements direction);
                void getHorizontalMoves(gd::BitBoardIndex movedPiece, gd::Movements direction);
                void getVerticalMoves(gd::BitBoardIndex movedPiece, gd::Movements direction);
        void getKingMoves();
            std::bitset<8> getKingMoveDirections();
            void getKingCommonMoves(std::bitset<8> directions);
                void getKingCommonMove(uint8_t targetBit);
            void getLongCastle();
            void getShortCastle();
    void getCaptureMove(gd::BitBoardIndex MovedPiece, gd::BitBoardIndex CapturedPiece, uint8_t targetBit);
    void getNonCaptureMove(gd::BitBoardIndex MovedPiece, uint8_t targetBit);
    bool isBlackKingChecked(gd::BitBoardPtr &ptr);
    gd::BitBoardPtr copyMotherBitBoard();
    ~BlackChildren();
        void deleteChildren();
};
#endif //BLACKCHILDREN_HPP
