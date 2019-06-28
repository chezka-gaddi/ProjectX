#include <utilities/mapLoader.h>

MapData * loadMap(Settings * settings){
    MapData * map = new MapData();
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
            map->width = width;
            if (!quiet)
                std::cout << "...done.\n";
        }
        else if(key == "HEIGHT")
        {
            if (!quiet)
                std::cout << "Elon\n    gati\n        ng t\n            he ma\n                p...  ";
            std::stringstream(args) >> height;
            height = settings->checkSettingValue(5, 21, height, "height");
            map->height = height;
            if (!quiet)
                std::cout << "\n                                                                   ...done.\n";
        }
        else if(fileLine == "MAP")
        {
            if (width == 0 || height ==0){
                printf("ERROR: Problem with map file.  Width or Height not loaded before map section.");
                exit(1);
            }
            if (!quiet)
                    std::cout << "Building the map->..\n";
            map->generateTileMap();
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
                    //obstacleLocations.push_back(std::pair<int, int> (x, y));
                    map->tileMap[y][x].type = "Hedgehog";
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
                            //obstacleLocations.push_back(std::pair<int,int> (x, y));
                            map->tileMap[y][x].type = "Hedgehog";
                        }
                        else if(x < wPad)
                        {
                            //obstacleLocations.push_back(std::pair<int,int> (x, y));
                            map->tileMap[y][x].type = "Hedgehog";
                        }
                        else
                        {
                            switch(fileLine[x-wPad-1])
                            {
                            case 'B':
                            case 'b':
                                //bushLocations.push_back(std::pair<int,int> (x, y));
                                map->tileMap[y][x].type = "Bush";
                                break;
                            case 'R':
                            case 'r':
                                //rockLocations.push_back(std::pair<int,int> (x, y));
                                map->tileMap[y][x].type = "Rock";
                                break;
                            case 'T':
                            case 't':
                                //treeLocations.push_back(std::pair<int,int> (x, y));
                                map->tileMap[y][x].type = "Tree";
                                break;
                            case 'W':
                            case 'w':
                                //waterLocations.push_back(std::pair<int,int> (x, y));
                                map->tileMap[y][x].type = "Water";
                                break;
                            case 'C':
                            case 'c':
                                //specialLocations.push_back(std::pair<int,int> (x, y));
                                map->tileMap[y][x].type = "Crate";
                                break;
                            case 'X':
                            case 'x':
                            case ' ':
                                break;
                            default:
                                //obstacleLocations.push_back(std::pair<int, int> (x, y));
                                map->tileMap[y][x].type = "Hedgehog";
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
                }
                y++;
            }
        }
    }
    return map;
}