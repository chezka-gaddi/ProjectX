#include <utilities/mapLoader.h>

std::shared_ptr<MapData> loadMap(std::shared_ptr<Settings> settings){
    std::shared_ptr<MapData> map;
    std::string key, args, fileLine, mapName = "maps/" + settings->getMapName();
    std::ifstream fin;
    fin.open(mapName);
    int width = 0, height = 0, x, y, i, hPad = 0, wPad = 0;
    bool quiet = settings->checkQuiet();
    

    if(!fin)
    {
        printf("ERROR: Unable to open map (%s).\n", mapName.c_str());
        exit(1);
    }

    while(!fin.eof())
    {
        getline(fin, fileLine);
        i = fileLine.find(' '); //index of first space
        key = fileLine.substr(0, i); //separate the identefier from the argumets
        args = fileLine.substr(i+1); 
    
        if(key == "WIDTH")
        {
            if (!quiet)
                std::cout << "S t r e t c h i n g   t h e   m a p . . .  ";
            std::stringstream(args) >> width;
            width = settings->checkSettingValue(5, 50, width, "width");
            if (!quiet)
                std::cout << "...done.\n";
        }
        else if(key == "HEIGHT")
        {
            if (!quiet)
                std::cout << "Elon\n    gati\n        ng t\n            he ma\n                p...  ";
            std::stringstream(args) >> height;
            height = settings->checkSettingValue(5, 21, height, "height");
            if (!quiet)
                std::cout << "\n                                                                   ...done.\n";
        }
        else if(key == "MAP\r")
        {
            if (width == 0 || height ==0){
                printf("ERROR: Problem with map file.  Width or Height not loaded before map section.");
                exit(1);
            }
            if (!quiet)
                    std::cout << "Building the map->..\n";
            map = std::shared_ptr<MapData>(new MapData(width, height));
            if(height < 9)
            {
                hPad = (9 - height) / 2;
                height = 9;
                //std::cout << "hPad: " << hPad << endl;
            }
            if(width < 15)
            {
                wPad = (15 - width) / 2;
                width = 15;
                //std::cout << "wPad: " << wPad << endl;
            }
            for(y=1; y <= hPad; y++)
            {
                for(x = 1; x <= width; x++)
                {
                    map->tileMap[y][x].type = "Hedgehog";
                    map->tileMap[y][x].health = 0;
                }
            }
            //cout << "Y equals: " << y << endl;
            while (y <= height - hPad)
            {
                if(y == height/3){
                if (!quiet)
                    std::cout << "  Planting trees...\n";
                }else if(y == height/3*2){
                if (!quiet)
                    std::cout << "  Moving rocks...\n";
                }else if(y == height-1){
                if (!quiet)
                    std::cout << "  Trimming bushes...\n";
                }
                getline(fin, fileLine);
                for(x = 1; x <= width; x++)
                {
                    if(x > (int) fileLine.size() + wPad)
                        {
                            map->tileMap[y][x].type = "Hedgehog";
                            map->tileMap[y][x].health = 0;
                        }
                        else if(x < wPad)
                        {
                            map->tileMap[y][x].type = "Hedgehog";
                            map->tileMap[y][x].health = 0;
                        }
                        else
                        {
                            switch(fileLine[x-wPad-1])
                            {
                            case 'B':
                            case 'b':
                                map->tileMap[y][x].type = "Bush";
                                map->tileMap[y][x].health = 1;
                                break;
                            case 'R':
                            case 'r':
                                map->tileMap[y][x].type = "Rock";
                                map->tileMap[y][x].health = 4;
                                break;
                            case 'T':
                            case 't':
                                map->tileMap[y][x].type = "Tree";
                                map->tileMap[y][x].health = 2;
                                break;
                            case 'W':
                            case 'w':
                                map->tileMap[y][x].type = "Water";
                                map->tileMap[y][x].health = 0;
                                break;
                            case 'C':
                            case 'c':
                                map->tileMap[y][x].type = "Crate";
                                map->tileMap[y][x].health = 1;
                                break;
                            case 'X':
                            case 'x':
                            case ' ':
                                break;
                            default:
                                map->tileMap[y][x].type = "Hedgehog";
                                map->tileMap[y][x].health = 0;
                                break;
                            }
                        }
                }
            y++;
            }
            while(y <= height)
            {
                for(x = 1; x <= width; x++)
                {
                    //obstacleLocations.push_back(std::pair<int, int> (x, y));
                    map->tileMap[y][x].type = "Hedgehog";
                    map->tileMap[y][x].health = 0;
                }
                y++;
            }
        }
    }
    return map;
}