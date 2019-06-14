#include "configParser.h"

bool parseConfig( Settings * settings){
    std::string configFile = settings->getConfigFile();

    //INIReader config(configFile);
    INIReader config("config.ini");

    int cerrors = config.ParseError();
    if (config.ParseError() != 0) {
        printf("Can't load %s\n", configFile.c_str());
        //return false;
    }
    std::cout << "Config loaded from " << configFile  << ": \n";
    std::cout << "Map Section: \n"
              << "Width: " << config.GetInteger("MAP", "width", 30) << "\n"
              << "Height: " << config.GetInteger("MAP", "height", 14) << "\n"
              << "Map: \n" << config.Get("MAP", "map", "") << "\n\n";
    std::cout << "Images Section: \n"
              << "Field Image: " << config.Get("IMAGES", "fieldimage", "images/green.png") << "\n"
              << "Tree: " << config.Get("IMAGES", "tree", "images/tree/tree.png") << "\n"
              << "Bush: " << config.Get("IMAGES", "bush", "images/bush/bush1.png") << "\n"
              << "Rock: " << config.Get("IMAGES", "rock", "images/rock/rock.png") << "\n"
              << "Water: " << config.Get("IMAGES", "water", "images/water/waterTex.png") << "\n\n";
    std::cout << "Stats Section: \n"
              << "Damage: " << config.GetInteger("STATS", "damage", 2) << "\n"
              << "Health: " << config.GetInteger("STATS", "health", 2) << "\n"
              << "Radar: " << config.GetInteger("STATS", "radar", 4) << "\n"
              << "AP: " << config.GetInteger("STATS", "ap", 2) << "\n"
              << "Special: " << config.GetInteger("STATS", "special", 1) << "\n"
              << "Range: " << config.GetInteger("STATS", "range", 4) << "\n"
              << "Ammo: " << config.GetInteger("STATS", "ammo", 6) << "\n\n";
    std::cout << "Game Section: \n"
              << "Max Turns: " << config.GetInteger("GAME", "maxturns", 200) << "\n\n";
    std::cout << "Platform Section: \n"
              << "AI Speed: " << config.GetInteger("PLATFORM", "ai_speed", 750) << "\n"
              << "Animation Frames: " << config.GetInteger("PLATFORM", "animation_frames", 20) << "\n"
              << "Bullet Speed: " << config.GetInteger("PLATFORM", "bullet_speed", 80) << "\n"
              << "Tank Speed: " << config.GetInteger("PLATFORM", "tank_speed", 400) << "\n\n";

    return true;
}