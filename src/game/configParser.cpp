#include "configParser.h"

MapData * parseConfig( Settings * settings){
    std::string configFile = settings->getConfigFile();
    bool quiet = settings->checkQuiet();

    INIReader config(configFile);
    //INIReader config("config.ini");
    MapData * map;

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
    //std::cout << "Images Section: \n"
    //          << "Field Image: \n" << config.Get("IMAGES", "fieldimage", "images/green.png") << "\n"
    //          << "Tree: \n" << config.Get("IMAGES", "tree", "") << "\n"
    //          << "Bush: \n" << config.Get("IMAGES", "bush", "") << "\n"
    //          << "Rock: \n" << config.Get("IMAGES", "rock", "") << "\n"
    //          << "Water: \n" << config.Get("IMAGES", "water", "") << "\n\n";
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



    return map;
}