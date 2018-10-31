/***************************************************************************//**
* @file game.cpp
* @author Chezka Gaddi
* @brief Contains all functions that maintains Game class.
*******************************************************************************/

#include "game.h"
#include "callbacks.h"
#include "event.h"
#include <ctime>

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
    float fscaler;
    if (fieldx < 19){
      fscaler = x * ((-.013 * fieldx) + .445);
    }else if (fieldx >= 20 && fieldx <= 25){
      fscaler = x * ((-0.0075 * fieldx) + 0.335);
    }else if (fieldx > 25){
      fscaler = x * ((-0.005050 * fieldx) + .273750);
    }
    //float fscalar = x * .25    //15
    //float fscalar = x * .1850; //20
    //float fscalar = x * .1475;   //25
    //float fscalar = x * .12225;      //30
    GLfloat x_gl = -1.75 + (fscaler);
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
    //float fscalar = y * 2.7/(fieldy);
    //float fscalar = y * .3; //9
    //float fscalar = y * .215; //12
    //float fscalar = y * .170; //15
    //float fscalar = .142; //18
    float fscaler;
    if (fieldy <= 12){
            fscaler = (y * ((-.028333 * fieldy) + .555));
    }else if (fieldy <= 15 && fieldy > 12){
            fscaler = (y * ((-.015 * fieldy) + .395));
    }else if (fieldy > 16){
            fscaler = (y * ((-.00933 * fieldy) + .31));
    }
    GLfloat y_gl = 0.75 - (fscaler);
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
float Drawable::scalar = 1.0;
int TimerEvent::idle_speed = 750;
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
    int ai_speed = 1000;
    int width = 15;
    int  height = 9;
    int damage = 1;
    int  health = 3;
    int range = 1;
    int radar = 2;
    std::vector<std::pair<int,int>> obstacleLocations;
    std::vector<std::pair<int,int>> treeLocations;
    std::vector<std::pair<int,int>> rockLocations;
    std::vector<std::pair<int,int>> bushLocations;
    std::vector<std::pair<int,int>> tankLocations;

    std::vector<std::string> tankImages;
    std::vector<std::string> gameImages;
    std::vector<std::string> treeImages;
    std::vector<std::string> rockImages;
    std::vector<std::string> bushImages;
    std::string name;
    int attributePoints = 0;
    srand(time(0));

    if (!fin){
        cout << "FAILED TO LOAD CONFIG\n";
        exit(1);
    }
    
    while (!fin.eof())
    {
        getline(fin, configLine);
        if (configLine[0] != '#') //ignore comment lines
        {
            if (configLine == "MAP")
            {
               for ( int y = 0; y < height; y++)
               {
                    getline(fin, configLine);
                    cout << configLine << endl;

                    for(int x = 0; x < width; x++)
                    {   
                        if (configLine[x] == 'O' 
                         || configLine[x] == 'B' 
                         || configLine[x] == 'T')
                            obstacleLocations.push_back(std::pair<int, int> (x, y));
                    }

                }

            
            }
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
                
                for( int x = 0; x < 5; x++ )
                {
                    i = args.find(' ');    //skip y
                    name = args.substr(0,i);
                    tankImages.push_back(name);
                    args = args.substr(i+1);
                }
            }
            else if (id == "AI_SPEED")
            {
                stringstream(args) >> ai_speed;
                if (ai_speed > 1000)
                {
                        cout << "Speeds above 1000 are extremely slow, defaulting at 1000\n";
                        ai_speed = 1000;
                }
                TimerEvent::idle_speed = ai_speed;
                idle_speed = ai_speed;
            } 
            //field params
            else if (id == "WIDTH")
            {
                stringstream(args) >> width;
                if (width < 15) { 
                    width = 15;
                    cout << "Invalid width parameter, defaulting to 15.\n";
                } else if (width > 40) {
                        width = 40;
                        cout << "Invalid width parameter, defaulting to 40.\n";
                }
                fieldx = width;
                Drawable::scalar = (3.75/width)/.25;
            }
            else if (id == "HEIGHT")
            {
                stringstream(args) >> height;
                if (height < 9){
                    height = 9;
                    cout << "Invalid height parameter, defaulting to 9.\n";
                } else if (height > 20) {
                        height = 20;
                        cout << "Invalid height parameter, defaulting to 30.\n";
                }
                fieldy = height;
            }
            else if (id == "FIELDIMAGE")
            {
                stringstream(args) >> name;
                gameImages.push_back(name);
            }
            else if (id == "OBSTACLE" || id == "TREE" || id == "ROCK" || id == "BUSH")
            {
                int x,y;
                bool taken;
                stringstream(args) >> x >> y;
                if (x > width - 1 || x < 0 || y > height - 1 || y < 0)
                {
                    printf ("Invalid obstacle location: (%d, %d). Ranges: (0-%d, 0-%d)\n", x, y, width-1, height-1);
                }else {
                  for (int i = 0; i < tankLocations.size(); i ++){
                          if (tankLocations[i].first == x && tankLocations[i].second == y){
                                  taken = true;
                                  printf ("Invalid obstacle location: (%d, %d) aleady taken by tank\n", x, y);
                          }
                  }
                  if (!taken)
                  {
                          for (int i = 0; i < obstacleLocations.size(); i ++){
                              if (obstacleLocations[i].first == x && obstacleLocations[i].second == y){
                                taken = true;
                                printf ("Invalid obstacle location: (%d, %d) aleady taken by object\n", x, y);
                              }
                          }
                  }
                  if (!taken && id == "TREE"){
                          treeLocations.push_back(std::pair<int,int> (x, y));
                  } else if (!taken && id == "ROCK"){
                          rockLocations.push_back(std::pair<int,int> (x, y));
                  } else if (!taken && id == "BUSH"){
                          bushLocations.push_back(std::pair<int,int> (x, y));
                  } else {
                          obstacleLocations.push_back(std::pair<int,int> (x, y));
                  }
                  taken = false;
                }
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
            else if( id == "TREE_IMAGE" )
            {
                bool done = false;
                while (!done)
                {
                    if (args.find(' ') == string::npos)
                    {
                        done = true;
                        treeImages.push_back(args);
                    }
                    else
                    {
                        i = args.find(' ');
                        treeImages.push_back(args.substr(0, i));
                        args = args.substr(i + 1);
                    }

                }
            }
            else if( id == "ROCK_IMAGE" )
            {
                bool done = false;
                while (!done)
                {
                    if (args.find(' ') == string::npos)
                    {
                        done = true;
                        rockImages.push_back(args);
                    }
                    else
                    {
                        i = args.find(' ');
                        rockImages.push_back(args.substr(0, i));
                        args = args.substr(i + 1);
                    }

                }
            }
            else if( id == "BUSH_IMAGE" )
            {
                bool done = false;
                while (!done)
                {
                    if (args.find(' ') == string::npos)
                    {
                        done = true;
                        bushImages.push_back(args);
                    }
                    else
                    {
                        i = args.find(' ');
                        bushImages.push_back(args.substr(0, i));
                        args = args.substr(i + 1);
                    }

                }
            }
            //Tank params
            else if (id == "DAMAGE")
            {
                stringstream(args) >> damage;
                if (damage < 1){ 
                  damage = 1;
                  cout << "Invalid damage value, defaulting to 2\n";
                } else if (damage > 4) {
                    printf("%d damage might be a little excesive, setting to 4", damage);
                    damage = 4;
                }
            }
            else if (id == "HEALTH")
            {
                stringstream(args) >> health;
                if (health < 2){ 
                  health = 2;
                  cout << "Invalid health value, defaulting to 2\n";
                } else if (health > 5) {
                    printf("%d health might be a little excesive, setting to 5", health);
                    health = 5;
                }
            }
            else if (id == "AP")
            {
                stringstream(args) >> range;
                if (range < 2){ 
                  range = 2;
                  cout << "Invalid number of action points value, defaulting to 2\n";
                } else if (range > 5) {
                    printf("%d range might be a little excesive, setting to 5", range);
                    range = 5;
                }
            }
            else if (id == "RADAR")
            {
                stringstream(args) >> radar;
                if (radar < 2){ 
                  radar = 2;
                  cout << "Invalid radar value, defaulting to 2\n";
                } else if (radar > 10) {
                    printf("%d radar might be a little excesive, setting to 10", radar);
                    radar = 10;
                }
            }
            else if (id == "SPECIAL")
            {
                stringstream(args) >> attributePoints;
                if (attributePoints < 1){ 
                  attributePoints = 1;
                  cout << "Invalid special value, defaulting to 1\n";
                } else if (attributePoints > 4) {
                    printf("%d specials might be a little excesive, setting to 4", attributePoints);
                    attributePoints = 4;
                }
            }
            else if (id != "")
            {
                std::cout << "BAD ARGUMENT: " << id << '\n';
            }

        }
    }

    glEnable(GL_TEXTURE_2D);
    if(!LoadGLTextures(tankImages, gameImages, treeImages, rockImages, bushImages))
        cout << "Failed to open image." << endl;
    glDisable(GL_TEXTURE_2D);
    
    cout << "Loading Shared Objects...";
    std::vector<Actor*> startActorPointers = dynamicTankLoader(AINames);

    std::vector<ActorInfo> startActors;


    for (int i = 0; i < startActorPointers.size(); ++i)
    {
        startActors.push_back(ActorInfo(startActorPointers[i]
                    , health
                    , damage
                    , tankLocations[i].first
                    , tankLocations[i].second
                    , i + 1
                    , range
                    , 0
                    , radar));
    }
    cout << "Done" << endl;
    // Create a stats menu for up to 4 tanks
    for( auto actTemp : startActors)
    {
        temp = new Menu( actTemp.id, actTemp.health, actTemp.shots, actTemp.hits );
        objects.push_back(temp);
    }

    cout << "Initializing Game...";
    tankGame = new GameField(width, height, startActors, displayWrapper, this);
    tankGame->setSPECIAL(attributePoints);
    cout << "Done" << endl;

    // Add obstacles to the gamefield
    cout << "Generating Obstacles...";
    for (auto o : obstacleLocations)
    {
        tankGame->addObstacle(o.first, o.second);
        temp = new Obstacles( (rand() % 3), convertGLXCoordinate( o.first ), convertGLYCoordinate( o.second ), o.first, o.second );
        constants.push_back(temp);
    }
    for (auto t : treeLocations)
    {
        tankGame->addObstacle(t.first, t.second, 'T');
        temp = new Obstacles( 0, convertGLXCoordinate( t.first ), convertGLYCoordinate( t.second ), t.first, t.second );
        trees.push_back(temp);
    }
    for (auto r : rockLocations)
    {
        tankGame->addObstacle(r.first, r.second, 'R'); //No driving over rocks
        temp = new Obstacles( 1, convertGLXCoordinate( r.first ), convertGLYCoordinate( r.second ), r.first, r.second );
        rocks.push_back(temp);
    }
    for (auto b : bushLocations)
    {
        tankGame->addObstacle(b.first, b.second, 'B');
        temp = new Obstacles( 2, convertGLXCoordinate( b.first ), convertGLYCoordinate( b.second ), b.first, b.second );
        bushes.push_back(temp);
    }
    cout << "Done" << endl;
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
