#include <utilities/mapLoader.h>

MapData loadMap(Settings settings){
    MapData map;
    std::string key, args, fileLine, mapName = settings.getMapName();
    std::ifstream fin("map/" + mapName);
    int width, height, x, y, i, hPad = 0, wPad = 0;
    bool quiet = settings.checkQuiet();
    
    //Location vectors
    std::vector<std::pair<int,int>> obstacleLocations, treeLocations, rockLocations, bushLocations,
      tankLocations, waterLocations, specialLocations;
    
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
            width = settings.checkSettingValue(5, 50, width, "width");
            if (!quiet)
                std::cout << "...done.\n";
        }
        else if(key == "HEIGHT")
        {
            if (!quiet)
                std::cout << "Elon\n    gati\n        ng t\n            he ma\n                p...  ";
            std::stringstream(args) >> height;
            height = settings.checkSettingValue(5, 21, height, "height");
            if (!quiet)
                std::cout << "\n                                                                   ...done.\n";
        }
        else if(fileLine == "MAP")
        {
            if (!quiet)
                    std::cout << "Building the map...\n";
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
            for(y=0; y < hPad; y++)
            {
                for(x = 0; x < width; x++)
                {
                obstacleLocations.push_back(std::pair<int, int> (x, y));
                }
            }
            //cout << "Y equals: " << y << endl;
            while (y < height - hPad)
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
                for(x = 0; x < width; x++)
                {
                    if(x >= (int) fileLine.size() + wPad)
                        {
                            obstacleLocations.push_back(std::pair<int,int> (x, y));
                        }
                        else if(x < wPad)
                        {
                            obstacleLocations.push_back(std::pair<int,int> (x, y));
                        }
                        else
                        {
                            switch(fileLine[x-wPad])
                            {
                            case 'B':
                            case 'b':
                                bushLocations.push_back(std::pair<int,int> (x, y));
                                break;
                            case 'R':
                            case 'r':
                                rockLocations.push_back(std::pair<int,int> (x, y));
                                break;
                            case 'T':
                            case 't':
                                treeLocations.push_back(std::pair<int,int> (x, y));
                                break;
                            case 'W':
                            case 'w':
                                waterLocations.push_back(std::pair<int,int> (x, y));
                                break;
                            case 'C':
                            case 'c':
                                specialLocations.push_back(std::pair<int,int> (x, y));
                                break;
                            case 'X':
                            case 'x':
                            case ' ':
                                break;
                            default:
                                obstacleLocations.push_back(std::pair<int, int> (x, y));
                                break;
                            }
                        }
                }
            y++;
            }
            while(y < height)
            {
                for(x = 0; x < width; x++)
                {
                obstacleLocations.push_back(std::pair<int, int> (x, y));
                }
                y++;
            }
        }
    }
    return map;
}