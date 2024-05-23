#include "../include/SearchTree.hpp"


gd::BitBoardPtr SearchTree::iterativeDeepening(const gd::BitBoardPtr position, const  uint8_t maxDepth, const bool color)
{
    std::vector<gd::EvaluedPosition> evaluedPositions = getPositions(position, color);
    gd::BitBoardPtr choosenChild;
    for (uint8_t depth=1; depth<maxDepth; depth++)
    {
        float alpha = -1000.0f;
        float beta  = 1000.0f;
        for(int i=0; i<evaluedPositions.size(); i++)
        {std::cout<<(int)depth;
            evaluedPositions[i].eval = alphaBeta(evaluedPositions[i].position, depth, alpha, beta, !color);
            if(color)
                alpha = std::max(alpha, evaluedPositions[i].eval);
            else
                beta = std::min(beta, evaluedPositions[i].eval);

        }




        if(color)
            positionSorter.sortEvaluatedPositionsDescending(evaluedPositions);
        else
            positionSorter.sortEvaluatedPositionsAscending(evaluedPositions);



        for(int i=0; i<evaluedPositions.size(); i++)
        {
            //std::cout<<std::setw(5)<<evaluedPositions[i].eval;
        }
        //std::cout<<std::endl<<std::endl;







    }
    choosenChild = copyBitBoard(evaluedPositions.front().position);
    deletePositions(evaluedPositions);
    return choosenChild;
}
    std::vector<gd::EvaluedPosition> SearchTree::getPositions(const gd::BitBoardPtr position, const bool color)
{
    std::vector<gd::BitBoardPtr> children;
    if(color)
        children = whiteChildren.generateChildren(position);
    else
        children = blackChildren.generateChildren(position);
    std::vector<gd::EvaluedPosition> evaluedPosition;
    for (auto &position: children)
        evaluedPosition.push_back({position, 0.0f});
    return evaluedPosition;
}
    void SearchTree::deletePositions(std::vector<gd::EvaluedPosition> positions)
{
    for(uint8_t i=0; i<positions.size(); i++)
        delete[]positions[i].position;
}
float SearchTree::alphaBeta(const gd::BitBoardPtr position, const uint8_t depth, float alpha, float beta, const bool color)
{
    if(depth == 0)
        return positionEvaluator.evaluatePosition(position);
    std::vector<gd::BitBoardPtr> children;
    float eval;
    if(color)
    {
        float maxEval = -1000.0;
        children = whiteChildren.generateChildren(position);
        if(children.size() == 0)
        {
            if((position[gd::whiteKing] & position[gd::blackCapturedSquare]).any())
                return -1000.0f - static_cast<float>(depth);
            else
                return 0.0f;
        }
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
        children = blackChildren.generateChildren(position);
        if(children.size() == 0)
        {
            if((position[gd::blackKing] & position[gd::whiteCapturedSquare]).any())
                return 1000.0f + static_cast<float>(depth);
            else
                return 0.0f;
        }
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
gd::BitBoardPtr SearchTree::copyBitBoard(const gd::BitBoardPtr orginal)const
    {
        gd::BitBoardPtr copy  = new std::bitset<64>[gd::bitBoardSize]{};
        for(uint8_t i=0; i<gd::bitBoardSize; i++)
            copy[i] = orginal[i];
        return copy;
    }





gd::BitBoardPtr SearchTree::findByAlphaBeta(const gd::BitBoardPtr position, const uint8_t depth, const bool color)
{
    std::vector<gd::BitBoardPtr> children;
    std::vector<float> childEval;
    gd::BitBoardPtr choosenChild;
    float alpha = -1000.0f;
    float beta  = 1000.0f;
    float eval;
    if(color)
    {
        children = whiteChildren.generateChildren(position);
        for(int i=0; i<children.size(); i++)
        {std::cout<<(int)depth-1;
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
        children = blackChildren.generateChildren(position);
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
    return choosenChild;
}
float SearchTree::alphaBetaX(const gd::BitBoardPtr position, const uint8_t depth, float alpha, float beta, const bool color)
{
    if(depth == 0)
        return positionEvaluator.evaluatePosition(position);
    std::vector<gd::BitBoardPtr> children;
    float eval;
    if(color)
    {
        float maxEval = -1000.0;
        children = whiteChildren.generateChildren(position);
        if(children.size() == 0)
        {
            if((position[gd::whiteKing] & position[gd::blackCapturedSquare]).any())
                return -1000.0f + static_cast<float>(depth);
            else
                return 0.0f;
        }

        for(int i=0; i<children.size(); i++)
        {
            eval = alphaBetaX(children[i], depth-1, alpha, beta, black);
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
        children = blackChildren.generateChildren(position);
        if(children.size() == 0)
        {
            if((position[gd::blackKing] & position[gd::whiteCapturedSquare]).any())
                return 1000.0f - static_cast<float>(depth);
            else
                return 0.0f;
        }

        for(int i=0; i<children.size(); i++)
        {
            eval = alphaBetaX(children[i], depth-1, alpha, beta, white);
            minEval = std::min(minEval, eval);
            beta = std::min(beta, eval);
            if(alpha >= beta)
                break;
        }
        blackChildren.deleteChildren(children);
        return minEval;
    }
}
gd::BitBoardPtr SearchTree::findByMinimax(const gd::BitBoardPtr position, const uint8_t depth, const bool color)
{
    std::vector<gd::BitBoardPtr> children;
    std::vector<float> childEval;
    gd::BitBoardPtr choosenChild;
    float alpha = -1000.0f;
    float beta  = 1000.0f;
    float eval;
    if(color)
    {
        children = whiteChildren.generateChildren(position);
        for(int i=0; i<children.size(); i++)
        {
            eval = minimax(children[i], depth-1, black);
            alpha = std::max(alpha, eval);
            childEval.push_back(eval);
        }
        auto it = std::find(childEval.begin(), childEval.end(), alpha);
        choosenChild = copyBitBoard(children[distance(childEval.begin(), it)]);
        whiteChildren.deleteChildren(children);
    }
    else
    {
        children = blackChildren.generateChildren(position);
        for(int i=0; i<children.size(); i++)
        {
            eval = minimax(children[i], depth-1, white);
            beta = std::min(beta, eval);
            childEval.push_back(eval);
        }
        auto it = std::find(childEval.begin(), childEval.end(), beta);
        choosenChild = copyBitBoard(children[distance(childEval.begin(), it)]);
        blackChildren.deleteChildren(children);
    }
    return choosenChild;
}
    float SearchTree::minimax(const gd::BitBoardPtr position, const uint8_t depth, const bool color)
{
    if(depth == 0)
        return positionEvaluator.evaluatePosition(position);
    std::vector<gd::BitBoardPtr> children;
    float eval;
    if(color)
    {
        float maxEval = -1000.0;
        children = whiteChildren.generateChildren(position);
        for(int i=0; i<children.size(); i++)
        {
            eval = minimax(children[i], depth-1, black);
            maxEval = std::max(maxEval, eval);
        }
        whiteChildren.deleteChildren(children);
        return maxEval;
    }
    else
    {
        float minEval = 1000.0;
        children = blackChildren.generateChildren(position);
        for(int i=0; i<children.size(); i++)
        {
            eval = minimax(children[i], depth-1, white);
            minEval = std::min(minEval, eval);
        }
        blackChildren.deleteChildren(children);
        return minEval;
    }
}