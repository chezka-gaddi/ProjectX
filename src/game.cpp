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
    GLfloat x_gl = (x - 10.) / 4.;
    if( x_gl > 0 )
        x_gl -= 0.3;
    else
        x_gl += 0.3;

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
    GLfloat y_gl = (y - 2.5) / 4.;
    if( y_gl > 0 )
        y_gl -= 0.3;
    else
        y_gl += 0.3;

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
* @brief executeTurn
*
* While the game is still playable, execute a turn from each of the tanks,
* otherwise return back to main and destroy the GUI.
*
*******************************************************************************/
void Game::executeTurn()
{
    std::cout << "Game Turn [" << turn << "] executed\n";
    std::cout << "Repainting game objects\n";
    
    if(isplayable(tankGame->getActors()))
    {
        //glutPostRedisplay();
        tankGame->nextTurn();
        turn++;
    }
    
    else
        glutLeaveMainLoop();
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
    
    std::cout << "Game::Loading playfield\n";
    temp = new GameFieldDrawable();
    constants.push_back(temp);
   

    std::cout << "Game::Loading tanks\n";

    //change tankactor here to what ever we have decided to call the ascii tank actor
    Actor *player1;
    Actor *player2;
    
    switch (g_mode)
    {
        case ai:
            player1 = new SimpleAI;
            player2 = new SimpleAI;
            break;
        
        case sp:
            player1 = new AsciiTankActor;
            player2 = new SimpleAI;
            break;
        
        case mp:
            player1 = new AsciiTankActor;
            player2 = new AsciiTankActor;
            break;
        
        default:
            break;
    }
    
    //tank actor pointers are made and then packaged into ActorInfo structs
    ActorInfo player1Info = ActorInfo(player1, 1,1,2,2,1);
    ActorInfo player2Info = ActorInfo(player2, 1,1,16,2,2);
    
    std::vector<ActorInfo> startActors;
    startActors.push_back(player1Info);
    startActors.push_back(player2Info);
    

    tankGame = new GameField(18,5, startActors, display);
    

    // Add obstacles to the gamefield
    tankGame->addObstacle(6,2);
    tankGame->addObstacle(14,2); 
    temp = new Obstacles( convertGLXCoordinate( 6 ), convertGLYCoordinate( 2 ) );
    constants.push_back(temp);
    
    temp = new Obstacles( convertGLXCoordinate( 14 ), convertGLYCoordinate( 2 ) );
    constants.push_back(temp);
   
    
    // Create a stats menu for both tanks
    for( auto actTemp : startActors)
    {
        temp = new Menu( actTemp.id, actTemp.health, actTemp.shots );
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
