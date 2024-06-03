#include "include/SearchTree.hpp"
#include "include/PositionWriter.hpp"
#include "include/Play.hpp"
#include "include/TranspositionTable.hpp"
#include "include/Polyglot.hpp"

std::vector<std::string> readOpenings()
{
    std::vector<std::string> lines;
    std::string line;
    std::ifstream file("txt/openings.txt");
    if(file.is_open())
    {
        while (std::getline(file, line))
            lines.push_back(line);
        file.close();
    }
    else
        std::cerr << "Unable to open file: " << "txt/openings.txt" << std::endl;
    
    return lines;
}



int main()
{
    PositionConverter positionConverter;
    PositionWriter positionWriter;
    PositionEvaluator positionEvaluator;
    SearchTree searchTree;
    TranspositionTable transpositionTable;
    WhiteChildren wc;
    BlackChildren bc;
    Polyglot polyglot;
    Play play(0);//play.run();

    gd::BitBoardPtr x = positionConverter.convert_FEN_NotationToBitBoard
    ("p1pppppp/RNBQKBNR/RNBQKBNR/RNBQKBNR/RNBQKBNR/RNBQKBNR/RNBQKBNR/1P1PPPP1 b KQkq - 0 1");
    //searchTree.iterativeDeepening(x, 1);

    x[gd::extraInfo][ 0]=1;
    x[gd::extraInfo][ 7]=1;
    x[gd::extraInfo][56]=1;
    x[gd::extraInfo][63]=1;


    positionWriter.writeChessboard(x);
    positionWriter.writeBitBoard(x);
    std::cout<<std::hex<<polyglot.generateKey(x);
//rnbqkbnr/p1pppppp/8/8/P6P/R1p5/1P1PPPP1/1NBQKBNR b Kkq - 0 4



    
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
