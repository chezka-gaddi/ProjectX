#include "Settings.h"
#include <stdio.h>
#include <iostream>

attributes Settings::getAttributes(){return baseAttributes;}
int Settings::getIdleSpeed(){return idleSpeed;}
int Settings::getAniFrames(){return aniFrames;}
int Settings::getTankSpeed(){return tankSpeed;}
int Settings::getBulletSpeed(){return bulletSpeed;}
int Settings::getMaxTurns(){return maxTurns;}
gameMode Settings::getGameMode(){ return gMode;}

//setters
void Settings::setAttributes(attributes attr){baseAttributes = attr;}
void Settings::setIdleSpeed(int ai_speed){
  idleSpeed = checkSettingValue(1, 1500, ai_speed, "idle speed", !modeQuiet);
}
void Settings::setAniFrames(int aniSpeed){
  aniFrames = checkSettingValue(0, 30, aniSpeed, "animation frames", !modeQuiet);
}
void Settings::setTankSpeed(int tank_speed){
  tankSpeed = checkSettingValue(0, 800, tank_speed, "tank speed", !modeQuiet);    
}
void Settings::setBulletSpeed(int bullet_speed){
  bulletSpeed = checkSettingValue(0, 100, bullet_speed, "bullet speed", !modeQuiet);
}
void Settings::setMaxTurns(int maxT){
  maxTurns = checkSettingValue(1, 1000, maxT, "max turns", !modeQuiet);
}
void Settings::setGameMode(gameMode gm){ gMode = gm;}
void Settings::setUI(bool s){showui = s;}
void Settings::setQuietMode(bool q){modeQuiet = q;}
void Settings::setTrackingMode(bool t){tracking = t;}
void Settings::setMapName(std::string m){mapName = m;}
void Settings::setInstantProj(bool p){projInstant = p;}

void Settings::setAttrDamage(int damage){
  baseAttributes.tankDamage = checkSettingValue(0, 8, damage, "damage", !modeQuiet);
}
void Settings::setAttrHealth(int health){
  baseAttributes.tankHealth = checkSettingValue(0, 8, health, "health", !modeQuiet);
}
void Settings::setAttrAP(int ap){
  baseAttributes.tankAP = checkSettingValue(0, 6, ap, "action points", !modeQuiet);
}
void Settings::setAttrRadar(int radar, int width){
  baseAttributes.tankRadar = checkSettingValue(0, width, radar, "radar", !modeQuiet);
}
void Settings::setAttrAmmo(int ammo){
  baseAttributes.tankAmmo = checkSettingValue(0, 10, ammo, "ammo", !modeQuiet);
}
void Settings::setAttrRange(int range){
  baseAttributes.projRange = checkSettingValue(0, 10, range, "range", !modeQuiet);
}

void Settings::setAttrSpecial(int attributePoints){
  baseAttributes.tankSpecial = checkSettingValue(0, 20, attributePoints, "special points", !modeQuiet);
}

void Settings::setResultsFile(std::string s){
  resultsFile = s;
}

void Settings::setConfigFile(std::string c){
  configFile = c;
}

int Settings::getAttrDamage(){return baseAttributes.tankDamage;}
int Settings::getAttrHealth(){return baseAttributes.tankHealth;}
int Settings::getAttrAP(){return baseAttributes.tankAP;}
int Settings::getAttrRadar(){return baseAttributes.tankRadar;}
int Settings::getAttrAmmo(){return baseAttributes.tankAmmo;}
int Settings::getAttrRange(){return baseAttributes.projRange;}
int Settings::getAttrSpecial(){return baseAttributes.tankSpecial;}

bool Settings::showUI(){return showui;}

void Settings::setCoverageMode(bool c){modeCoverage = c;}
bool Settings::checkCoverage(){return modeCoverage;}
bool Settings::checkQuiet(){return modeQuiet;}
bool Settings::checkTracking(){return tracking;}
bool Settings::checkInstantProj(){return projInstant;}

std::string Settings::getResultsFile(){return resultsFile;}
std::string Settings::getConfigFile(){return configFile;}
std::string Settings::getMapName(){return mapName;}

int Settings::checkSettingValue(int min, int max, int value, std::string param, bool force){
  if(value < min)
  {
    value = min;
    printf("WARNING: Invalid %s value, defaulting to %d\n", param.c_str(), min);
  }
  else if(value > max)
  {
    printf("WARNING: %d %s is too high, setting to %d.\n", value, param.c_str(), max);
    value = max;
  }else if (force){
    printf("   The %s was set to %d.\n", param.c_str(), value);
  }
  return value;
}