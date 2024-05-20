#include "../include/SearchTree.hpp"

gd::BitBoardPtr SearchTree::findBestMove(const gd::BitBoardPtr position, const uint8_t depth, const bool color)
{
    std::vector<gd::BitBoardPtr> children;
    std::vector<float> childEval;
    gd::BitBoardPtr choosenChild;
    float alpha = -1000.0f;
    float beta  = 1000.0f;
    float eval;
    if(color == white)
    {
        children = whiteChildren.getMoves(position);
        for(int i=0; i<children.size(); i++)
        {
            eval = alphaBeta(children[i], depth-1, alpha, beta, black);
            alpha = std::max(alpha, eval);
            childEval.push_back(eval);
        }
        auto it = std::find(childEval.begin(), childEval.end(), alpha);
        choosenChild = copyBitBoard(children[distance(childEval.begin(), it)]);
        whiteChildren.deleteChildren(children);
    }
    else
    {
        children = blackChildren.getMoves(position);
        for(int i=0; i<children.size(); i++)
        {
            eval = alphaBeta(children[i], depth-1, alpha, beta, white);
            beta = std::min(beta, eval);
            childEval.push_back(eval);
        }
        auto it = std::find(childEval.begin(), childEval.end(), beta);
        choosenChild = copyBitBoard(children[distance(childEval.begin(), it)]);
        blackChildren.deleteChildren(children);
    }
    PositionFiller(1,1).fillBitBoard(choosenChild);
    return choosenChild;
}
float SearchTree::alphaBeta(const gd::BitBoardPtr position, const uint8_t depth, float alpha, float beta, const bool color)
{
    if(depth == 0)
        return evaluatePosition(position);
    std::vector<gd::BitBoardPtr> children;
    float eval;
    if(color == white)
    {
        float maxEval = -1000.0;
        children = whiteChildren.getMoves(position);
        for(int i=0; i<children.size(); i++)
        {
            eval = alphaBeta(children[i], depth-1, alpha, beta, black);
            maxEval = std::max(maxEval, eval);
            alpha = std::max(alpha, eval);
            if(alpha >= beta)
                break;
        }
        whiteChildren.deleteChildren(children);
        return maxEval;
    }
    else
    {
        float minEval = 1000.0;
        children = blackChildren.getMoves(position);
        for(int i=0; i<children.size(); i++)
        {
            eval = alphaBeta(children[i], depth-1, alpha, beta, white);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if(alpha >= beta)
                break;
        }
        blackChildren.deleteChildren(children);
        return minEval;
    }
}
float SearchTree::evaluatePosition(const gd::BitBoardPtr &ptr)//const
{
    //licznik++;
    return
     ptr[gd::whitePawn].count() + 3*ptr[gd::whiteKnight].count() + 3*ptr[gd::whiteBishop].count() + 5*ptr[gd::whiteRook].count() + 9*ptr[gd::whiteQueen].count()
    -ptr[gd::blackPawn].count() - 3*ptr[gd::blackKnight].count() - 3*ptr[gd::blackBishop].count() - 5*ptr[gd::blackRook].count() - 9*ptr[gd::blackQueen].count();
}
gd::BitBoardPtr SearchTree::copyBitBoard(const gd::BitBoardPtr orginal)const
    {
        gd::BitBoardPtr copy  = new std::bitset<64>[gd::bitBoardSize]{};
        copy[gd::whitePawn]   = orginal[gd::whitePawn];
        copy[gd::whiteKnight] = orginal[gd::whiteKnight];
        copy[gd::whiteBishop] = orginal[gd::whiteBishop];
        copy[gd::whiteRook]   = orginal[gd::whiteRook];
        copy[gd::whiteQueen]  = orginal[gd::whiteQueen];
        copy[gd::whiteKing]   = orginal[gd::whiteKing];
        copy[gd::blackPawn]   = orginal[gd::blackPawn];
        copy[gd::blackKnight] = orginal[gd::blackKnight];
        copy[gd::blackBishop] = orginal[gd::blackBishop];
        copy[gd::blackRook]   = orginal[gd::blackRook];
        copy[gd::blackQueen]  = orginal[gd::blackQueen];
        copy[gd::blackKing]   = orginal[gd::blackKing];
        copy[gd::extraInfo]   = orginal[gd::extraInfo];
        return copy;
    }



