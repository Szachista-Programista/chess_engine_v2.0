#ifndef POSITIONCONVERTER_HPP
#define POSITIONCONVERTER_HPP

#include "PositionFiller.hpp"


class PositionConverter
{
public:
        PositionFiller positionFiller;
        //********************

        gd::ChessBoardPtr convertBitBoardTo8x8CharArray(gd::BitBoardPtr &ptr);
        gd::BitBoardPtr convertStringToBitBoard(std::string content);
        std::string convertBitBoardTo_FEN_Notation(gd::BitBoardPtr &ptr);
            std::string getPieces(gd::BitBoardPtr &ptr);
                char getPieceChar(gd::BitBoardIndex index);     
            char getTurnOfColor(gd::BitBoardPtr &ptr);
            std::string getCastles(gd::BitBoardPtr &ptr);
            std::string getEnPassant(gd::BitBoardPtr &ptr);
            std::string getValueOf50MovesRule(gd::BitBoardPtr &ptr);
            std::string getNumberOfMove(gd::BitBoardPtr &ptr);
                gd::BitBoardIndex getPieceIndex(gd::BitBoardPtr &ptr, uint8_t bit);
        gd::BitBoardPtr convert_FEN_NotationToBitBoard(std::string FEN);
            void setPieces(gd::BitBoardPtr &ptr, std::string FEN_part);
                void setPiece(gd::BitBoardPtr &ptr, uint8_t bit, char piece);
            void setTurnOfColor(gd::BitBoardPtr &ptr, std::string FEN_part);
            void setCastles(gd::BitBoardPtr &ptr, std::string FEN_part);
            void setEnPassant(gd::BitBoardPtr &ptr, std::string FEN_part);
            void setValueOf50MovesRule(gd::BitBoardPtr &ptr, std::string FEN_part);
            void setNumberOfMove(gd::BitBoardPtr &ptr, std::string FEN_part);
        std::string convertChessBoardFileContentToString();
        

        std::string convertBitBoardToString(gd::BitBoardPtr &ptr);


        gd::BitBoardPtr initializeBitBoardPtr();
            gd::BitBoardPtr loadBitBoard();
                




};
#endif //POSITIONCONVERTER_HPP

