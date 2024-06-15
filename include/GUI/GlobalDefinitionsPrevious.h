#ifndef GLOBAL_DEFINITIONS_PREVIOUS_H
#define GLOBAL_DEFINITIONS_PREVIOUS_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include <thread>
#ifdef _WIN32
    #include <Windows.h>
    #include <conio.h>
#elif __APPLE__
    #include <termios.h>
    #include <unistd.h>
#elif __linux__
    #include <termios.h>
    #include <unistd.h>
#else
    #error the program only supports(Windows/Mac_OS/Linux)
#endif

namespace globalType{


    extern sf::RenderWindow *windowPtr;

    enum GameResult{
        engineWin,
        stalemate,
        userWin
    };
    enum MenuAction{
        goBack,
        backToGame,
        black,
        mainMenu,
        play,
        random,
        saveNotation,
        settings,
        watchPlayedGame,
        white,
        quit,
        displayPastMovements,
        knight,
        bishop,
        rook,
        queen
    } extern menuAction;

    using chessboardPointer = char(*)[8];
    using chessboardUnderlightPointer = bool(*)[8];
    struct errorType{std::string errorMessage;};

    extern bool windowResized;
    extern float windowWidth;
    extern float windowHeight;

    extern int numberOfButtonTexture;
    extern int numberOfBoardTexture;

//********************************************************************************
    void readConfigFile();
    void writeConfigFile();
}
#endif//GLOBAL_DEFINITIONS_PREVIOUS_H


