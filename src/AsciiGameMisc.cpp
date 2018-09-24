//
// Created by jlee on 9/24/18.
//

#include <iostream>
#include "AsciiGameMisc.h"
#include "Actor.h"

bool isplayable(std::vector<ActorInfo> actorInfo){
    int sum = 0;
    for(ActorInfo a: actorInfo){

        if(a.id == tankId){
            sum += 1;
        }
    }
    return sum >=2;
}
void displayAscii(GameField gameField, std::vector<ActorInfo> actorInfo){
    std::vector<std::string> asciiGameField();

    for(int i = 0; i <= gameField.getWidth(); i++){
        std::string tempString = "";
        for(int j = 0; j <= gameField.getHeight(); j++){
            tempString += ' ';
        }
        asciiGameField().push_back(tempString.c_str());
    }
    //populate the ascii field (only works on terminals with a constant width typeset)
    for(ActorInfo a: actorInfo){
        if(a.id == tankId){
            asciiGameField()[a.x][a.y] = 'T';
        }
        else{
            asciiGameField()[a.x][a.y] = 'O';
        }
    }
    for(int i = 0; i < 4; i++){
        std::cout << std::endl;
    }
    for(std::string s: asciiGameField()){
         std::cout << s << std::endl;
    }


}