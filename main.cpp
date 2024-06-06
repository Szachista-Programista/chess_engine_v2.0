#include "include/Play.hpp"
    TranspositionTable transpositionTable;
    PositionConverter positionConverter;
    PositionEvaluator positionEvaluator;
    PositionWriter positionWriter;
    WhiteChildren whiteChildren;
    BlackChildren blackChildren;
    SearchTree searchTree;
    Movement movement;
    Polyglot polyglot("bin/book.bin");
    Play play(0);
////////////////////////////////////////////////////////////////

int main()
{
    play.run();

    gd::BitBoardPtr x = positionConverter.FEN_ToBitBoard("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    gd::BitBoardPtr y = positionConverter.FEN_ToBitBoard("rnbqkb1r/pppp1ppp/5n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R b KQkq - 3 3");




    //x = searchTree.iterativeDeepening(x, 1);

    //positionWriter.writeBitBoard(y);

    return 0;
}
//r1bq1rk1/p1pp1ppp/1pn2n2/4p1N1/1bB1P1Q1/2N5/PPPP1PPP/R1B1K2R w KQ - 0 1
//rnbqkb1r/pppp1ppp/5n2/4p3/4P3/2N2N2/PPPP1PPP/R1BQKB1R b KQkq - 3 3
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
