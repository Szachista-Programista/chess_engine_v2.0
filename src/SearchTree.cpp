#include "../include/SearchTree.hpp"

gd::BitBoardPtr SearchTree::findByAlphaBeta(const gd::BitBoardPtr position, const bool color)
{
    gd::BitBoardPtr choosenChild;
    for(uint8_t depth=0;; depth++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<gd::BitBoardPtr> children;
        std::vector<int> childEval;
        int alpha = -gd::INF;
        int beta  = gd::INF;
        int eval;
        if(color)
        {
            children = whiteChildren.generateChildren(position);
            for(int i=0; i<children.size(); i++)
            {
                eval = alphaBeta(children[i], depth, alpha, beta, black);
                alpha = std::max(alpha, eval);
                childEval.push_back(eval);
            }
            auto it = std::find(childEval.begin(), childEval.end(), alpha);
            choosenChild = gd::copyBitBoard(children[distance(childEval.begin(), it)]);
            whiteChildren.deleteChildren(children);
        }
        else
        {
            children = blackChildren.generateChildren(position);
            for(int i=0; i<children.size(); i++)
            {
                eval = alphaBeta(children[i], depth, alpha, beta, white);
                beta = std::min(beta, eval);
                childEval.push_back(eval);
            }
            auto it = std::find(childEval.begin(), childEval.end(), beta);
            choosenChild = gd::copyBitBoard(children[distance(childEval.begin(), it)]);
            blackChildren.deleteChildren(children);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout<<">>>AB "<<std::setw(4)<<duration.count()<<"ms - depth="<<(int)depth<<" <<<"<<std::endl;
        if(duration.count() > 1500)
            break;
        else
            delete[]choosenChild;
    }
    return choosenChild;
}
gd::BitBoardPtr SearchTree::iterativeDeepening(const gd::BitBoardPtr position, const bool color)
{
    std::vector<gd::EvaluedPosition> evaluedPositions = getPositions(position, color);
    gd::BitBoardPtr choosenChild;
    for(uint8_t depth=0;; depth++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        int alpha = -gd::INF;
        int beta  =  gd::INF;
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
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout<<">>>ID "<<std::setw(4)<<duration.count()<<"ms - depth="<<(int)depth<<" <<<"<<std::endl;
        if(duration.count() > 1500)
            break;
    }
    choosenChild = gd::copyBitBoard(evaluedPositions.front().position);
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
        evaluedPosition.push_back({position, 0});
    return evaluedPosition;
}
    void SearchTree::deletePositions(std::vector<gd::EvaluedPosition> positions)
{
    for(uint8_t i=0; i<positions.size(); i++)
        delete[]positions[i].position;
}
int SearchTree::alphaBeta(const gd::BitBoardPtr position, const uint8_t depth, int alpha, int beta, const bool color)
{
    if(depth == 0)
        return positionEvaluator.evaluatePosition(position);
    std::vector<gd::BitBoardPtr> children;
    int eval;
    if(color)
    {
        int maxEval = -gd::INF;
        children = whiteChildren.generateChildren(position);
        if(children.size() == 0)
        {
            if((position[gd::whiteKing] & position[gd::blackCapturedSquare]).any())
                return -gd::INF - depth;
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
        int minEval = gd::INF;
        children = blackChildren.generateChildren(position);
        if(children.size() == 0)
        {
            if((position[gd::blackKing] & position[gd::whiteCapturedSquare]).any())
                return gd::INF + depth;
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



