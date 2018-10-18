/***************************************************************************//**
* @file game.cpp
* @author Chezka Gaddi
* @brief Contains all functions that maintains Game class.
*******************************************************************************/

#include "game.h"
#include "callbacks.h"

/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Default constructor, sets turn = 0
*******************************************************************************/
Game::Game() : turn(0) {}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief Constructor
*
* Constructor that sets the game mode, sets turn = 0
*
* @param[in] mode - type of game to be played
*******************************************************************************/
Game::Game(gameMode mode) : turn(0)
{
    g_mode = mode;
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief Destructor
*
* Frees up the memory allocated to the drawables and the GameField.
*******************************************************************************/
Game::~Game()
{
    for( auto temp : objects )
        delete temp;

    delete tankGame;
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief convertGLXCoordinate
*
* Converts the coordinates to GLfloat to be displayed correctly on the screen.
*
* @param[in] x - integer to be converted
* @return x_gl - GLfloat conversion of x
*******************************************************************************/
float Game::convertGLXCoordinate( int x )
{
    GLfloat x_gl = -1.77 + (x * 0.25);
    return x_gl;
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief convertGLYCoordinate
*
* Converts the coordinates to GLfloat to be displayed correctly on the screen.
*
* @param[in] y - integer to be converted
* @return y_gl - GLfloat conversion of y
*******************************************************************************/
float Game::convertGLYCoordinate( int y )
{
    GLfloat y_gl = 0.75 - ( y * 0.3 );
    return y_gl;
}


/***************************************************************************//**
* @author Jacob Lee
* @brief isplayable
*
* Determines the end of the game by the count of the tanks on the field.
*
* @param[in] actorInfo - list of all the active actors
* @return boolean of whether or not more than one tank is still active
*******************************************************************************/
static bool isplayable(std::vector<ActorInfo> actorInfo)
{
    int tankCount = 0;

    for (auto a : actorInfo)
        tankCount += (a.id > 0) ? 1 : 0;

    return (tankCount > 1);
}



/***************************************************************************//**
* @author Chezka Gaddi
* @brief gameOver
*
* Display the screen that reads game over
*******************************************************************************/
void gameOver()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -5.0f);
    glBindTexture(GL_TEXTURE_2D, gameTex[7]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f,  1.0f);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f( 0.5f, -0.5f,  1.0f);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f( 0.5f,  0.5f,  1.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-0.5f,  0.5f,  1.0f);
    glEnd();
    glPopMatrix();

    system("sleep 1.");
    glutSwapBuffers();
    system("sleep 1.");
}


/***************************************************************************//**
* @author Chezka Gaddi
* @brief executeTurn
*
* While the game is still playable, execute a turn from each of the tanks,
* otherwise return back to main and destroy the GUI.
*
*******************************************************************************/
void Game::executeTurn()
{
    if(isplayable(tankGame->getActors()))
    {
        tankGame->nextTurn();
        turn++;
    }

    else
    {
        gameOver();
        glutLeaveMainLoop();
    }
}
/**
 * @author David Donahue
 * @par Description:
 * Wrapper to display() that acts as the GameField display callback
 */

void displayWrapper(MapData map, std::vector<ActorInfo> actors, int turnCount)
{
    display();
}



/***************************************************************************//**
* @author Chezka Gaddi
* @brief initGameState
*
* Initialize the main GameField and all the Drawables needed to start the game.
* Reads settings from the file "config.txt"
*******************************************************************************/
void Game::initGameState()
{
    Drawable *temp = nullptr;

    // Load game field
    temp = new GameFieldDrawable();
    constants.push_back(temp);
    std::vector<string> AINames;
    std::cout << "Game::Loading config.txt\n";
    ifstream fin("config.txt");
    std::string configLine;
    int width = 20;
    int  height = 10;
    int damage = 1;
    int  health = 3;
    int range = 1;
    std::vector<std::pair<int,int>> obstacleLocations;
    std::vector<std::pair<int,int>> tankLocations;

    std::vector<std::string> tankImages;
    std::vector<std::string> gameImages;
    std::string name;

    if (!fin)
        cout << "FAILED TO LOAD CONFIG\n";
    
    while (!fin.eof())
    {
        getline(fin, configLine);
        if (configLine[0] != '#') //ignore comment lines
        {
            int i = configLine.find(' '); //index of first space
            std::string id = configLine.substr(0, i); //separate the identefier from the argumets
            std::string args = configLine.substr(i+1);

            //AI settings
            if (id == "AI") //AI to load
            {
                int x, y;
                i = args.find(' ');
                AINames.push_back(args.substr(0, i));
                std::stringstream(args.substr(i+1)) >> x >> y;
                tankLocations.push_back(std::pair<int,int>(x,y));
                
                i = args.find(' ', i+1);    //skip x
                i = args.find(' ', i+1);    //skip y
                
                args = args.substr(i+1);
                
                for( int x = 0; x < 9; x++ )
                {
                    i = args.find(' ');    //skip y
                    name = args.substr(0,i);
                    tankImages.push_back(name);
                    args = args.substr(i+1);
                }
            }
            
            //field params
            else if (id == "WIDTH")
            {
                stringstream(args) >> width;
            }
            else if (id == "HEIGHT")
            {
                stringstream(args) >> height;
            }
            else if (id == "FIELDIMAGE")
            {
                stringstream(args) >> name;
                gameImages.push_back(name);
            }
            else if (id == "OBSTACLE")
            {
                int x,y;
                stringstream(args) >> x >> y;
                obstacleLocations.push_back(std::pair<int,int> (x, y));
            }
            else if( id == "OBSTACLE_IMAGE" )
            {
                bool done = false;
                while (!done)
                {
                    if (args.find(' ') == string::npos)
                    {
                        done = true;
                        gameImages.push_back(args);
                    }
                    else
                    {
                        i = args.find(' ');
                        gameImages.push_back(args.substr(0, i));
                        args = args.substr(i + 1);
                    }

                }
            }
            //Tank params
            else if (id == "DAMAGE")
            {
                stringstream(args) >> damage;
            }
            else if (id == "HEALTH")
            {
                stringstream(args) >> health;
            }
            else if (id == "RANGE")
            {
                stringstream(args) >> range;
            }
            else if (id != "")
            {
                std::cout << "BAD ARGUMENT: " << id << '\n';
            }

        }
    }

    glEnable(GL_TEXTURE_2D);
    if(!LoadGLTextures(tankImages, gameImages))
        cout << "OH HELL NO!!!!"<< endl;
    glDisable(GL_TEXTURE_2D);
    
    std::vector<Actor*> startActorPointers = dynamicTankLoader(AINames);

    std::vector<ActorInfo> startActors;


    for (int i = 0; i < startActorPointers.size(); ++i)
    {
        startActors.push_back(ActorInfo(startActorPointers[i], health, damage, tankLocations[i].first,
                                        tankLocations[i].second, i + 1,range));
    }
    // Create a stats menu for both tanks
    for( auto actTemp : startActors)
    {
        temp = new Menu( actTemp.id, actTemp.health, actTemp.shots, actTemp.hits );
        objects.push_back(temp);
    }

    tankGame = new GameField(width, height, startActors, displayWrapper);

    // Add obstacles to the gamefield
    for (auto o : obstacleLocations)
    {
        tankGame->addObstacle(o.first, o.second);
        temp = new Obstacles( 1, convertGLXCoordinate( o.first ), convertGLYCoordinate( o.second ) );
        constants.push_back(temp);
    }
}


/***************************************************************************//**
* @brief closeDown
*
* Prints out debugging info.
*******************************************************************************/
void Game::closeDown()
{
    std::cout << "Game::Closing game, cleaning up memory\n";
}

/***************************************************************************//**
* @brief earlyOut
*
* Allows exiting the game during playback with the ESC, Q, or q input
*******************************************************************************/
void Game::earlyOut()
{
    glutLeaveMainLoop();
}
