#include "game.h"
#include "callbacks.h"

/***************************************************************************//**
* @brief Constructor
*
* Here's where you handle things that should happen during a turn
* - Ask each of the tanks for their action
* - Update the game state
* - Issue a call to repaint the playfield, projectiles, tanks, etc.
*
*
*******************************************************************************/
Game::Game() : turn(0) {}


Game::Game(gameMode mode) : turn(0)
{
    g_mode = mode;
}


float Game::convertGLXCoordinate( int x )
{
    cout << "start x: " << x;
    GLfloat x_gl = (x - 10.) / 4.;
    if( x_gl > 0 )
        x_gl -= 0.3;
    else
        x_gl += 0.3;
    cout << "\tend x: " << x_gl << endl;

    return x_gl;
}


float Game::convertGLYCoordinate( int y )
{
    cout << "start y: " << y;
    GLfloat y_gl = (y - 2.5) / 4.;
    if( y_gl > 0 )
        y_gl -= 0.3;
    else
        y_gl += 0.3;
    cout << "\tend y: " << y_gl << endl;

    return y_gl;
}


Game::~Game()
{
    for( auto temp : objects )
        delete temp;

    for( auto temp : obstacles )
        delete temp;

    delete tankGame;
}




static bool isplayable(std::vector<ActorInfo> actorInfo)
{
    int tankCount = 0;
    
    for (auto a : actorInfo)
        tankCount += (a.id > 0) ? 1 : 0;
    
    return (tankCount > 1);
}


void Game::makeDrawables()
{
    Drawable *temp_draw = nullptr;
    
    tankGame->getActors(); 
    vector <ActorInfo> actors = tankGame->getActors();
    
    for( auto act : actors )
    {
        temp_draw = new TankDrawable( act.id, convertGLXCoordinate( act.x ), convertGLYCoordinate( act.y) );
        objects.push_back( temp_draw );
    }
}


/***************************************************************************//**
* @brief executeTurn
*
* Here's where you handle things that should happen during a turn
* - Ask each of the tanks for their action
* - Update the game state
* - Issue a call to repaint the playfield, projectiles, tanks, etc.
*
*******************************************************************************/
void Game::executeTurn()
{
    std::cout << "Game Turn [" << turn << "] executed\n";
    std::cout << "Repainting game objects\n";
    
    if(isplayable(tankGame->getActors()))
    {
        glutPostRedisplay();
        tankGame->nextTurn();
        turn++;
    }
    
    else
        glutLeaveMainLoop();
}


void Game::initGameState()
{
    std::cout << "Game::Loading playfield\n";
    std::cout << "Game::Loading tanks\n";
    std::cout << "Game::Setting turn counter\n";

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
    

    tankGame->addObstacle(6,2);     //add some obstacles to make things more fun
    tankGame->addObstacle(14,2); 
   
    Drawable *temp = nullptr;
    
    for( auto actTemp : startActors)
    {
        temp = new Menu( actTemp.id, actTemp.health, actTemp.shots );
        obstacles.push_back(temp);
    }
    
    temp = new GameFieldDrawable();
    obstacles.push_back(temp);
    
    temp = new Obstacles( convertGLXCoordinate( 6 ), convertGLYCoordinate( 2 ) );
    obstacles.push_back(temp);
    
    temp = new Obstacles( convertGLXCoordinate( 14 ), convertGLYCoordinate( 2 ) );
    obstacles.push_back(temp);
    

    glutPostRedisplay();
}


void Game::closeDown()
{
    std::cout << "Game::Closing game, cleaning up memory\n";
    std::cout << "Game::Writing results file\n";
}
