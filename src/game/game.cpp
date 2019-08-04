/***************************************************************************//**
 * @file game.cpp
 * @author Chezka Gaddi
 * @brief Contains all functions that maintains Game class.
 *******************************************************************************/

#include <game/game.h>
#include <ui/callbacks.h>
#include <iostream>
#include <GL/glut.h>
#include <utilities/tankLoader.h>
#include <utilities/mapLoader.h>
#include <game/gameover.h>
#include <game/configParser.h>
#include <fstream>



/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief Constructor
 *
 * Default constructor, sets turn = 0
 *******************************************************************************/
Game::Game(){}


/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief Destructor
 *
 * Frees up the memory allocated to the drawables and the GameField.
 *******************************************************************************/
Game::~Game()
{
  objects.clear();
  constants.clear();
  bushes.clear();
  rocks.clear();
  trees.clear();
  waters.clear();
  specials.clear();
  sfx.clear();
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
float Game::convertGLXCoordinate(int x)
{
  //float fscaler = (x - 1) * (4.0717* pow(tankGame->getWidth(), -1.031));
  //GLfloat x_gl = -1.75 + (fscaler);
  //return x_gl;

  float tempx = 3.70 * ((x - 0.5) / tankGame->getWidth()) - 1.85;
  return tempx; 
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
float Game::convertGLYCoordinate(int y)
{
  //float fscaler =  (y - 1) * (3.195 * pow(tankGame->getHeight(), -1.08));
  //GLfloat y_gl = 0.75 - (fscaler);
  //return y_gl;

  float tempy = -3.0 * ((y - 0.5) / tankGame->getHeight()) + 1.22;
  return tempy;
  
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
static bool isplayable(const std::vector<ActorInfo> &actorInfo)
{
  int tankCount = 0;

  for(auto a : actorInfo)
    tankCount += (a.id > 0 && a.health) ? 1 : 0;
  return (tankCount > 1);
}

 /**************************************************************************//**
 * @author Jonathan McKee
 * @brief checkMaxTurn
 *
 * Check to see if we have hit the max number of turns.  If we have then kill off
 * all tanks and let the game end on next turn loop.
 *******************************************************************************/
bool Game::checkMaxTurn()
{
  if (tankGame->getGameTurn() != settings->getMaxTurns())
    return false;

  //printf("Finding Early Winner.\n");
    std::vector<ActorInfo> *actors = tankGame->getActorsPointer();
    int actorId=0;
    int currMaxHealth=0;
    bool tie = false;
    for(auto a : *actors)   //clear out non tanks
    {
      if(a.id < 0)
      {
        //printf("Clearing out projectile.\n");
        a.health = 0;
      }
    }
    tankGame->cull();  //remove the old tanks
    for(auto a : *actors)
    {
      if(a.health > currMaxHealth)
      {
        actorId = a.id;
        tie = false;
        currMaxHealth=a.health;
        //printf("Found a max: %d \n", actorId);
      }
      else if(a.health == currMaxHealth)
      {
        //printf("Found a duplicate.\n");
        tie = true;
      }
    }
    if(tie == true)   //If it is a tie clear out all tanks to get to draw screen
    {
      for(auto &a : *actors)
      {
        a.health = 0;
      }
    }
    else if(tie == false)    //No tie, kill off all tanks
    {
      for(auto &a : *actors)
      {
        if(a.id != actorId)//prevent killing off the winner
        {
          a.health = 0;
        }
      }
    }
    return true;
}


 /**************************************************************************//**
 * @author Jon McKee
 * @brief executeGame
 *
 * While the game is still playable, execute a turn from each of the tanks,
 * otherwise return back to main and destroy the GUI.  This function allows the
 * game to run independent of the GUI.
 *
 *******************************************************************************/
void Game::executeGame()
{
  //printf("Current Turns:  %d of %d\n",tankGame->getTurnCount(), max_turns);
  while (isplayable(tankGame->getActorsConst())) //If we still have tanks keep playing
  {
    tankGame->nextTurn();
    if(checkMaxTurn())
    {
      tankGame->cull();
    }
  }
  gameOver(tankGame->getDeceased(), tankGame->getActors(), settings, tankGame->gameTurn);
}

/**************************************************************************//**
 * @author Chezka Gaddi
 * @modified Jon McKee
 * @brief executeTurn
 *
 * Execute a game turn from each of the tanks if the game is playable, 
 * otherwise return back to main and destroy the GUI.
 *
 *******************************************************************************/
void Game::executeTurn()
{
  //printf("Current Turns:  %d of %d\n",tankGame->getTurnCount(), max_turns);
  if (isplayable(tankGame->getActorsConst())) //If we still have tanks keep playing
  {
    tankGame->nextTurn();
    if(checkMaxTurn())
    {
      tankGame->cull();
    }
  }else{
    gameOver(tankGame->getDeceased(), tankGame->getActors(), settings, tankGame->gameTurn);
    glutLeaveMainLoop();
  }
}

/**
 * @author David Donahue
 * @modified Jon McKee
 * @par Description:
 * Wrapper to display() that acts as the GameField display callback
 */
void displayWrapper(std::shared_ptr<Settings> settings)
{
    if (settings->showUI())
      display();
}



/***************************************************************************//**
 * @author Chezka Gaddi
 * @modified Jon McKee
 * @brief initGameState
 *
 * Initialize the main GameField and all the Drawables needed to start the game.
 * Reads settings from the file "config.txt"
 *******************************************************************************/
float Drawable::xscalar = 1.0;
float Drawable::yscalar = 1.0;
float Drawable::scalar = 1.0;
int TimerEvent::idle_speed = 750;
void Game::initGameState(std::shared_ptr<Settings> & setting)
{
  settings = setting;
  bool quiet = settings->checkQuiet();

  std::string configLine, tType, name, imgPath;
  int x, y, hPad = 0, wPad=0;
  //Player Count
  int pCount = 1;
  std::vector<ActorInfo> startActors;
  //Location vectors
  std::vector<std::pair<int,int>> tankLocations;

  //Image vectors for custom images
  std::vector<std::string> tankImages, gameImages, treeImages, rockImages, bushImages,
      waterImages, tImages, AINames;

  std::ofstream fout;
  std::shared_ptr<MapData> mapLoader = nullptr;

  //Seed random for random obstacle selection
  srand(time(0));

  //Load game field drawable object
  constants.push_back(std::unique_ptr<Drawable>(new GameFieldDrawable));

  if (!quiet)
    printf("Loading configuration from file ");
  mapLoader = parseConfig(setting); //INI Config reader
  //mapLoader->printTileMap(); //Test map loaded correctly 

  //Load images from config.ini
  if (settings->showUI()){
    gameImages = parseList(settings, "IMAGES", "fieldimage");
    bushImages = parseList(settings, "IMAGES", "bush");
    treeImages = parseList(settings, "IMAGES", "tree");
    rockImages = parseList(settings, "IMAGES", "rock");
    waterImages = parseList(settings, "IMAGES", "water");
    tImages = parseList(settings, "IMAGES", "obstacle");
    gameImages.insert(std::end(gameImages), std::begin(tImages), std::end(tImages));
  }

  //Get Player Count and Player Names
  name = parseAI(settings, "AI1", "name");
  while(name != ""){
    AINames.push_back(name);
    pCount++;
    name = parseAI(settings, "AI" + std::to_string(pCount), "name");
  }
  pCount--;
  
  //Process remaining parts of AI (X, Y, Images)
  for (int i = 1; i <= pCount; i++){
    x = std::stoi(parseAI(settings, "AI" + std::to_string(i), "x"));
    y = std::stoi(parseAI(settings, "AI" + std::to_string(i), "y"));
    tankLocations.push_back(std::pair<int,int>(x+wPad,y+hPad));

    name = parseAI(settings, "AI" + std::to_string(i), "images");
    if (name == ""){
      imgPath = "images/tanks/Default";
      tankImages.push_back(imgPath + "/base.png");
      tankImages.push_back(imgPath + "/turret.png");
      tankImages.push_back(imgPath + "/bullet.png");
    }else{
      tankImages.push_back(name + "/base.png");
      tankImages.push_back(name + "/turret.png");
      tankImages.push_back(name + "/bullet.png");
    }
  }

  if (!quiet){

  }
  //Check player locations
  for(unsigned int x=0; x < tankLocations.size(); x++)
  {
    for(unsigned int y = x + 1; y < tankLocations.size(); y++)
    {
      if(tankLocations.at(x) == tankLocations.at(y))
      {
        printf("WARNING: Tanks set to spawn on the same tile (%d, %d).\n", tankLocations[x].first, tankLocations[y].second);
        continue;
      }
    }
  }

  //Try and create output file
  fout.open(settings->getResultsFile(), std::ios::out | std::ios::in | std::ios::app);
  //Warn if we cannot save settings, ignore quiet for this error
  if(!fout)
  {
    //Warning because game will still play
    printf("WARNING: Unable to open results file (%s).  Game will play but results will not be saved.\n", settings->getResultsFile().c_str());
  }
  
  //This should not be possible
  if (mapLoader == nullptr){
    printf("ERROR: No map file was loaded.\n");
    exit(1);
  }

  //set globals
  TimerEvent::idle_speed = settings->getIdleSpeed();
  Drawable::xscalar = 1.85/mapLoader->width; //The available width area (3.7) divided by 2 divided by map width
  Drawable::scalar = Drawable::xscalar;
  Drawable::yscalar = 1.50/mapLoader->height; //The available height area (3.0) divided by 2 divided by map height
  
  //Only load textures if we're showing UI
  if (settings->showUI()){
    if (!quiet)
      printf("Loading textures...\n");
    glEnable(GL_TEXTURE_2D);
    if(!LoadGLTextures(tankImages, gameImages, treeImages, rockImages, bushImages, waterImages, quiet) && !quiet)
        printf("WARNING: Failed to open image(s).  Game will still play but will have broken textures.\n");
    glDisable(GL_TEXTURE_2D);
  }

  //Load the tank players from shared objects
  if (!quiet)
    printf("Loading Shared Objects (Tanks)...\n");
  std::vector<Actor*> startActorPointers = dynamicTankLoader(AINames);
    
  if (!quiet)
    printf("Loading players...\n");
  startActors = loadPlayers(quiet, tankLocations, AINames, startActorPointers, settings->getAttributes(), mapLoader->height, mapLoader->width);
  //printf("Height: %d  Width: %d\n",height, width);
  tankGame = std::unique_ptr<GameField>(new GameField(mapLoader->width, mapLoader->height, startActors, displayWrapper, this, settings));
  tankGame->setMap(mapLoader);
  tankGame->setSPECIAL(settings->getAttributes());
  
  if (!quiet){
    printf("   ...Done\n");
    printf("Clearing spawn points...\n");
  }
  // Add tanks to the gamefield map
  for(auto tank : startActors)
  {
    if (mapLoader->tileMap[tank.y][tank.x].type == "Rock"
      || mapLoader->tileMap[tank.y][tank.x].type == "Water"
      || mapLoader->tileMap[tank.y][tank.x].type == "Hedgehog")
    {
      if (!quiet)
        printf("WARNING: removing object at (%d,%d) for tank spawn.\n",tank.x, tank.y);
      mapLoader->tileMap[tank.y][tank.x].type = "Empty";
      mapLoader->tileMap[tank.y][tank.x].health = 0;
    }
  }
  //Create one-time usable drawable objects
  for (int i = 1; i <= mapLoader->height; i++){
    for (int j=1; j <= mapLoader->width; j++){
      tType = mapLoader->tileMap[i][j].type;
      if(tType == "Rock"){
          rocks.push_back(std::unique_ptr<Obstacles>(new Obstacles(1, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i)));
      }else if (tType == "Water"){
          constants.push_back(std::unique_ptr<Drawable>(new Obstacles(3, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i)));
      }else if (tType == "Bush"){
          bushes.push_back(std::unique_ptr<Obstacles>(new Obstacles(2, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i)));
      }else if (tType == "Tree"){
          trees.push_back(std::unique_ptr<Obstacles>(new Obstacles(0, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i)));
      }else if (tType == "Crate"){
          specials.push_back(std::unique_ptr<Drawable>(new Crate(convertGLXCoordinate(j), convertGLYCoordinate(i), j, i)));
      }else if (tType == "Hedgehog"){
          constants.push_back(std::unique_ptr<Drawable>(new Obstacles(50, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i)));
      }
    }
  }

  if (!quiet)
    printf("...done.\n");
  if (settings->checkCoverage()){
    printf("Turning on coverage mode.");
    settings->setIdleSpeed(1);
    settings->setAniFrames(1);
    settings->setTankSpeed(1);
    settings->setBulletSpeed(1);
  }
}

/***************************************************************************//**
 * @author Chezka Gaddi
 * @modified Jon McKee
 * @brief initTournState
 *
 * Initialize the main GameField and all the Drawables needed to start the game.
 * Reads settings from the file "config.txt"
 *******************************************************************************/
void Game::initTournState(std::shared_ptr<Settings> & setting, std::shared_ptr<MapData> map, std::vector<std::string> AINames, 
    std::vector<std::pair<int, int>> tankLocations, std::vector<std::string> tankImages)
{
  settings = setting;
  bool quiet = settings->checkQuiet();
  std::string configLine, tType, name, imgPath;
  std::vector<ActorInfo> startActors;

  //Image vectors for custom images
  std::vector<std::string> gameImages = {"images/green.png"}; 
  std::vector<std::string> treeImages = {"images/tree/treea.png", "images/tree/treeb.png", "images/tree/treec.png"}; 
  std::vector<std::string> rockImages = {"images/rock/rocka.png", "images/rock/rockb.png"}; 
  std::vector<std::string> bushImages = {"images/bush/busha.png", "images/bush/bushb.png","images/bush/bushc.png"};
  std::vector<std::string> waterImages = {"images/water/waterTex.png"};
  std::vector<std::string> tImages; 

  std::ofstream fout;

  //Seed random for random obstacle selection
  srand(time(0));

  //Empty the arrays
  rocks.clear();
  bushes.clear();
  trees.clear();
  specials.clear();
  constants.clear();

  //Load game field drawable object
  constants.push_back(std::unique_ptr<Drawable>(new GameFieldDrawable));

  //Check player locations
  for(unsigned int x=0; x < tankLocations.size(); x++)
  {
    for(unsigned int y = x + 1; y < tankLocations.size(); y++)
    {
      if(tankLocations.at(x) == tankLocations.at(y))
      {
        printf("WARNING: Tanks set to spawn on the same tile (%d, %d).\n", tankLocations[x].first, tankLocations[y].second);
        continue;
      }
    }
  }

  //Try and create output file
  fout.open(settings->getResultsFile(), std::ios::out | std::ios::in | std::ios::app);
  //Warn if we cannot save settings, ignore quiet for this error
  if(!fout)
  {
    //Warning because game will still play
    printf("WARNING: Unable to open results file (%s).  Game will play but results will not be saved.\n", settings->getResultsFile().c_str());
  }
  
  //This should not be possible
  if (map == nullptr){
    printf("ERROR: No map file was loaded.\n");
    exit(1);
  }

  //set globals
  TimerEvent::idle_speed = settings->getIdleSpeed();
  Drawable::xscalar = 1.85/map->width; //The available width area (3.7) divided by 2 divided by map width
  Drawable::scalar = Drawable::xscalar;
  Drawable::yscalar = 1.50/map->height; //The available height area (3.0) divided by 2 divided by map height
  
  //Only load textures if we're showing UI
  /*if (settings->showUI()){
    if (!quiet)
      printf("Loading textures...\n");
    glEnable(GL_TEXTURE_2D);
    if(!LoadGLTextures(tankImages, gameImages, treeImages, rockImages, bushImages, waterImages, quiet) && !quiet)
        printf("WARNING: Failed to open image(s).  Game will still play but will have broken textures.\n");
    glDisable(GL_TEXTURE_2D);
  }*/

  //Load the tank players from shared objects
  std::vector<Actor*> startActorPointers = dynamicTankLoader(AINames);
    
  startActors = loadPlayers(quiet, tankLocations, AINames, startActorPointers, settings->getAttributes(), map->height, map->width);
  tankGame = std::unique_ptr<GameField>(new GameField(map->width, map->height, startActors, displayWrapper, this, settings));
  tankGame->setMap(map);
  tankGame->setSPECIAL(settings->getAttributes());

  // Add tanks to the gamefield map
  for(auto tank : startActors)
  {
    if (map->tileMap[tank.y][tank.x].type == "Rock"
      || map->tileMap[tank.y][tank.x].type == "Water"
      || map->tileMap[tank.y][tank.x].type == "Hedgehog")
    {
      if (!quiet)
        printf("WARNING: removing object at (%d,%d) for tank spawn.\n",tank.x, tank.y);
      map->tileMap[tank.y][tank.x].type = "Empty";
      map->tileMap[tank.y][tank.x].health = 0;
    }
  }
  //Create one-time usable drawable objects
  for (int i = 1; i <= map->height; i++){
    for (int j=1; j <= map->width; j++){
      tType = map->tileMap[i][j].type;
      if(tType == "Rock"){
          rocks.push_back(std::unique_ptr<Obstacles>(new Obstacles(1, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i)));
      }else if (tType == "Water"){
          constants.push_back(std::unique_ptr<Drawable>(new Obstacles(3, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i)));
      }else if (tType == "Bush"){
          bushes.push_back(std::unique_ptr<Obstacles>(new Obstacles(2, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i)));
      }else if (tType == "Tree"){
          trees.push_back(std::unique_ptr<Obstacles>(new Obstacles(0, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i)));
      }else if (tType == "Crate"){
          specials.push_back(std::unique_ptr<Drawable>(new Crate(convertGLXCoordinate(j), convertGLYCoordinate(i), j, i)));
      }else if (tType == "Hedgehog"){
          constants.push_back(std::unique_ptr<Drawable>(new Obstacles(50, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i)));
      }
    }
  }
}

/***************************************************************************//**
 * @author Jon McKee
 * @brief loadPlayers
 *
 * Dynamically loads the playersS
 *******************************************************************************/
std::vector<ActorInfo> Game::loadPlayers(bool quiet, std::vector<std::pair<int,int>> tankLocations, std::vector<std::string> AINames, std::vector<Actor*> startActorPointers, attributes baseAttr, int height, int width){
 std::vector<ActorInfo> actors;
 if (!quiet)
    printf("Creating Player Tanks...\n");
  for(unsigned int i = 0; i < startActorPointers.size(); ++i)
  {
    if ( tankLocations[i].first <= width &&
         tankLocations[i].first >= 1 &&
         tankLocations[i].second <= height &&
         tankLocations[i].second >= 1){
         actors.push_back(ActorInfo(startActorPointers[i]
                                    , AINames[i]
                                    , i + 1
                                    , tankLocations[i].first
                                    , tankLocations[i].second
                                    , baseAttr.tankHealth
                                    , baseAttr.tankHealth
                                    , baseAttr.tankDamage
                                    , baseAttr.tankAP
                                    , baseAttr.tankRadar
                                    , baseAttr.projRange
                                    , baseAttr.tankAmmo
                                    , baseAttr.tankAmmo
                                    ));
    //printf("Actor %d name: %s\n", i, AINames[i].c_str());
    }else{
      printf("WARNING: Invalid location for %s (%d, %d)\n", AINames[i].c_str(), tankLocations[i].first, tankLocations[i].second);
      tankLocations.erase(tankLocations.begin() + i);
      --i;
    }
  }
  return actors;
}

/***************************************************************************//**
 * @brief closeDown
 *
 * Prints out debugging info.
 *******************************************************************************/
void Game::closeDown()
{
  printf("Game::Closing game, cleaning up memory\n");
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