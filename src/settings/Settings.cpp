#include "../settings/Settings.h"
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
          if(ai_speed > 1500)
          {
            std::cout << "Speeds above 1500 are extremely slow, defaulting at 1500\n";
            ai_speed = 1500;
          }else if (ai_speed < 1){
            std::cout << "AI Speed of 0 introduces an uneccessary delay, defaulting to 1\n";
            ai_speed = 1;
          }
          if (!modeQuiet)
            std::cout << "   ...done.\n";  
  idleSpeed = ai_speed;
}
void Settings::setAniFrames(int aniSpeed){
  if (!modeQuiet)
    std::cout << "Slowing down time...  \n";
  if(aniSpeed > 30)
  {
    std::cout << "Speeds above 30 are slow, defaulting to 30\n";
    aniSpeed = 30;
  }else if (aniSpeed < 0){
    std::cout << "Speed below 0 are now allowed, defaulting to 0\n";
    aniSpeed = 0;
  }
  if (!modeQuiet)
    std::cout << "   ...done.\n";
  aniFrames = aniSpeed;
}
void Settings::setTankSpeed(int tank_speed){
  if (!modeQuiet)
    std::cout << "Greasing the wheels...  \n";
  if(tank_speed > 800)
  {
    std::cout << "Tank speeds above 800 are extremely slow, defaulting to 800\n";
    tank_speed = 800;
  }else if (tank_speed < 0){
    std::cout << "Tank speed below 0 are now allowed, defaulting to 0\n";
    tank_speed = 0;
  }
  if (!modeQuiet)
    std::cout << "   ...done.\n";
  tankSpeed = tank_speed;  
}
void Settings::setBulletSpeed(int bullet_speed){
  if (!modeQuiet){
    std::cout << "Putting helium in the bullets...  \n";
  }
    if(bullet_speed > 100)
  {
    std::cout << "Bullet speeds above 100 are extremely slow, defaulting to 100\n";
    bullet_speed = 100;
  }else if (bullet_speed < 0){
    std::cout << "Bullet speeds below 0 are now allowed, defaulting to 0\n";
    bullet_speed = 0;
  }
  if (!modeQuiet)
    std::cout << "   ...done.\n";
  bulletSpeed = bullet_speed;
}
void Settings::setMaxTurns(int maxT){
  if (!modeQuiet)
    std::cout << "Reducing camping spots...\n";
  if(maxT < 1)
  {
    maxT = 1;
    std::cout << "Invalid max_turn parameter (Less than 1), defaulting to 1.\n";
  }
  else if(maxT > 1000)
  {
    maxT = 1000;
    std::cout << "Max turns set too high, defaulting to 1000.\n";
  }
  maxTurns = maxT;
  if (!modeQuiet)
    std::cout << "   ...done.\n";  
}
void Settings::setGameMode(gameMode gm){ gMode = gm;}
void Settings::setTurn(int t){turn = t;}
void Settings::setActTurn(int at){actTurn = at;}
void Settings::setModCounter(int mc){modCounter = mc;}
void Settings::setUI(bool s){showui = s;}
void Settings::setQuietMode(bool q){modeQuiet = q;}

void Settings::setAttrDamage(int damage){
    if(damage < 0)
    {
        damage = 0;
        printf("Invalid damage value, defaulting to %d\n", damage);
    }
    else if(damage > 8)
    {
        printf("%d damage might be a little excesive, setting to 10\n", damage);
        damage = 8;
    }
    baseAttributes.tankDamage = damage;
}
void Settings::setAttrHealth(int health){
          if(health < 0)
          {
            health = 0;
            printf("Invalid health value, defaulting to %d\n", health);
          }
          else if(health > 8)
          {
            printf("%d health might be a little excesive, setting to 8\n", health);
            health = 8;
          }
baseAttributes.tankHealth = health;
}
void Settings::setAttrAP(int ap){
          if(ap < 0)
          {
            ap = 0;
            printf("Invalid number of action points value, defaulting to %d\n", ap);
          }
          else if(ap > 6)
          {
            printf("%d range might be a little excesive, setting to 6\n", ap);
            ap = 6;
          }
baseAttributes.tankAP = ap;
}
void Settings::setAttrRadar(int radar, int width){
          if(radar < 0)
          {
            radar = 0;
            printf("Invalid radar value, defaulting to %d\n", radar );
          }
          else if(radar > width)
          {
            printf("%d radar might be a little excesive, setting to %d\n", radar, width);
            radar = width;
          }
baseAttributes.tankRadar = radar;
}
void Settings::setAttrAmmo(int ammo){
          if(ammo < 0)
          {
            ammo = 0;
            printf("Invalid ammo amount, defaulting to %d\n", ammo);
          }
          else if(ammo > 10)
          {
            printf("%d ammo might be a little excesive, setting to 10.\n", ammo);
            ammo = 10;
          }
baseAttributes.tankAmmo = ammo;
}
void Settings::setAttrRange(int range){
          if(range < 0)
          {
            range = 0;
            printf("Invalid range value, defaulting to %d\n", range);
          }
          else if(range > 10)
          {
            printf("%d range might be a little excesive, setting to %d\n", range, 10);
            range = 10;
          }
baseAttributes.projRange = range;
}

void Settings::setAttrSpecial(int attributePoints){
          if(attributePoints < 0)
          {
            attributePoints = 0;
            printf("Invalid special value, defaulting to %d\n", attributePoints);
          }
          else if(attributePoints > 20)
          {
            printf("%d specials might be a little excesive, setting to 20.\n", attributePoints);
            attributePoints = 20;
          }
baseAttributes.tankSpecial = attributePoints;
}

void Settings::setResultsFile(std::string s){
  resultsFile = s;
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

std::string Settings::getResultsFile(){return resultsFile;}