#include "../../include/GUI/GlobalDefinitionsPrevious.h"

namespace globalType{

    sf::RenderWindow *windowPtr;

    bool windowResized;
    float windowWidth  = 1000;
    float windowHeight = 750;

    MenuAction menuAction;

    int numberOfButtonTexture;
    int numberOfBoardTexture;
//********************************************************************************
    void readConfigFile()
    {
        std::ifstream reading;
        std::string data;
        try
        {
            reading.open("resources/config.txt");
            if (!reading.is_open())
                throw std::ifstream::failure("The file 'config.txt' cannot be opened .");
            if (!getline(reading, data))
                throw std::ifstream::failure("Error reading character from 'config.txt' file .");
        }
        catch(const std::ifstream::failure &e)
        {
            errorType x;
            x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
            throw x;
        }
        reading.close();

        numberOfButtonTexture     = static_cast<int>(data[0] - '0');
        numberOfBoardTexture      = static_cast<int>(data[1] - '0');
    }
    void writeConfigFile()
    {
        std::string data{};
        data += static_cast<char>(numberOfButtonTexture     + '0');
        data += static_cast<char>(numberOfBoardTexture      + '0');

        std::ofstream file("resources/config.txt");
        try
        {
            if (!file.is_open())
                throw std::ofstream::failure("The file could not be opened for writing.");
        }
        catch(const std::ofstream::failure &e)
        {
            errorType x;
            x.errorMessage = __PRETTY_FUNCTION__ + std::string(" >> error: ") + e.what();
            throw x;
        }
        file << data;
        file.close();
    }
}

