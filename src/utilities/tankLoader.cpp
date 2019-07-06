//
// Created by jlee on 10/12/18.
//


#include "utilities/tankLoader.h"
#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <string>
#include "actors/Actor.h"


/**
 * @author David Donahue
 * @par Description:
 * Loads all of the given actors from ./tanks/<name>.so.
 * It works by loading the maker() function from each .so and running it
 * to get a pointer to an instance of the class.
 *
 * @param[in] objectNames - names of the actors to load.
 * @return vector of pointers to the loaded actors
 */
std::vector<Actor *> dynamicTankLoader(std::vector<std::string> objectNames)
{
    std::vector<Actor *> ret;
    std::string relPath ("./tanks/");
    std::string soPath;
    std::string symName;
    for (auto s : objectNames)
    {
        //build up the full realative file path from the given name
        soPath = (relPath);
        soPath.append(s);
        soPath.append(".so");

        //get a 'handle' to the .so file, which can be used to load symbols
        void * handle = dlopen(soPath.c_str(), RTLD_LAZY); //open the .so
        if (handle == NULL) //make sure it opened
        {
            std::cout << "Failed to open " << s << "\n";
            std::cout << dlerror() << std::endl;
        }
        else
        {
            Actor* (*maker)() = (Actor* (*)()) dlsym(handle, "maker"); //get the maker() symbol
            if (maker == NULL) //If the symbol was not found in the .so
            {
                std::cout << "Failed to load symbol " << symName << '\n';
            }
            else
            {
                ret.push_back(maker()); //Run maker() to construct an instance of the class
            }
        }

    }
    return ret;

}


