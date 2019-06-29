/***************************************************************************//**
 * @file game.cpp
 * @author Chezka Gaddi
 * @brief Contains all functions that maintains Game class.
 *******************************************************************************/

#include <game/game.h>
#include <ui/callbacks.h>
#include <ui/event.h>
#include <ctime>

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
  //for(auto temp : objects)
    //delete temp;
  objects.clear();
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
float Game::convertGLXCoordinate(int x)
{
  float fscaler;
  fscaler = (x - 1) * (4.0717* pow(fieldx, -1.031));
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
float Game::convertGLYCoordinate(int y)
{
  float fscaler =  (y - 1) * (3.1923* pow(fieldy, -1.08));
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
static bool isplayable(const std::vector<ActorInfo> &actorInfo)
{
  int tankCount = 0;

  for(auto a : actorInfo)
    tankCount += (a.id > 0) ? 1 : 0;
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
        if(a.id != actorId)
        {
          a.health = 0;
        }
      }
    }
    return true;
}


 /**************************************************************************//**
 * @author Chezka Gaddi
 * @modified Jon McKee
 * @brief executeTurn
 *
 * While the game is still playable, execute a turn from each of the tanks,
 * otherwise return back to main and destroy the GUI.
 *
 *******************************************************************************/
void Game::executeTurn()
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
  if (settings->showUI())
    glutLeaveMainLoop();
}

/**
 * @author David Donahue
 * @modified Jon McKee
 * @par Description:
 * Wrapper to display() that acts as the GameField display callback
 */
void displayWrapper(Settings * settings)
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
int TimerEvent::idle_speed = 750;
void Game::initGameState(Settings * setting)
{
  settings = setting;
  bool quiet = settings->checkQuiet();
  if(!quiet)
    std::cout << "Game::Loading config.txt\n";
  ifstream fin("config.txt");

  std::string configLine, tType, name, imgPath;
  Obstacles* tempOb;
  Drawable* tempObj = nullptr;
  bool done;
  //parseConfig(setting); //INI Config reader

  //Game Setting defaults
  unsigned int ai_speed = 750, width = 15, height = 9, maxT = 1000, hPad = 0, wPad = 0;
  //setting defaults
  unsigned int aniSpeed = 20, tank_speed = 400, bullet_speed = 80;
  //Tank Defaults
  unsigned int damage = 1, health = 3, range = 4, radar = 4, ap = 1, ammo = 6;
  //Default Tank Images
  attributes baseStats;

  //Location vectors
  std::vector<std::pair<int,int>> obstacleLocations, treeLocations, rockLocations, bushLocations,
      tankLocations, waterLocations, specialLocations;

  //Image vectors for custom images
  std::vector<std::string> tankImages, gameImages, treeImages, rockImages, bushImages,
      waterImages, AIImages, AINames;

  int attributePoints = 0;
  ofstream fout;
  MapData * mapLoader = nullptr;

  //Seed random for random obstacle selection
  srand(time(0));

  // Load game field
  constants.push_back(new GameFieldDrawable);

  //Check if we had a config file we could read.
  if(!fin)
  {
    createConfig();
  }
  //Try and create output file
  fout.open(settings->getResultsFile(), ios::out | ios::in | ios::app);
  //Warn if we cannot save settings, ignore quiet for this error
  if(!fout)
  {
    printf("WARNING: Unable to open results file (%s).  Game will play but results will not be saved.\n", settings->getResultsFile().c_str());
  }
  while(!fin.eof())
  {
    getline(fin, configLine);
    if(configLine[0] != '#') //Ignore comment lines
    {
      unsigned i = configLine.find(' '); //index of first space
      std::string id = configLine.substr(0, i); //separate the identefier from the argumets
      std::string args = configLine.substr(i+1);
      if (id == "MAPNAME"){
        //MapLoader
        settings->setMapName(args);
        mapLoader = loadMap(settings);
        //mapLoader->printTileMap(); //Test map loaded correctly
        height = mapLoader->height;
        width = mapLoader->width;
      //AI settings
      }else if(id == "AI")  //AI to load
      {
        if(AINames.size() == 0)
          if (!quiet)
            cout << "Waking up the tank commanders...\n";
        if (!quiet)
          cout << "   Checking player " << AINames.size()+1 << "...";
        int x, y;
        i = args.find(' ');
        AINames.push_back(args.substr(0, i));
        std::stringstream(args.substr(i+1)) >> x >> y;
        //printf("\nTank at: Actual: %d, %d Modified: %d, %d.\n",x, y, x+wPad,y+hPad);
        tankLocations.push_back(std::pair<int,int>(x+wPad,y+hPad));
        for(unsigned int x=0; x < tankLocations.size(); x++)
        {
          for(unsigned int y = x + 1; y < tankLocations.size(); y++)
          {
            if(tankLocations.at(x) == tankLocations.at(y))
            {
              cout << "Tanks cannot spawn on the same tile!" << endl;
              continue;
            }
          }
        }
        
        if (!quiet)
          cout << "  finding spawn...";
        i = args.find(' ', i+1); //skip x
        i = args.find(' ', i+1); //skip y

        args = args.substr(i+1); //chop off already used info
        if (!quiet)
          cout << "  colorizing tank...";
        i = args.find(' '); // find end of current item
        
        //Get our trunk image directory
        if (args.substr(0,i) == AINames.back()){
          imgPath = "images/Default";
          AIImages.push_back(imgPath + "/base.png");
          AIImages.push_back(imgPath + "/turret.png");
          AIImages.push_back(imgPath + "/tankD.png");
          AIImages.push_back(imgPath + "/tankL.png");
          AIImages.push_back(imgPath + "/bullet.png");
        }else{
          imgPath = args.substr(0, i);
          AIImages.push_back(imgPath + "/tankU.png");
          AIImages.push_back(imgPath + "/tankR.png");
          AIImages.push_back(imgPath + "/tankD.png");
          AIImages.push_back(imgPath + "/tankL.png");
          AIImages.push_back(imgPath + "/bullet.png");
        }
        
        
        tankImages.insert(std::end(tankImages), std::begin(AIImages), std::end(AIImages));
        
        AIImages.clear();
        if (!quiet)
          cout << "  ...done.\n";
      }
      else if(id == "AI_SPEED")
      {
        stringstream(args) >> ai_speed;
        settings->setIdleSpeed(ai_speed);
      }
      else if(id == "ANIMATION_SPEED")
      {
        stringstream(args) >> aniSpeed;
        settings->setAniFrames(aniSpeed);
      }
      else if(id == "TANK_SPEED")
      {
        stringstream(args) >> tank_speed;
        settings->setTankSpeed(tank_speed);
      }
      else if(id == "BULLET_SPEED")
      {
        stringstream(args) >> bullet_speed;
        settings->setBulletSpeed(bullet_speed);
      }
      else if(id == "MAXTURNS")
      {
        stringstream(args) >> maxT;
        settings->setMaxTurns(maxT);
      }
      else if(id == "FIELDIMAGE")
      {
        if (!settings->showUI()){continue;}
        if (!quiet)
          cout << "Painting the background...\n";
        stringstream(args) >> name;
        gameImages.push_back(name);
        if(!quiet)
          cout << "   ...done\n";
      }
      else if(id == "OBSTACLE_IMAGE")
      {
        if (!settings->showUI()){continue;}
        done = false;
        while(!done)
        {
          if(args.find(' ') == string::npos)
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
      else if(id == "TREE_IMAGE")
      {
        if (!settings->showUI()){continue;}
        done = false;
        while(!done)
        {
          if(args.find(' ') == string::npos)
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
      else if(id == "ROCK_IMAGE")
      {
        if (!settings->showUI()){continue;}
        done = false;
        while(!done)
        {
          if(args.find(' ') == string::npos)
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
      else if(id == "WATER_IMAGE")
      {
        if (!settings->showUI()){continue;}
        done = false;
        while(!done)
        {
          if(args.find(' ') == string::npos)
          {
            done = true;
            waterImages.push_back(args);
          }
          else
          {
            i = args.find(' ');
            waterImages.push_back(args.substr(0, i));
            args = args.substr(i + 1);
          }

        }
      }
      else if(id == "BUSH_IMAGE")
      {
        if (!settings->showUI()){continue;}
        done = false;
        while(!done)
        {
          if(args.find(' ') == string::npos)
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
      else if(id == "DAMAGE")
      {
        stringstream(args) >> damage;
        settings->setAttrDamage(damage);
      }
      else if(id == "HEALTH")
      {
        stringstream(args) >> health;
        settings->setAttrHealth(health);
      }
      else if(id == "AP")
      {
        stringstream(args) >> ap;
        settings->setAttrAP(ap);
      }
      else if(id == "RADAR")
      {
        stringstream(args) >> radar;
        settings->setAttrRadar(radar, width);
      }
      else if(id == "RANGE")
      {
        stringstream(args) >> range;
        settings->setAttrRange(range);
      }
      else if(id == "SPECIAL")
      {
        stringstream(args) >> attributePoints;
        settings->setAttrSpecial(attributePoints);
      }
      else if(id == "AMMO")
      {
        stringstream(args) >> ammo;
        settings->setAttrAmmo(ammo);
      }
      else if(id != "")
      {
        if (!quiet)
          std::cout << "BAD ARGUMENT: " << id << '\n';
      }
    }
  }
  if (mapLoader == nullptr){
    printf("ERROR: No map name specified or loaded.\n");
    exit(1);
  }
  //set globals
  TimerEvent::idle_speed = ai_speed;
  Drawable::xscalar = (3.75/width)/.32;
  Drawable::yscalar = Drawable::xscalar;
  fieldx = width;
  fieldy = height;

  //Only load textures if we're showing UI
  if (settings->showUI()){
    glEnable(GL_TEXTURE_2D);
    if(!LoadGLTextures(tankImages, gameImages, treeImages, rockImages, bushImages, waterImages, quiet) && !quiet)
        cout << "Failed to open image(s).\n" << endl;
    glDisable(GL_TEXTURE_2D);
  }
  if (!quiet)
    cout << "Loading Shared Objects...\n";
  std::vector<Actor*> startActorPointers = dynamicTankLoader(AINames);
  std::vector<ActorInfo> startActors;

  if (!quiet)
    cout << "Finalizing game settings...\n";

  baseStats = settings->getAttributes();

  startActors = loadPlayers(quiet, tankLocations, AINames, startActorPointers, baseStats, height, width);
  //printf("Height: %d  Width: %d\n",height, width);
  tankGame = new GameField(width, height, startActors, displayWrapper, this, settings);
  tankGame->setMap(mapLoader);
  tankGame->setSPECIAL(baseStats);
  if (!quiet)
    cout << "   ...Done\n" << endl;

  // Add obstacles to the gamefield
  if (!quiet)
    cout << "Clearing spawn points...\n";
  for(auto tank : tankLocations)
  {
    if (mapLoader->tileMap[tank.second][tank.first].type == "Rock"
      || mapLoader->tileMap[tank.second][tank.first].type == "Water"
      || mapLoader->tileMap[tank.second][tank.first].type == "Hedgehog")
    {
      if (!quiet)
        cout << "WARNING: removing object at (" << tank.first << "," << tank.second << ")\n";
      mapLoader->tileMap[tank.second][tank.first].type = "Empty";
      mapLoader->tileMap[tank.second][tank.first].health = 0;
    }
  }
  //Create drawable objects
  for (unsigned int i = 1; i <= height; i++){
    for (unsigned int j=1; j <= width; j++){
      tType = mapLoader->tileMap[i][j].type;
      
      if(tType == "Rock"){
          tempOb = new Obstacles(1, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i);
          rocks.push_back(tempOb);
      }else if (tType == "Water"){
          tempOb = new Obstacles(3, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i);
          constants.push_back(tempOb);
      }else if (tType == "Bush"){
          tempOb = new Obstacles(2, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i);
          bushes.push_back(tempOb);
      }else if (tType == "Tree"){
          tempOb = new Obstacles(0, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i);
          trees.push_back(tempOb);
      }else if (tType == "Crate"){
          tempObj = new Crate(convertGLXCoordinate(j), convertGLYCoordinate(i), j, i);
          specials.push_back(tempObj);
      }else if (tType == "Hedgehog"){
          tempOb = new Obstacles(50, convertGLXCoordinate(j), convertGLYCoordinate(i), j, i);
          constants.push_back(tempOb);
      }
    }
  }

  if (!quiet)
    cout << "...done.\n" << endl;
  if (settings->checkCoverage()){
    cout << "Turning on coverage mode." << endl;
    settings->setIdleSpeed(1);
    settings->setAniFrames(1);
    settings->setTankSpeed(1);
    settings->setBulletSpeed(1);
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
    cout << "Creating Player Tanks...\n";
  for(unsigned int i = 0; i < startActorPointers.size(); ++i)
  {
    if ( tankLocations[i].first <= width &&
         tankLocations[i].first >= 1 &&
         tankLocations[i].second <= height &&
         tankLocations[i].second >= 1){
         actors.push_back(ActorInfo(startActorPointers[i]
                                    , baseAttr.tankHealth
                                    , baseAttr.tankDamage
                                    , tankLocations[i].first
                                    , tankLocations[i].second
                                    , i + 1
                                    , baseAttr.tankAP
                                    , baseAttr.projRange
                                    , 0
                                    , baseAttr.tankRadar
                                    , baseAttr.tankAmmo
                                    , AINames[i]));
    //printf("Actor %d name: %s\n", i, AINames[i].c_str());
    }else{
      cout << "WARNING: Invalid location for " << AINames[i] << " (" << tankLocations[i].first << "," << tankLocations[i].second << ")" << endl;
    }
  }
  return actors;
}

/***************************************************************************//**
 * @author Jon McKee
 * @brief createConfig
 *
 * Creates new config file
 *******************************************************************************/
void Game::createConfig()
{
  ifstream fin;
  ofstream fout;
  cout << "FAILED TO LOAD CONFIG FILE\n";
  cout << "Attempting to generate config file...\n";
  fin.open("config.sample");
  fout.open("config.txt", ios::out | ios::in | ios::app);
  if(!fin || !fout)
  {
    cout << "Unable to generate new config file.\n";
    exit(1);
  }

  fout << "WIDTH 30\n";
  fout << "HEIGHT 14\n";
  fout << "MAP\n";
  fout << "xxxxxxxxRRRRRRxxxxxxxxRRRRRRxx\n";
  fout << "xxxxxxxTWWRRWWTxxxxxxTWWRRWWTx\n";
  fout << "xxxxxxTTTBTTTBTTxxxxTTTBTTTBTT\n";
  fout << "xxxxxCxxxxxxxxxxxxxxxxxxxxxxxx\n";
  fout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxB\n";
  fout << "xxxxTxxxxxTxxxxxTxxxxxTxxxxBBT\n";
  fout << "xxTTBTTxTTBTTxTTBTTxTTBTTxxTTB\n";
  fout << "xxRxRxRxRxRxRxRxRxRxRxRxRxxRxR\n";
  fout << "Oxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
  fout << "Oxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
  fout << "OxxRxxxxxRxxxxxRxxxxWRxxxxxxxx\n";
  fout << "xxTTTxxxTTTxxxTTTWWWTTTxxxxxxx\n";
  fout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
  fout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
  fout << "#AI LIST: AI <NAME> <STARTX> <STARTY> <UPIMAGE> <RIGHTIMAGE> <DOWNIMAGE> <LEFTIMAGE> <BULLETIMAGE>\n\n";
  fout << "#AI IDLE SPEED: AI_SPEED <750>\n";
  fout << "AI_SPEED 750\n\n";
  fout << "#FIELDIMAGE <MAP FILE>\n";
  fout << "FIELDIMAGE images/green.png\n\n";
  fout << "#OBSTACLE_IMAGE <IMAGE1> [<IMAGE2>]\n";
  fout << "OBSTACLE_IMAGE images/tree/tree.png images/rock/rock.png\n";
  fout << "TREE_IMAGE images/tree/tree.png images/tree/treeb.png images/tree/treec.png images/tree/treed.png\n";
  fout << "BUSH_IMAGE images/bush/bush1.png images/bush/bush2.png images/bush/bush3.png images/bush/bush4.png\n";
  fout << "ROCK_IMAGE images/rock/rock.png images/rock/rockb.png images/rock/rockc.png\n";
  fout << "WATER_IMAGE images/Water/waterTex.png images/Water/waterTexNS.png images/Water/waterTexES.png images/Water/waterTexSS.png images/Water/waterTexWS.png images/Water/waterTexNES.png images/Water/waterTexSES.png images/Water/waterTexSWS.png images/Water/waterTexNWS.png images/Water/waterTexEWS.png images/Water/waterTexNSS.png images/Water/waterTexNWES.png images/Water/waterTexNESS.png images/Water/waterTexSEWS.png images/Water/waterTexNWSS.png images/Water/waterTexPond.png\n\n";
  fout << "#Game Settings\n";
  fout << "#MAXTURNS 200\n";
  fout << "MAXTURNS 200\n\n";
  fout << "#AI_SPEED <750>\n";
  fout << "AI_SPEED 750\n\n";
  fout << "#BULLET_SPEED <80>\n";
  fout << "BULLET_SPEED 80\n\n";
  fout << "#TANK_SPEED <400>\n";
  fout << "TANK_SPEED 400\n\n";
  fout << "#ANIMATION_SPEED <20>\n";
  fout << "ANIMATION_SPEED 20\n\n";
  fout << "#TANK RULES\n";
  fout << "#STAT <AMMOUNT>\n";
  fout << "#VALID STATS: DAMAGE, HEALTH, RADAR, AP, SPECIAL, RANGE, AMMO\n";
  fout << "DAMAGE 1\n";
  fout << "HEALTH 3\n";
  fout << "RADAR 4\n";
  fout << "AP 2\n";
  fout << "SPECIAL 1\n";
  fout << "RANGE 4\n";
  fout << "AMMO 6\n";

  fin.close();
  fout.close();
  cout << "   ...done.\n";
  cout << "Please add tanks to the new config.txt and re-run the platform.\n";
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