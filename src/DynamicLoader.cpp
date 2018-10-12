//
// Created by jlee on 10/12/18.
//

#include "DynamicLoader.h"
#include <dlfcn.h>
#include <fstream>

std::vector<void*>* dl_List(){

    static std::vector<void*> * handleList = new std::vector<void*>();

    return handleList;
}

std::map<std::string,makeTank_Fptr > * TankMakers(){
    static std::map<std::string,makeTank_Fptr > * Makers = new std::map<std::string,makeTank_Fptr >();

    return Makers;
};

void dynamicLoader(std::string TankSetFileName){

    std::ifstream SetFile;

    SetFile.open(TankSetFileName, std::ifstream::in);

    std::vector<std::string> files = std::vector<std::string>();
    std::string line;

    //gets all of the library file names
    while(getline(SetFile,line)){
        files.push_back(line);
    }
    //dont need the Set file open anymore
    SetFile.close();

    //populate dl_List and tank makers
    for(std::string s: files){
        std::string relativePath = "./tanks/objects/";

        relativePath += s;

        //gets a handle to the shared library and loads the library
        dl_List()->push_back(dlopen( relativePath.c_str(), RTLD_NOW));
        //makes sure the handle isnt null
        if( dl_List()->at(dl_List()->size() -1) != nullptr){
            makeTank_Fptr temp = static_cast<makeTank_Fptr>(dlsym(dl_List()->at(dl_List()->size()-1),"makeTank"));
            TankMakers()->insert(std::pair<std::string,makeTank_Fptr>(s, temp));
            temp = nullptr;
        }

        //TankMakers should be populated now
    }

}

void closeLibs(){
    for(void * handle: *dl_List()){
        dlclose(handle);
    }
}