//
// Created by jlee on 10/12/18.
//

#ifndef SRC_tankLoader_H
#define SRC_tankLoader_H

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <actors/Actor.h>

typedef void* makeTank_Fptr;

std::vector<Actor *> dynamicTankLoader(std::vector<std::string> objectNames);

#endif //SRC_tankLoader_H
