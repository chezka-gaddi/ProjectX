//
// Created by jlee on 10/12/18.
//


#include "DynamicLoader.h"
#include <dlfcn.h>
#include <fstream>
#include <iostream>
#include <Actor.h>
#include <string>


std::vector<Actor *> dynamicTankLoader(std::vector<std::string> objectNames)
{
    std::vector<Actor *> ret;
    std::string relPath ("./tanks/");
    for (auto s : objectNames)
    {
        s.insert(0, relPath);
        s.append(".so");
        void * handle = dlopen(s.c_str(), RTLD_LAZY);
        if (handle == NULL)
        {
            std::cout << "Failed to open " << s << "\n";
            std::cout << dlerror() << std::endl;
        }
        else
        {
            Actor* (*maker)() = (Actor* (*)()) dlsym(handle, "_ZN8SimpleAI5makerEv");
            if (maker == NULL)
            {
                std::cout << "Failed to load symbol\n";
            }
            else
            {
                std::cout << maker() << std::endl;
                ret.push_back(maker());
            }
        }

    }
    return ret;
    
}

void closeLibs()
{
    return;
}
