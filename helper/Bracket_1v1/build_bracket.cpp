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
    vector<string> round_matchup;
    map_list_file.open(argv[2]);

    while(!map_list_file.eof())
    {
        getline(map_list_file, temp);
        map_list.push_back(temp);
    }
    map_list_file.close();

    string tank1;
    string tank2;
    string config_name = "OneVOneTournament/Round_1_1";

    int random;

    tank_list.open(argv[1], ios::in);



    while(!tank_list.eof())
    {
        getline(tank_list, tank1);
        getline(tank_list, tank2);

        round_matchup.push_back(tank1);
        round_matchup.push_back(tank2);

        if(tank1.empty() || tank2.empty())
        {
            break;
        }

        // TODO Check for odd number of tanks

        game_config.open(config_name.c_str());

        random = rand() % map_list.size() - 1;
        game_config << "#Map: "<< map_list[random] << endl;
        map.open(map_list[random]);

        if(map.is_open())
        {
            cout << "Map Opened" << endl;
            while(temp != "Spawn Points x, y")
            {
                getline(map, temp);
                game_config << temp << endl;
            }

            game_config << "# Tank List" << endl;
            while( round_matchup.size() != 0)
            {
               getline(map, temp);
               game_config << "AI "  <<round_matchup.back() << " " << temp << endl;
               round_matchup.pop_back();
            }


        }
        map.close();

        tank1.erase();
        tank2.erase();




        game_config  << endl << "#Tank rules" << endl
            << "DAMAGE 1"
            << endl
            << "HEALTH 2"
            << endl
            << "AP 2"
            << endl
            << "SPECIAL 1"
            << endl;




        game_config.close();
        config_name.back()++;


    }

    tank_list.close();

    return 0;



}
