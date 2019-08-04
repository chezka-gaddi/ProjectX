#include "tournamentParser.h"
#include "utilities/inireader.h"
#include "utilities/mapLoader.h"

std::vector<bracket> parseBrackets(){
    std::string mName = "not_default", stats = "not_default", settings = "not_default";
    std::string images = "not_default", spawns = "not_default", section = "";
    int players = 0, count=0, rounds = 0;
    std::vector<bracket> bracketList;
    bracket tBracket;
    INIReader config("./tournament/map_list.ini");
    while (mName != "" && stats != "" && settings != "" && images != "" && players >= 0){
        //Save the previous data if we've started getting it
        if (count > 0){
            tBracket.mapName = mName;
            tBracket.stats = stats;
            tBracket.images = images;
            tBracket.settings = settings;
            tBracket.players = players;
            tBracket.spawns = spawns;
            tBracket.rounds = rounds;
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
        spawns = config.Get(section, "spawns", "");
        players = config.GetInteger(section, "players", -1);
        rounds = config.GetInteger(section, "rounds", 1);
    }

    return bracketList;
}

std::vector<player> parsePlayers(){
    std::string name = "not_default", images = "Default", section = "";
    int count=0;
    std::vector<player> playerList;
    player tPlayer;
    INIReader config("./tournament/player_list.ini");
        while (name != ""){
        //Save the previous data if we've started getting it
        if (count > 0){
            tPlayer.name = name;
            tPlayer.wins = 0;
            tPlayer.losses = 0;
            tPlayer.participated = 0;
            tPlayer.images = "images\\tanks\\" + images;
            tPlayer.id = count;
            playerList.push_back(tPlayer);
        }
        //Increment counter for section name
        count++;
        //build the section name
        section = "AI";
        if (count < 10){
            section += "0" + std::to_string(count);
        }else{
            section += std::to_string(count);
        }

        //Load the parameters
        name = config.Get(section, "name", "");
        images = config.Get(section, "images", "Default");
    }
    return playerList;
}

std::vector<std::pair<int,int>> parseSpawns(std::string spawnList){
    int count = 0;
    int x, y;
    int i = 0;
    INIReader config("./tournament/spawns_list.ini");
    std::vector<std::pair<int,int>> spawns;
    std::string key;

    count = config.GetInteger(spawnList, "number", 0);
    //printf("%s specified %d spawns.\n", spawnList.c_str(), count);
    if (count == 0)
        return spawns;

    for (i = 0; i <= count; i++){
        key = "spawnx" + std::to_string(i);
        x = config.GetInteger(spawnList, key, 0);
        key = "spawny" + std::to_string(i);
        y = config.GetInteger(spawnList, key, 0);
        if (x != 0 && y != 0){
            spawns.push_back(std::pair<int,int>(x, y));
        }
    }
    //printf("Found %d of %d spawns.\n", i - 1, count);

    return spawns;
}

attributes parseStats(std::string statList){
    attributes baseAttributes;
    INIReader config(".tournament/stats_list.ini");

    baseAttributes.tankDamage = config.GetInteger("statsList", "damage", 2);
    baseAttributes.tankHealth = config.GetInteger("statsList", "health", 2);
    baseAttributes.tankAP = config.GetInteger("statsList", "ap", 2);
    baseAttributes.tankRadar = config.GetInteger("statsList", "radar", 4);
    baseAttributes.tankAmmo = config.GetInteger("statsList", "ammo", 6);
    baseAttributes.projRange = config.GetInteger("statsList", "range", 4);
    baseAttributes.tankSpecial = config.GetInteger("statsList", "special", 1);

    return baseAttributes;
}
void parseSettings(std::string settingList, std::shared_ptr<Settings> settings){
    int maxturns=200, ai_speed=1, animation_frames=1, bullet_speed=1, tank_speed=1;

    INIReader config(".tournament/settings_list.ini");

    maxturns = config.GetInteger("settingList", "maxturns", 200);
    ai_speed = config.GetInteger("settingList", "ai_speed", 750);
    animation_frames = config.GetInteger("settingList", "animation_frames", 20);
    bullet_speed = config.GetInteger("settingList", "bullet_speed", 80);
    tank_speed = config.GetInteger("settingList", "tank_speed", 400);

    settings->setMaxTurns(maxturns);
    settings->setIdleSpeed(ai_speed);
    settings->setAniFrames(animation_frames);
    settings->setTankSpeed(tank_speed);
    settings->setBulletSpeed(bullet_speed);
}
void parseImages(){}
