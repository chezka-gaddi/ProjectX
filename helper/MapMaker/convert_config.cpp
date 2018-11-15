////////////////////////////////////////////////////////////////////////////////
// Description: Converts a ascii grid of obstacles and empty spaces to
//              config options for our platform.
////////////////////////////////////////////////////////////////////////////////


// Include(s)
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct pos
{
    int x;
    int y;

    pos(int new_x, int new_y):x(new_x), y(new_y) {};
};

int main (int argc, char ** argv)
{
    ifstream ascii;
    ofstream output;
    int width;
    int height;

    string temp;
    char ** map;

    vector<pos> Spawns;



    if(argc != 3)
    {
        cout << "Not the right amount of arguments"
             << endl
             << "Command Should Look Like:"
             << endl
             << "./make_config ascii_map config_args"
             << endl;
        exit(1);
    }

    ascii.open(argv[1], ios::in);
    output.open(argv[2]);

    getline(ascii, temp);

    width = atoi(temp.c_str());

    getline(ascii, temp);

    height = atoi(temp.c_str());

    cout << "Map size: "<<width << " " << height << endl;

    output << "WIDTH " << width << endl;
    output << "HEIGHT " << height << endl;


    for(int y = 0; y < height; y++)
    {
        getline(ascii, temp);
        for(int x = 0; x < width; x++)
        {
            if (temp[x] == 'O')
                output << "OBSTACLE " << x << " " << y  << endl;
            else if(temp[x] == 'T')
                Spawns.push_back(pos(x, y));
        }
    }

    output << endl;
    output << "Spawn Points x, y" << endl;

    for(auto position: Spawns)
    {
        output<< position.x << " " << position.y << endl;
    }

    ascii.close();
    output.close();

    return 0;



}
