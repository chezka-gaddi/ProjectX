/***************************************************************************//**
* @file settings.h
* @author Jonathan McKee
* @brief Contains all functions prototypes the settings class.
*******************************************************************************/
#ifndef __settings_h
#define __settings_h

#include <structures/attributes.h>
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
    std::string getResultsFile();
    std::string getConfigFile();
    std::string getMapName();
    bool checkInstantProj();

    //mode checkers
    bool checkCoverage();
    bool checkQuiet();
    bool showUI();
    bool checkTracking();

    //individual attribute getters
    int getAttrDamage();
    int getAttrHealth();
    int getAttrAP();
    int getAttrRadar();
    int getAttrAmmo();
    int getAttrRange();
    int getAttrSpecial();

    //setters
    void setAttributes(attributes attr);
    void setIdleSpeed(int is);
    void setAniFrames(int af);
    void setTankSpeed(int ts);
    void setBulletSpeed(int bs);
    void setMaxTurns(int mt);
    void setGameMode(gameMode gm);
    void setUI(bool set);
    void setCoverageMode(bool c);
    void setQuietMode(bool q);
    void setResultsFile(std::string r);
    void setConfigFile(std::string c);
    void setTrackingFile(std::string t);
    void setTrackingMode(bool t);
    void setMapName(std::string m);
    void setInstantProj(bool p);

    //individual attribute setters
    void setAttrDamage(int damage);
    void setAttrHealth(int health);
    void setAttrAP(int ap);
    void setAttrRadar(int radar, int width);
    void setAttrAmmo(int ammo);
    void setAttrRange(int range);
    void setAttrSpecial(int special);

    //Helper functions
    int checkSettingValue(int, int, int, std::string);
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

    //platform settings
    bool modeQuiet = false; //quiet mode for blocking text
    bool modeCoverage = false; //coverage mode for faster animations
    bool showui = true; //should we display the ui
    std::string resultsFile = "results.txt"; //results output file
    std::string configFile = "config.ini"; //Config ini file
    std::string mapName = "default.map"; //map file name
    bool tracking = false; //track all actions to file
    bool projInstant = false; //Single turn projectiles
};

#endif //__GAME_H
