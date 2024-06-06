#include "../include/SearchTree.hpp"

SearchTree::SearchTree(): polyglot{"bin/book.bin"}
{}
gd::BitBoardPtr SearchTree::iterativeDeepening(const gd::BitBoardPtr position, const bool color)
{

    std::vector<gd::EvaluedPosition> evaluedPositions = getPositions(position, color);
    gd::BitBoardPtr choosenChild;

    //choosenChild = gd::copyBitBoard(position);
    //if(polyglot.checkPolyglotBook(choosenChild))
    //    return choosenChild;
    //else 
    //    delete[]choosenChild;


    for(int depth=0;; depth++)
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
        positionSorter.sortEvaluatedPositions(evaluedPositions, color);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);  yyy(evaluedPositions, depth, duration);
        if(duration.count() > 1500)
            break;
            
    }                                                                                         xxx();
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
    for(int i=0; i<children.size(); i++)
        evaluedPosition.push_back({children[i], 0, i});
    return evaluedPosition;
}
    void SearchTree::deletePositions(std::vector<gd::EvaluedPosition> evaluedPosition)
{
    for(uint8_t i=0; i<evaluedPosition.size(); i++)
        delete[]evaluedPosition[i].position;
}
int SearchTree::alphaBeta(const gd::BitBoardPtr position, const uint8_t depth, int alpha, int beta, const bool color)
{
    int eval;
    const uint64_t zobristKey = transpositionTable.computeZobristKey(position);
    if (transpositionTable.probeTTEntry(zobristKey, depth, eval))
        return eval;
    if(depth == 0)
        return positionEvaluator.evaluatePosition(position);
    std::vector<gd::BitBoardPtr> children;
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
        transpositionTable.storeTTEntry(zobristKey, depth, maxEval);
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
        transpositionTable.storeTTEntry(zobristKey, depth, minEval);
        return minEval;
    }
}


void SearchTree::yyy(const std::vector<gd::EvaluedPosition> &positions, int depth, std::chrono::milliseconds duration)
{
    std::ofstream file("txt/abc.txt", std::ios::app);

    //if (!file.is_open()) {
        //std::cerr << "Nie udało się otworzyć pliku do zapisu: " << filename << std::endl;
        //return;
    //}
    file<<"d="<<depth<<" t="<<std::setw(4)<<duration.count()<<" # ";
    for (int i=0; i<positions.size(); i++)
    {
        file<<std::setw(5)<<positions[i].moveNumber;
        if (i < positions.size() - 1)
            file << ", ";
    }
    file<<std::endl;
    file<<"d="<<depth<<" t="<<std::setw(4)<<duration.count()<<" # ";
    for (int i=0; i<positions.size(); i++)
    {
        file<<std::setw(5)<<positions[i].eval;
        if (i < positions.size() - 1)
            file << ", ";
    }
    file<<std::endl;
    file.close();
}
void SearchTree::xxx()
{
    std::ofstream file("txt/abc.txt", std::ios::app);
    file<<std::string(200, '#')<<std::endl;
    file.close();
}
