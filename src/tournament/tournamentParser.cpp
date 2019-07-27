#include "tournamentParser.h"
#include "utilities/inireader.h"
#include "utilities/mapLoader.h"

/*
std::shared_ptr<MapData> parseConfig( const std::shared_ptr<Settings> & settings){
    std::string configFile = settings->getConfigFile();
    bool quiet = settings->checkQuiet();

    if (!quiet)
        printf("%s...", configFile.c_str());
    INIReader config(configFile);
    std::shared_ptr<MapData> map;

    //Store the parse error/line number
    //Currently generates errors on lines that appear to be correctly written
    //int cerrors = config.ParseError();
    //if (config.ParseError() != 0) {
    //    printf("Can't load %s\n", configFile.c_str());
    //    return false;
    //}
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
} */

std::vector<bracket> parseBrackets(){
    std::string mName = "not_default", stats = "not_default", settings = "not_default";
    std::string images = "not_default", section = "";
    int players = 0, count=0;
    std::vector<bracket> bracketList;
    bracket tBracket;
    INIReader config("../../tournament/map_list.ini");
    while (mName != "" && stats != "" && settings != "" && images != "" && players >= 0){
        //Save the previous data if we've started getting it
        if (count > 0){
            tBracket.mapName = mName;
            tBracket.stats = stats;
            tBracket.images = images;
            tBracket.settings = settings;
            tBracket.players = players;
            bracketList.push_back(tBracket);
        }
        //Increment counter for section name
        count++;
        //build the section name
        section = "MAP";
        if (count < 10){
            section += "00" + std::to_string(count);
        } else if (count < 100){
            section += "0" + std::to_string(count);
        }

        //Load the parameters
        mName = config.Get(section, "name", "");
        stats = config.Get(section, "stats", "");
        settings = config.Get(section, "settings", "");
        images = config.Get(section, "images", "");
        players = config.GetInteger(section, "players", -1);
    }

    return bracketList;
}

void parseStats(){}
void parseSettings(){}
void parsePlayers(){}
void parseImages(){}