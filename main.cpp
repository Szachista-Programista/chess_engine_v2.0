#include "include/SearchTree.hpp"
#include "include/PositionWriter.hpp"
#include <chrono>////////////





int main()
{
    PositionConverter positionConverter;
    PositionWriter positionWriter;
    SearchTree searchTree;
    WhiteChildren wc;
    BlackChildren bc;

    gd::BitBoardPtr a,b,c,x = positionConverter.convert_FEN_NotationToBitBoard
    ("r1bqkb1r/pppp1ppp/2n2n2/4p1N1/2B1P3/8/PPPP1PPP/RNBQK2R w KQkq - 0 1");




    int depth = 8;

    auto start = std::chrono::high_resolution_clock::now();
    //////////////////
    b = searchTree.findByAlphaBeta(x, depth, 1);
    //////////////////
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout<< std::endl << "Czas wykonania \"findByAlphaBeta\"    : " << duration.count() << " ms" << std::endl;
     start = std::chrono::high_resolution_clock::now();
    //////////////////
    c = searchTree.iterativeDeepening(x, depth, 1);
    //////////////////
     stop = std::chrono::high_resolution_clock::now();
     duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout<< std::endl << "Czas wykonania \"iterativeDeepening\" : " << duration.count() << " ms" << std::endl;



    positionWriter.writeChessboard(x);
    positionWriter.writeChessboard(b);
    positionWriter.writeChessboard(c);


/*
    unsigned long long iterations = 0;    auto start = std::chrono::steady_clock::now();    const int time_limit_seconds = 2;
    while (true)
    {

    iterations++;    auto current = std::chrono::steady_clock::now(); if (std::chrono::duration_cast<std::chrono::seconds>(current - start).count() >= time_limit_seconds) break;
    }
    std::cout << "Program wykonano przez " << time_limit_seconds << " sekundy." << std::endl << "Liczba wykonanych iteracji: " << iterations << std::endl;
*/
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
