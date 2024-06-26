#ifndef WHITECHILDREN_HPP
#define WHITECHILDREN_HPP

#include "PositionFiller.hpp"

class WhiteChildren
{
        gd::BitBoardPtr mother;
        std::vector<gd::BitBoardPtr> children;
        uint8_t bit;
        PositionFiller positionFiller;
        //********************
public: std::vector<gd::BitBoardPtr> generateChildren(gd::BitBoardPtr position);
private:    void getMoves();
                void getPawnMoves();
                    void getPawnCommonMoves();
                        void getPawnCommonForwardMoves();
                            void getDoublePawnPush();
                        void getPawnCommonCaptureMoves();
                        void getEnPassantMoves();
                            void getEnPassantMove(const uint8_t targetBit);
                    void getPawnPromotionMoves();
                        void getPawnForwardPromotionMoves();
                            void getForwardPromotionMove(const gd::BitBoardIndex PromotedPiece);
                        void getPawnLeftCapturePromotionMove();
                        void getPawnRightCapturePromotionMove();
                            void getCapturePromotionMove(const gd::BitBoardIndex PromotedPiece, const gd::BitBoardIndex CapturedPiece, const uint8_t targetBit);
                void getKnightMoves();
                    std::bitset<8> getKnightMoveDirections();
                    void getKnightMoves(const std::bitset<8> directions);
                        void getKnightMove(const uint8_t targetBit);
                void getBishopMoves();
                void getRookMoves();
                void getQueenMoves();
                        void getSlantMoves(const gd::BitBoardIndex movedPiece, const gd::Movements direction);
                        void getHorizontalMoves(const gd::BitBoardIndex movedPiece, const gd::Movements direction);
                        void getVerticalMoves(const gd::BitBoardIndex movedPiece, const gd::Movements direction);
                void getKingMoves();
                    std::bitset<8> getKingMoveDirections();
                    void getKingCommonMoves(const std::bitset<8> directions);
                        void getKingCommonMove(const uint8_t targetBit);
                            void getKingCaptureMove(const gd::BitBoardIndex capturedPiece, const uint8_t targetBit);
                            void getKingNonCaptureMove(const uint8_t targetBit);
                    void getLongCastle();
                    void getShortCastle();
            void getCaptureMove(const gd::BitBoardIndex MovedPiece, const gd::BitBoardIndex CapturedPiece, const uint8_t targetBit);
            void getNonCaptureMove(const gd::BitBoardIndex MovedPiece, const uint8_t targetBit);
            void validateMove(gd::BitBoardPtr &ptr);
                bool isWhiteKingChecked(gd::BitBoardPtr &ptr);
            gd::BitBoardPtr copyMotherBitBoard();
public: void deleteChildren(std::vector<gd::BitBoardPtr> &children);
};
#endif //WHITECHILDREN_HPP
