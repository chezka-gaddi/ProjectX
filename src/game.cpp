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
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f,  1.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.5f, -0.5f,  1.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.5f,  0.5f,  1.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f,  0.5f,  1.0f);
	glEnd();
    glPopMatrix();

    system("sleep 1");
    glutSwapBuffers();
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
*******************************************************************************/
void Game::initGameState()
{
    Drawable *temp = nullptr;
    
    // Load game field
    temp = new GameFieldDrawable();
    constants.push_back(temp);
    std::cout << "Game::Loading tanks\n";
    std::vector<string> AINames = {"SimpleAI", "SimpleAI"};
    std::vector<Actor*> StartActorPointers = dynamicTankLoader(AINames);
    
    std::vector<ActorInfo> startActors;
    startActors.push_back(ActorInfo (StartActorPointers[0], 3, 1, 2, 0, 1));
    startActors.push_back(ActorInfo (StartActorPointers[1], 3, 1, 14, 5, 2));
    

    // Create a stats menu for both tanks
    for( auto actTemp : startActors)
    {
        temp = new Menu( actTemp.id, actTemp.health, actTemp.shots, actTemp.hits );
        objects.push_back(temp);
    }

    tankGame = new GameField(15,9, startActors, displayWrapper);
    
    // Add obstacles to the gamefield
    tankGame->addObstacle(3,0);
    tankGame->addObstacle(13,4); 
    tankGame->addObstacle(7,2); 
    tankGame->addObstacle(4,7); 
    tankGame->addObstacle(10,5); 
    tankGame->addObstacle(14,1); 
    tankGame->addObstacle(2,5); 
   

    temp = new Obstacles( 1, convertGLXCoordinate( 3 ), convertGLYCoordinate( 0 ) );
    constants.push_back(temp);
    temp = new Obstacles( 2, convertGLXCoordinate( 13 ), convertGLYCoordinate( 4 ) );
    constants.push_back(temp);
    temp = new Obstacles( 2, convertGLXCoordinate( 7 ), convertGLYCoordinate( 2 ) );
    constants.push_back(temp);
    temp = new Obstacles( 1, convertGLXCoordinate( 4 ), convertGLYCoordinate( 7 ) );
    constants.push_back(temp);
    temp = new Obstacles( 1, convertGLXCoordinate( 10 ), convertGLYCoordinate( 5 ) );
    constants.push_back(temp);
    temp = new Obstacles( 1, convertGLXCoordinate( 14 ), convertGLYCoordinate( 1 ) );
    constants.push_back(temp);
    temp = new Obstacles( 1, convertGLXCoordinate( 2 ), convertGLYCoordinate( 5 ) );
    constants.push_back(temp);
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
