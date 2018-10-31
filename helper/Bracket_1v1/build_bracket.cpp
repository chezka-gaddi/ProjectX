////////////////////////////////////////////////////////////////////////////////
// Description: Reads in the list of tanks, then makes config files for each
//              Match of a bracket.
////////////////////////////////////////////////////////////////////////////////


// Include(s)
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

// Input looks like ./EXE tank_list map_list
 
int main (int argc, char ** argv)
{
    ifstream tank_list;
    ofstream game_config;
    ifstream map;
    ifstream map_list;
    
    string temp;
    vector<string> tanks;
    vector<string> maps;
    string base_file_name;
    int map_id = 0;
    // Load Tanks
    tank_list.open(argv[1]);
    if (!tank_list.is_open())
    {
        cout << "Cant open tanks" << endl;
        exit(1);
    }

    while(!tank_list.eof())
    {
        getline(tank_list, temp);
        tanks.push_back(temp);
    }
    tank_list.close();


    // Load Maps
    map_list.open(argv[2]);
    if (!map_list.is_open())
    {
        cout << "Cant open maps" << endl;
        exit(1);
    }

    while(!map_list.eof())
    {
        getline(map_list, temp);
        maps.push_back(temp);
    }

    map_list.close();

    // Build a Game for each possible tank combo
    
    
    srand(time(NULL));
    for(int tank_1 = 0; tank_1 < tanks.size() - 1; tank_1++)
    {
        for(int tank_2 = tank_1 + 1; tank_2 < tanks.size() - 1 ; tank_2++)
        {
        base_file_name = tanks.at(tank_1) + "vs" + tanks.at(tank_2);
        game_config.open(base_file_name);
            map_id = rand() % maps.size() - 1;
            
            map.open(maps[map_id]);
            // copy over the map to the game config
            game_config << "Map: " << maps.at(map_id) << endl;
            while(!map.eof())
            {
                getline(map, temp);
                game_config << temp << endl;
            }
            map.close();
            
            game_config << "AI " << tanks.at(tank_1) << " 0 0 images/Blue/tankB_U.png images/Blue/tankB_R.png images/Blue/tankB_D.png images/Blue/tankB_L.png images/Blue/bulletB.png" << endl;
            game_config << "AI " << tanks.at(tank_2) << " 29 12 images/Red/tankR_U.png images/Red/tankR_R.png images/Red/tankR_D.png images/Red/tankR_L.png images/Red/bulletR.png" << endl;


            game_config << "#Game Rules" << endl;

            game_config << "DAMAGE 1" << endl;
            game_config << "HEALTH 2" << endl;
            game_config << "RADAR 10" << endl;
            game_config << "AP 5" << endl;
            game_config << "SPECIAL 1" << endl;

        game_config.close();
        }
    }


    return 0;



}
