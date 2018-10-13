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
    std::string soPath;
    std::string symName;
    for (auto s : objectNames)
    {
        soPath = (relPath);
        soPath.append(s);
        soPath.append(".so");

        //C++ is nice enough to scramble all the symbol names, and there is no way to get them at runtime...
        //Fun! this should predict the scrambled name based on my testing, but it is likely extraordinarily
        //fragile. TODO: find a way to read the symbol list into the program and search for maker
        symName = "_ZN8";
        symName.append(s);
        symName.append("5makerEv");
            
        
        void * handle = dlopen(soPath.c_str(), RTLD_LAZY); //open the .so
        if (handle == NULL) //make sure it opened
        {
            std::cout << "Failed to open " << s << "\n";
            std::cout << dlerror() << std::endl;
        }
        else
        {
            Actor* (*maker)() = (Actor* (*)()) dlsym(handle, symName.c_str()); //get the maker() symbol
            if (maker == NULL)
            {
                std::cout << "Failed to load symbol " << symName << '\n';
            }
            else
            {
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
