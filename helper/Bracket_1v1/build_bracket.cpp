////////////////////////////////////////////////////////////////////////////////
// Description: Reads in the list of tanks, then makes config files for each
//              Match of a bracket.
////////////////////////////////////////////////////////////////////////////////


// Include(s)
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main (int argc, char ** argv)
{
    ifstream tank_list;
    ofstream game_config;
    ifstream map;
    ifstream map_list_file;

    string temp;
    
    if(argc != 3)
    {
        cout << "Not the right amount of arguments" 
             << endl
             << "Command Should Look Like:"
             << endl
             << "./generate_bracket tank_list map_list"
             << endl;
        exit(1);
    }
    

    vector<string> map_list;
    map_list_file.open(argv[2]);

    while(!map_list_file.eof())
    {
        getline(map_list_file, temp);
        map_list.push_back(temp);
    }
    map_list_file.close();

    string tank1;
    string tank2;
    string config_name = "Round_1_1";


    tank_list.open(argv[1], ios::in);



    while(!tank_list.eof())
    {
        getline(tank_list, tank1);
        getline(tank_list, tank2);

        // TODO Check for odd number of tanks
        
        game_config.open(config_name.c_str());
        game_config << "# Tank List" << endl;
        game_config << "AI " << tank1 << endl;
        game_config << "AI " << tank2 << endl << endl << endl;
        
        map.open(map_list[rand() % map_list.size()]);
/*
        while(!map.eof())
        {
            getline(map, temp);
            game_config << temp << endl;
        }
       
        map.close();
  */       
        config_name[8]++;

    game_config.close();
    }

    tank_list.close();

    return 0;
    


}
