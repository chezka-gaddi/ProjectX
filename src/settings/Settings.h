/***************************************************************************//**
* @file settings.h
* @author Jonathan McKee
* @brief Contains all functions prototypes the settings class.
*******************************************************************************/
#ifndef __settings_h
#define __settings_h

#include <attributes.h>
#include <string>

class GameField; //Forward declare it for pointer

/*!<Enum class for the gameMode */
enum gameMode {none, ai, sp, mp, quiet, coverage, tournament, noui};

/***************************************************************************//**
* @author Jonathan McKee
* @brief Class
*
* Settings is an interface for loading and hold all of the game settings
*******************************************************************************/
class Settings
{
public:
    //getters
    attributes getAttributes();
    int getIdleSpeed();
    int getAniFrames();
    int getTankSpeed();
    int getBulletSpeed();
    int getMaxTurns();
    gameMode getGameMode();
    int getTurn();
    int getActTurn();
    int getModCounter();
    bool showUI();
    std::string getResultsFile();

    //individual attribute getters
    int getAttrDamage();
    int getAttrHealth();
    int getAttrAP();
    int getAttrRadar();
    int getAttrAmmo();
    int getAttrRange();
    int getAttrSpecial();
    bool checkCoverage();
    bool checkQuiet();

    void nextTurn();

    //setters
    void setAttributes(attributes attr);
    void setIdleSpeed(int is);
    void setAniFrames(int af);
    void setTankSpeed(int ts);
    void setBulletSpeed(int bs);
    void setMaxTurns(int mt);
    void setGameMode(gameMode gm);
    void setTurn(int t);
    void setActTurn(int at);
    void setModCounter(int mc);
    void setUI(bool set);
    void setCoverageMode(bool c);
    void setQuietMode(bool q);
    void setResultsFile(std::string r);

    //individual attribute setters
    void setAttrDamage(int damage);
    void setAttrHealth(int health);
    void setAttrAP(int ap);
    void setAttrRadar(int radar, int width);
    void setAttrAmmo(int ammo);
    void setAttrRange(int range);
    void setAttrSpecial(int special);

private:
    //default game settings
    int maxTurns = 1000;
    attributes baseAttributes;
    
    //Speed settings
    int idleSpeed = 750;
    int aniFrames = 20;
    int tankSpeed = 400;
    int bulletSpeed = 80;

    //pointers to components
    GameField *tankGame;   //Pointer to gamefield
    gameMode gMode = ai;  //default game mode

    //Current Match Settings
    int turn = 0; //Current game turn
    int actTurn = 0; //0 causes issues on first display call
    int modCounter = 7; //Modular counter for animation effects

    //platform settings
    bool modeQuiet = false; //quiet mode for blocking text
    bool modeCoverage = false; //coverage mode for faster animations
    bool showui = true; //should we display the ui
    std::string resultsFile = "results.txt"; //results output file
};

#endif //__GAME_H
