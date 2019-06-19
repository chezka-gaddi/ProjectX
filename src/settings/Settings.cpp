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
int Settings::getTurn(){return turn;}
int Settings::getActTurn(){return actTurn;}
int Settings::getModCounter(){return modCounter;}

void Settings::nextTurn(){turn++;}

//setters
void Settings::setAttributes(attributes attr){baseAttributes = attr;}
void Settings::setIdleSpeed(int ai_speed){
  if (!modeQuiet)
    std::cout << "Speeding up the AI's...  \n";
  idleSpeed = checkSettingValue(1, 1500, ai_speed, "idle speed");
  if (!modeQuiet)
    std::cout << "   ...done.\n";  
}
void Settings::setAniFrames(int aniSpeed){
  if (!modeQuiet)
    std::cout << "Slowing down time...  \n";
  aniFrames = checkSettingValue(0, 30, aniSpeed, "animation frames");
  if (!modeQuiet)
    std::cout << "   ...done.\n";
}
void Settings::setTankSpeed(int tank_speed){
  if (!modeQuiet)
    std::cout << "Greasing the wheels...  \n";
  tankSpeed = checkSettingValue(0, 800, tank_speed, "tank speed");  
  if (!modeQuiet)
    std::cout << "   ...done.\n";
  
}
void Settings::setBulletSpeed(int bullet_speed){
  if (!modeQuiet){
    std::cout << "Putting helium in the bullets...  \n";
  }
  bulletSpeed = checkSettingValue(0, 100, bullet_speed, "bullet speed");
  if (!modeQuiet)
    std::cout << "   ...done.\n";
}
void Settings::setMaxTurns(int maxT){
  if (!modeQuiet)
    std::cout << "Reducing camping spots...\n";
  maxTurns = checkSettingValue(1, 1000, maxT, "max turns");
  if (!modeQuiet)
    std::cout << "   ...done.\n";  
}
void Settings::setGameMode(gameMode gm){ gMode = gm;}
void Settings::setTurn(int t){turn = t;}
void Settings::setActTurn(int at){actTurn = at;}
void Settings::setModCounter(int mc){modCounter = mc;}
void Settings::setUI(bool s){showui = s;}
void Settings::setQuietMode(bool q){modeQuiet = q;}
void Settings::setTrackingMode(bool t){tracking = t;}

void Settings::setAttrDamage(int damage){
  baseAttributes.tankDamage = checkSettingValue(0, 8, damage, "damage");
}
void Settings::setAttrHealth(int health){
  baseAttributes.tankHealth = checkSettingValue(0, 8, health, "health");
}
void Settings::setAttrAP(int ap){
  baseAttributes.tankAP = checkSettingValue(0, 6, ap, "action points");
}
void Settings::setAttrRadar(int radar, int width){
  baseAttributes.tankRadar = checkSettingValue(0, width, radar, "radar");
}
void Settings::setAttrAmmo(int ammo){
  baseAttributes.tankAmmo = checkSettingValue(0, 10, ammo, "ammo");
}
void Settings::setAttrRange(int range){
  baseAttributes.projRange = checkSettingValue(0, 10, range, "range");
}

void Settings::setAttrSpecial(int attributePoints){
  baseAttributes.tankSpecial = checkSettingValue(0, 20, attributePoints, "special points");
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

std::string Settings::getResultsFile(){return resultsFile;}
std::string Settings::getConfigFile(){return configFile;}

int Settings::checkSettingValue(int min, int max, int value, std::string param){
  if(value < min)
  {
    value = min;
    printf("WARNING: Invalid %s value, defaulting to %d\n", param.c_str(), min);
  }
  else if(value > max)
  {
    printf("WARNING: %d %s is too high, setting to %d.\n", value, param.c_str(), max);
    value = max;
  }
  return value;
}