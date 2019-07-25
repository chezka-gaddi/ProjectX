#include "configParser.h"
#include "utilities/inireader.h"
#include "utilities/mapLoader.h"


std::shared_ptr<MapData> parseConfig( const std::shared_ptr<Settings> & settings){
    std::string configFile = settings->getConfigFile();
    //bool quiet = settings->checkQuiet();

    INIReader config(configFile);
    //INIReader config("config.ini");
   std::shared_ptr<MapData> map;

    //Store the parse error/line number
    //int cerrors = config.ParseError();
    //if (config.ParseError() != 0) {
    //    printf("Can't load %s\n", configFile.c_str());
    //    return false;
    //}
    //std::cout << "Config loaded from " << configFile  << ": \n";
    //Load the map
    settings->setMapName(config.Get("MAP","name","default.map"));
    map = loadMap(settings);
    //Player Stats
    settings->setAttrDamage(config.GetInteger("STATS", "damage", 2));
    settings->setAttrHealth(config.GetInteger("STATS", "health", 2));
    settings->setAttrRadar(config.GetInteger("STATS", "radar", 4), map->width);
    settings->setAttrAP(config.GetInteger("STATS", "ap", 2));
    settings->setAttrSpecial(config.GetInteger("STATS", "special", 1));
    settings->setAttrRange(config.GetInteger("STATS", "range", 4));
    settings->setAttrAmmo(config.GetInteger("STATS", "ammo", 6));
    //Game Settings
    settings->setMaxTurns(config.GetInteger("GAME", "maxturns", 200));
    //Platform Settings
    settings->setIdleSpeed(config.GetInteger("PLATFORM", "ai_speed", 750));
    settings->setAniFrames(config.GetInteger("PLATFORM", "animation_frames", 20));
    settings->setBulletSpeed(config.GetInteger("PLATFORM", "bullet_speed", 80));
    settings->setTankSpeed(config.GetInteger("PLATFORM", "tank_speed", 400));
    settings->setInstantProj(config.GetBoolean("PROJECTILE", "instant", false));
    return map;
}

std::vector<std::string> parseList(const std::shared_ptr<Settings> & settings, std::string section, std::string key){
    std::string configFile = settings->getConfigFile(), temp;
    //bool quiet = settings->checkQuiet();
    bool done = false;
    int i = 0;
    INIReader config(configFile);

    std::vector<std::string> list;

    temp = config.Get(section, key, "\n");
    if (temp == ""){
        return list;
    }
    
    while(!done)
    {
        if(temp.find('\n') == std::string::npos)
        {
        done = true;
        list.push_back(temp);
        }
        else
        {
        i = temp.find('\n');
        list.push_back(temp.substr(0, i));
        temp = temp.substr(i + 1);
        }

    }

    return list;
}

std::string parseAI(const std::shared_ptr<Settings> & settings, std::string section, std::string key){
    std::string configFile = settings->getConfigFile(), param;
    //bool quiet = settings->checkQuiet();
    INIReader config(configFile);

    param = config.Get(section, key, "");
    return param;
}