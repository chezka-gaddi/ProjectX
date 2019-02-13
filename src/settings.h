/***************************************************************************//**
* @file settings.h
* @author Jonathan McKee
* @brief Contains all functions prototypes the settings class.
*******************************************************************************/
#ifndef __settings_h
#define __settings_h

/*!<Enum class for the gameMode */
enum gameMode {none, ai, sp, mp, quiet, coverage};

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

    //setters
    void setAttributes();
    void setIdleSpeed();
    void setAniFrames();
    void setTankSpeed();
    void setBulletSpeed();
    void setMaxTurns();
    void setGameMode();
    void setTurn();
    void setActTurn();
    void setModCounter();

private:
    //default game settings
    int max_turns = 200;
    attributes baseAttributes;
    
    //Speed settings
    int idleSpeed = 750;
    int aniFrames = 20;
    int tankSpeed = 400;
    int bulletSpeed = 80;

    //pointers to components
    GameField *tankGame;   //Pointer to gamefield
    gameMode g_mode = ai;  //default game mode
    int turn = 0; //Current game turn
    int actTurn = 0; //0 causes issues on first display call
    int modCounter = 7; //Modular counter for animation effects
};

#endif //__GAME_H
