/***************************************************************************//**
* @file gameTracker.h
* @author Jon McKee
* @brief set of function to create a game turn move tracker
*******************************************************************************/
#include <string>
#include <fstream>
#include <structures/direction.h>

class gameTracker{

public:
    gameTracker(std::string o);
    
    ~gameTracker(){};

    void move(std::string player, direction dir, int x, int y);
    void attack(std::string player, direction dir);
    void reload(std::string player);
    void kill(std::string player);
    void newTurn(int turn);
    void newPlayerTurn(int player);
    void open();
    void close();

private:
    std::ofstream fout;
    std::string outfile = "gameMoves.txt";

    std::string convertDirection(direction dir);
};