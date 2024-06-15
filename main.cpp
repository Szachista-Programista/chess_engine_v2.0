#include "include/PlayService.hpp"
#include "include/GUI/Game.h"
TranspositionTable transpositionTable;
PositionConverter positionConverter;
PositionEvaluator positionEvaluator;
PositionWriter positionWriter;
WhiteChildren whiteChildren;
BlackChildren blackChildren;
SearchTree searchTree;
Movement movement;
Polyglot polyglot("bin/codekiddy.bin");
////////////////////////////////////////////////////////////////
void countNumberOfMoves(std::string FEN)
{
    gd::BitBoardPtr x = positionConverter.FEN_ToBitBoard(FEN);
    std::vector<gd::BitBoardPtr> B = blackChildren.generateChildren(x);
    std::vector<gd::BitBoardPtr> W = whiteChildren.generateChildren(x);
    std::cout<<" - bialy rochow: "<<W.size()<<" czarny rochow: "<<B.size()<<std::endl;
}
void testujDzieciaczki()
{
std::cout<<std::left<<std::setw(5)<<"40/36";
countNumberOfMoves("r1bq1b1r/pppk1pp1/8/np3p1p/1Q1nB1P1/N4N2/PPPPPP1P/R1B1K1R1 w Q - 0 1");
std::cout<<std::left<<std::setw(5)<<"3/2";
countNumberOfMoves("rnbk1n2/1pP1p1pp/7r/R3q3/3Q4/5N2/pP1p1PPP/1NB1K2R w K - 0 1");//szach
std::cout<<std::left<<std::setw(5)<<"8/8";
countNumberOfMoves("2bk1bn1/ppp1pppp/2n1q2R/r7/7R/r2Q1N2/PPPP1PPP/1NB1KB2 w - - 0 1");//szach
std::cout<<std::left<<std::setw(5)<<"45/46";
countNumberOfMoves("r3k1q1/1pppp2P/1nb5/8/8/5BN1/p2PPPP1/1Q2K2R w Kq - 0 1");//promocje/roszady
}
void GUI()
{
    do
    {
        globalType::windowResized = false;
        Game game;
        try
        {
            game.run();
        }
        catch(globalType::errorType &e)
        {
            std::cout<<e.errorMessage;
        }
    }
    while(globalType::windowResized);
}
////////////////////////////////////////////////////////////////

int main()
{

    GUI();

    //PlayService playService(color);
    //playService.run();
    //testujDzieciaczki();

    return 0;
}
////////////////////////////////////////////////////////////////
/*
#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <mutex>
#include <chrono>
#include <algorithm>

constexpr int DEPTH = 5;
constexpr int NUM_MOVES = 10;

std::mutex mtx;

// Funkcja symulująca przeszukiwanie dla danego ruchu
int search(int move, int depth, int alpha, int beta) {
    if (depth == 0) {
        return move * depth; // Symulacja wyniku
    }

    int bestScore = -9999;
    for (int i = 0; i < NUM_MOVES; ++i) {
        int score = -search(i, depth - 1, -beta, -alpha);
        bestScore = std::max(bestScore, score);
        alpha = std::max(alpha, score);
        if (alpha >= beta) {
            break; // Beta cutoff
        }
    }
    return bestScore;
}

// Funkcja przetwarzająca ruch w osobnym wątku
void processMove(int move, int alpha, int beta, std::promise<int> result) {
    int score = search(move, DEPTH, alpha, beta);
    result.set_value(score);
}

// Główna funkcja przeszukiwania równoległego
void parallelSearch(int depth, int alpha, int beta) {
    std::vector<std::thread> threads;
    std::vector<std::future<int>> futures;
    int bestScore = -9999;

    for (int move = 0; move < NUM_MOVES; ++move) {
        std::promise<int> promise;
        futures.push_back(promise.get_future());
        threads.emplace_back(processMove, move, alpha, beta, std::move(promise));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    for (auto& future : futures) {
        int score = future.get();
        std::lock_guard<std::mutex> lock(mtx);
        bestScore = std::max(bestScore, score);
        alpha = std::max(alpha, score);
        if (alpha >= beta) {
            break; // Beta cutoff
        }
    }

    std::cout << "Best score: " << bestScore << std::endl;
}

int main() {
    auto start = std::chrono::steady_clock::now();
    parallelSearch(DEPTH, -9999, 9999);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s\n";

    return 0;
}
*/
