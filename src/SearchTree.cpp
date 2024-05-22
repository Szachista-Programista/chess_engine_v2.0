#include "../include/SearchTree.hpp"

gd::BitBoardPtr SearchTree::findBestMove(const gd::BitBoardPtr position, const uint8_t depth, const bool color)
{
    std::vector<gd::BitBoardPtr> children;
    std::vector<float> childEval;
    gd::BitBoardPtr choosenChild;
    float alpha = -1000.0f;
    float beta  = 1000.0f;
    float eval;
    if(color)
    {
        children = whiteChildren.generateChildren(position);std::cout<<children.size();
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
gd::BitBoardPtr SearchTree::iterativeDeepening(const gd::BitBoardPtr position, const  uint8_t maxDepth, const bool color)
{
    std::vector<gd::EvaluedPosition> evaluedPositions = generatePositions(position, color);
    for (int depth=1; depth<=maxDepth; depth++)
    {
        float alpha = -1000.0f;
        float beta  = 1000.0f;
        for(int i=0; i<evaluedPositions.size(); i++)
        {
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
    }
    return evaluedPositions.front().position;
}
    std::vector<gd::EvaluedPosition> SearchTree::generatePositions(const gd::BitBoardPtr position, const bool color)
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



