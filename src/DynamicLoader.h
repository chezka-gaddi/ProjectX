//
// Created by jlee on 10/12/18.
//

#ifndef SRC_DYNAMICLOADER_H
#define SRC_DYNAMICLOADER_H

#include "AsciiGameMisc.h"
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>

typedef Actor* makeTank_Fptr();
/**
 * singleton to hold the libraries file handles
 * @return
 */
std::vector<void*>* dl_List();
/**
 * singleton to hold a map between object names and tank maker functions
 * @return
 */
std::map<std::string, makeTank_Fptr>* TankMakers();


/**
 * loads the dl_list and tank maker singletons It should be noted that only one TankSetFile can be used at a time
 * @param TankSetFileName the file name listing the names of the .so files to load
 */
void dynamicLoader(std::string TankSetFileName);

/**
 * closes all open libraries should be used when done with libraries
 */
void closeLibs();

#endif //SRC_DYNAMICLOADER_H
