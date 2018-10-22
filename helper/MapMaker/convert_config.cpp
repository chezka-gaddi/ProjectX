////////////////////////////////////////////////////////////////////////////////
// Description: Converts a ascii grid of obstacles and empty spaces to 
//              config options for our platform.
////////////////////////////////////////////////////////////////////////////////


// Include(s)
#include <fstream>
#include <iostream>

using namespace std;

int main (int argc, char ** argv)
{
    ifstream ascii;
    ofstream output;
    int width;
    int height;

    string temp;
    char ** map;



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


    for(int y = 0; y < height;y++)
    {
        getline(ascii, temp);
        for(int x = 0; x < temp.size(); x++)
        {
            if (temp[x] == 'O')
                output << "OBSTACLE " << x << " " << y  << endl;
        }
    }


    ascii.close();
    output.close();

    return 0;
    


}
