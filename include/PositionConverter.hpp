#ifndef POSITIONCONVERTER_HPP
#define POSITIONCONVERTER_HPP

#include "PositionFiller.hpp"


class PositionConverter
{
public:
        PositionFiller positionFiller;
        //********************
        std::string bitBoardToFEN(gd::BitBoardPtr &ptr);
            std::string getPieces(gd::BitBoardPtr &ptr);
                char getPieceChar(gd::BitBoardIndex index);   
                    gd::BitBoardIndex getPieceIndex(const gd::BitBoardPtr &ptr, uint8_t bit);  
            char getTurnOfColor(gd::BitBoardPtr &ptr);
            std::string getCastles(gd::BitBoardPtr &ptr);
            std::string getEnPassant(gd::BitBoardPtr &ptr);
            std::string getValueOf50MovesRule(gd::BitBoardPtr &ptr);
            std::string getNumberOfMove(gd::BitBoardPtr &ptr);
        gd::BitBoardPtr FEN_ToBitBoard(std::string FEN);
            void setPieces(gd::BitBoardPtr &ptr, std::string FEN_part);
                void setPiece(gd::BitBoardPtr &ptr, uint8_t bit, char piece);
            void setTurnOfColor(gd::BitBoardPtr &ptr, std::string FEN_part);
            void setCastles(gd::BitBoardPtr &ptr, std::string FEN_part);
            void setEnPassant(gd::BitBoardPtr &ptr, std::string FEN_part);
            void setValueOf50MovesRule(gd::BitBoardPtr &ptr, std::string FEN_part);
            void setNumberOfMove(gd::BitBoardPtr &ptr, std::string FEN_part);
        

        gd::ChessBoardPtr bitBoardTo8x8CharArray(gd::BitBoardPtr &ptr);
        std::string bitBoardToString(gd::BitBoardPtr &ptr);




};
#endif //POSITIONCONVERTER_HPP

