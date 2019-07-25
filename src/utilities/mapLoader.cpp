#include <utilities/mapLoader.h>

std::shared_ptr<MapData> loadMap(const std::shared_ptr<Settings> & settings){
    std::shared_ptr<MapData> map;
    std::string key, args, fileLine, mapName = "maps/" + settings->getMapName();
    std::ifstream fin;
    fin.open(mapName);
    int width = 0, height = 0, x, y, i, hPad = 0, wPad = 0;
    bool quiet = settings->checkQuiet();
    if (!quiet)
        printf("Loading map...\n");

    if(!fin)
    {
        printf("ERROR: Unable to open map (%s) file.\n", mapName.c_str());
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
                printf("   Reading map width\n");
            std::stringstream(args) >> width;
            width = settings->checkSettingValue(5, 50, width, "width");
        }
        else if(key == "HEIGHT")
        {
            if (!quiet)
                printf("   Reading map height\n");
            std::stringstream(args) >> height;
            height = settings->checkSettingValue(5, 21, height, "height");
        }
        else if(key == "MAP\r")
        {
            if (width == 0 || height ==0){
                printf("ERROR: Problem with map file or structure.  Width or Height not loaded before [MAP] section.");
                exit(1);
            }
            if (!quiet)
                    printf("   Reading map...\n");
            map = std::shared_ptr<MapData>(new MapData(width, height));
            if(height < 9)
            {
                hPad = (9 - height) / 2;
                height = 9;
                //printf("hPad: ", hPad);
            }
            if(width < 15)
            {
                wPad = (15 - width) / 2;
                width = 15;
                //printf("wPad: ", wPad);
            }
            for(y=1; y <= hPad; y++)
            {
                for(x = 1; x <= width; x++)
                {
                    map->tileMap[y][x].type = "Hedgehog";
                    map->tileMap[y][x].health = 0;
                }
            }
            while (y <= height - hPad)
            {
                getline(fin, fileLine);
                if (!quiet)
                    printf("      %s\n", fileLine.c_str());
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
            if (!quiet)
                printf("            ...Done.\n");
        }
    }
    return map;
}