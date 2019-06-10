/***************************************************************************//**
 * @file game.cpp
 * @author Chezka Gaddi
 * @brief Contains all functions that maintains Game class.
 *******************************************************************************/

#include "../game/game.h"
#include "../ui/callbacks.h"
#include "../ui/event.h"
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
  fscaler = x * (4.0717* pow(fieldx, -1.031));
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
  float fscaler =  y * (3.1923* pow(fieldy, -1.08));
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



/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief gameOver
 *
 * Display the screen that reads game over
 *******************************************************************************/
void Game::gameOver(std::vector<ActorInfo> dead, std::vector<ActorInfo> winner)
{


  const char *str;
  std::string scoreDetails[4] = {"Place:", "Player Number:", "Kills:","Hits:"};
  float color[] = {1.0f, 1.0f, 1.0f};
  float j = -0.7f;
  float k = -0.5;

  ofstream fout("results.txt", ios::out | ios::app);
  bool flag = false;

  unsigned int winDex = 0;
  int count = 1;
  int timer_pause = TimerEvent::idle_speed * 133;

  while(winner[winDex].name == "default\n" && winDex < winner.size())
    winDex++;
  if(winner.size() != 0)
  { 
    fout << "\n\nGame ended on turn: " << settings->getTurn();
    fout << "\nWinner: " << winner[winDex].name
        << " Kills: " << winner[winDex].kills
        << " Shots: " << std::to_string(winner[winDex].shots).c_str()
        << " Hits: " << std::to_string(winner[winDex].hits).c_str();
    fout << " AP: " << std::to_string(winner[winDex].AP).c_str()
        << " Radar: " << std::to_string(winner[winDex].radar).c_str();
    fout << " Max Health: " << std::to_string(winner[winDex].max_health).c_str()
        << " Remaining: " << std::to_string(winner[winDex].health).c_str()
        << " Max Ammo: " << std::to_string(winner[winDex].max_ammo).c_str()
        << " Remaining: " << std::to_string(winner[winDex].health).c_str()
        << " Final Position: (" << std::to_string(winner[winDex].x).c_str()
        << "," << std::to_string(winner[winDex].y).c_str() << ")\n";
    fout << "Non-Winning Participants:";
    
    for(int l = dead.size() - 1; l >= 0; l--)
    {
      fout << "\nParticipant: " << dead[l].name
          << " Kills: " << dead[l].kills
          << " Shots: " << dead[l].shots
          << " Hits: " << dead[l].hits;
      fout << " AP: " << dead[l].AP
          << " Radar: " << dead[l].radar;
      fout << " Max Health: " << dead[l].max_health
          << " Remaining: " << dead[l].health
          << " Max Ammo: " << dead[l].max_ammo
          << " Remaining: " << dead[l].health
          << " Final Position: (" << dead[l].x
          << "," << dead[l].y << ")";
    }
  }else{
    fout << "\n\nGame ended on turn: " << settings->getTurn();
    fout << "\nDraw Game: ";
    for(int l = dead.size() - 1; l >= 0; l--)
    {
      fout << "\nParticipant: " << dead[l].name
        << " Kills: " << dead[l].kills
        << " Shots: " << dead[l].shots
        << " Hits: " << dead[l].hits;
      fout << " AP: " << dead[l].AP
        << " Radar: " << dead[l].radar;
      fout << " Max Health: " << dead[l].max_health
        << " Remaining: " << dead[l].health
        << " Max Ammo: " << dead[l].max_ammo
        << " Remaining: " << dead[l].health
        << " Final Position: (" << dead[l].x
        << "," << dead[l].y << ")";
    }
  }

  if (!settings->showUI())
    return;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  glEnable(GL_TEXTURE_2D);

  glPushMatrix();
  glTranslatef(0.0f, 0.0f, -5.0f);
  glBindTexture(GL_TEXTURE_2D, gameTex[5]);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-0.8f, -0.3f,  1.0f);
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(0.8f, -0.3f,  1.0f);
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(0.8f,  0.8f,  1.0f);
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-0.8f,  0.8f,  1.0f);
  glEnd();
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);

  glPushMatrix();
  glTranslatef(0.0f, 0.0f, -5.0f);
  glColor3fv(color);

  if(winner.size() != 0)
  {
    for(int i = 0; i < 4; i++)
    {
      glRasterPos3f(j, -0.3f, 2.0f);
      str = scoreDetails[i].c_str();
      while(*str)
      {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *str);
        str++;
      }
      if(!flag)
      {
        j += 0.3;
        flag = true;
      }
      else
      {
        j += 0.7;
        flag = false;
      }
    }

    count = 1;
    k = -0.5;

    str = "1st";
    glRasterPos3f(-0.7f, k, 2.0f);
    while(*str)
    {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *str);
      str++;
    }

    str = winner[winDex].name.c_str();
    glRasterPos3f(-0.4f, k, 2.0f);
    while(*str)
    {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *str);
      str++;
    }

    str = std::to_string(winner[winDex].kills).c_str();
    glRasterPos3f(0.3f, k, 2.0f);
    while(*str)
    {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *str);
      str++;
    }

    str = std::to_string(winner[winDex].hits).c_str();
    glRasterPos3f(0.6f, k, 2.0f);
    while(*str)
    {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *str);
      str++;
    }
    k += -0.1f;
    count++;
    for(int l = dead.size() - 1; l >= 0; l--)
    {

      if(count < 4)
        switch(count)
        {
          case 2:
            str = "2nd";
            break;
          case 3:
            str = "3rd";
            break;
        }
      else
      {
        std::string s = std::to_string(count);
        s += "th";
        str = s.c_str();  //use char const* as target type      }
      }


      glRasterPos3f(-0.7f, k, 2.0f);
      while(*str)
      {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *str);
        str++;
      }


      //std::cout << "Finding " << count << "th place.........\n";
      str = dead[l].name.c_str();

      glRasterPos3f(-0.4f, k, 2.0f);
      while(*str)
      {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *str);
        str++;
      }

      str = std::to_string(dead[l].kills).c_str();
      glRasterPos3f(0.3f, k, 2.0f);
      while(*str)
      {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *str);
        str++;
      }

      str = std::to_string(dead[l].hits).c_str();
      glRasterPos3f(0.6f, k, 2.0f);
      while(*str)
      {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *str);
        str++;
      }

      k += -0.1f;
      count++;
    }
  }
  else
  {
    printf("Draw Game.\n");
    glRasterPos3f(-0.05f, -0.3f, 2.0f);
    std::string s = "DRAW";
    str = s.c_str();
    while(*str)
    {
      glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *str);
      str++;
    }
  }
  timer_pause >= 0 ? usleep(timer_pause) : usleep(0);

  glutSwapBuffers();
  timer_pause = TimerEvent::idle_speed * 533;
  timer_pause >= 0 ? usleep(timer_pause) : usleep(0);
  printf("Exiting!\n");
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
  if (settings->getTurn() != settings->getMaxTurns())
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
    //printf("Found a duplicate tie value: %d \n", tie);
    if(tie == true)   //If it is a tie clear out all tanks to get to draw screen
    {
      for(auto &a : *actors)
      {
        //printf("Health: %d \n", a.health);
        a.health = 0;
        //printf("Health: %d \n", a.health);
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
  gameOver(tankGame->getDeceased(), tankGame->getActors());
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
  bool quiet = (settings->getGameMode() == gameMode::quiet);
  if(!quiet)
    std::cout << "Game::Loading config.txt\n";
  ifstream fin("config.txt");
  std::string configLine;
  unsigned int x=0, y=0; //Temp Holders
  Obstacles* tempOb;
  Drawable *temp = nullptr;
  bool taken, done;

  //Game Setting defaults
  unsigned int ai_speed = 750, width = 15, height = 9, maxT = 1000, hPad = 0, wPad = 0;
  //setting defaults
  unsigned int aniSpeed = 20, tank_speed = 400, bullet_speed = 80;
  //Tank Defaults
  unsigned int damage = 1, health = 3, range = 4, radar = 4, ap = 1, ammo = 6;
  //Default Tank Images
  const std::vector<string> AIDefImg = {"images/Default/tankD_L.png", "images/Default/tankD_D.png",
                                        "images/Default/tankD_R.png","images/Default/tankD_U.png", "images/Default/bulletD.png"
                                       };
  attributes baseStats;

  //Location vectors
  std::vector<std::pair<int,int>> obstacleLocations, treeLocations, rockLocations, bushLocations,
      tankLocations, waterLocations, specialLocations;

  //Image vectors for custom images
  std::vector<std::string> tankImages, gameImages, treeImages, rockImages, bushImages,
      waterImages, AIImages, AINames;
  std::string name;
  int attributePoints = 0;
  ofstream fout;

  //Seed random for random obstacle selection
  srand(time(0));

  // Load game field
  constants.push_back(new GameFieldDrawable);

  if(!fin)
  {
    createConfig();
  }
  fout.open("results.txt", ios::out | ios::in | ios::app);
  if(!fout)
  {
    cout << "UNABLE OPEN RESULTS FILE (results.txt).  Game will play but results will not be saved.\n";
  }
  while(!fin.eof())
  {
    getline(fin, configLine);
    if(configLine[0] != '#') //Ignore comment lines
    {
      if(configLine == "MAP")
      {
        if (!quiet)
                cout << "Building the map...\n";
        if(height < 9)
        {
          hPad = (9 - height) / 2;
          height = 9;
          //cout << "hPad: " << hPad << endl;
        }
        if(width < 15)
        {
          wPad = (15 - width) / 2;
          width = 15;
          //cout << "wPad: " << wPad << endl;
        }
        for(y=0; y < hPad; y++)
        {
          for(x = 0; x < width; x++)
          {
            obstacleLocations.push_back(std::pair<int, int> (x, y));
          }
        }
        //cout << "Y equals: " << y << endl;
        while (y < height - hPad)
        {
          if(y == height/3){
            if (!quiet)
              cout << "  Planting trees...\n";
          }else if(y == height/3*2){
            if (!quiet)
              cout << "  Moving rocks...\n";
          }else if(y == height-1){
            if (!quiet)
              cout << "  Trimming bushes...\n";
          }
          getline(fin, configLine);
          //cout << configLine << endl;
          for(x = 0; x < width; x++)
          {
            if(x >= configLine.size() + wPad)
            {
              obstacleLocations.push_back(std::pair<int,int> (x, y));
            }
            else if(x < wPad)
            {
              obstacleLocations.push_back(std::pair<int,int> (x, y));
            }
            else
            {
              switch(configLine[x-wPad])
              {
                case 'B':
                case 'b':
                  bushLocations.push_back(std::pair<int,int> (x, y));
                  break;
                case 'R':
                case 'r':
                  rockLocations.push_back(std::pair<int,int> (x, y));
                  break;
                case 'T':
                case 't':
                  treeLocations.push_back(std::pair<int,int> (x, y));
                  break;
                case 'W':
                case 'w':
                  waterLocations.push_back(std::pair<int,int> (x, y));
                  break;
                case 'C':
                case 'c':
                  specialLocations.push_back(std::pair<int,int> (x, y));
                  break;
                case 'X':
                case 'x':
                case ' ':
                  break;
                default:
                  obstacleLocations.push_back(std::pair<int, int> (x, y));
                  break;
              }
            }
          }
        y++;
        }
        cout << endl;
        while(y < height)
        {
          for(x = 0; x < width; x++)
          {
            obstacleLocations.push_back(std::pair<int, int> (x, y));
          }
          y++;
        }
      }
      else
      {
        int i = configLine.find(' '); //index of first space
        std::string id = configLine.substr(0, i); //separate the identefier from the argumets
        std::string args = configLine.substr(i+1);
        //AI settings
        if(id == "AI")  //AI to load
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
                exit(1);
              }
            }
          }
          if (!quiet)
            cout << "  finding spawn...";
          i = args.find(' ', i+1);    //skip x
          i = args.find(' ', i+1);    //skip y

          args = args.substr(i+1);
          if (!quiet)
            cout << "  colorizing tank...";

          for(int x = 0; x < 5; x++)
          {
            i = args.find(' ');    //skip y
            name = args.substr(0,i);
            //printf("Image name: %s",name.c_str());
            AIImages.push_back(name);
            args = args.substr(i+1);
            if(args == AIImages[x])
              break;
          }
          //printf(". Array size: %d\n",(int)AIImages.size());
          if(AIImages.size() != 5)
          {
            tankImages.insert(std::end(tankImages), std::begin(AIDefImg), std::end(AIDefImg));
          }
          else
          {
            tankImages.insert(std::end(tankImages), std::begin(AIImages), std::end(AIImages));
          }
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
        //field params
        else if(id == "WIDTH")
        {
          if (!quiet)
            cout << "S t r e t c h i n g   t h e   m a p . . .  ";
          stringstream(args) >> width;
          if(width < 5)
          {
            width = 5;
            if (!quiet)
              printf("\nInvalid width parameter, defaulting to %d.\n", width);
          }
          else if(width > 50)
          {
            width = 50;
            if (!quiet)
              cout << "\nWidth parameter too high, defaulting to 50.\n";
          }
          if (!quiet)
            cout << "...done.\n";
        }
        else if(id == "HEIGHT")
        {
          if (!quiet)
            cout << "Elon\n    gati\n        ng t\n            he ma\n                p...  ";
          stringstream(args) >> height;
          if(height < 5)
          {
            height = 5;
            if (!quiet)
              printf("Invalid height parameter, defaulting to %d.\n", height);
          }
          else if(height > 21)
          {
            height = 21;
            if (!quiet)
              cout << "Height parameter too high, defaulting to 21.\n";
          }
          if (!quiet)
            cout << "\n                                                                   ...done.\n";
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
        else if(id == "OBSTACLE" || id == "TREE" || id == "ROCK" || id == "BUSH" || id == "CRATE" || id =="WATER")
        {
          stringstream(args) >> x >> y;
          if(x > width - 1 || x < 0 || y > height - 1 || y < 0)
          {
            if (!quiet)
              printf("Invalid obstacle location: (%d, %d). Ranges: (0-%d, 0-%d)\n", x, y, width-1, height-1);
          }
          else
          {
            for(unsigned int i = 0; i < tankLocations.size(); i ++)
            {
              if((unsigned int) tankLocations[i].first == x && (unsigned int)tankLocations[i].second == y)
              {
                taken = true;
                if (!quiet)
                  printf("Invalid obstacle location: (%d, %d) aleady taken by tank\n", x, y);
              }
            }
            if(!taken)
            {
              for(unsigned int i = 0; i < obstacleLocations.size(); i ++)
              {
                if((unsigned int)obstacleLocations[i].first == x && (unsigned int)obstacleLocations[i].second == y)
                {
                  taken = true;
                  if (!quiet)
                    printf("Invalid obstacle location: (%d, %d) aleady taken by object\n", x, y);
                }
              }
            }

            if(!taken && id == "TREE")
            {
              treeLocations.push_back(std::pair<int,int> (x, y));
            }
            else if(!taken && id == "ROCK")
            {
              rockLocations.push_back(std::pair<int,int> (x, y));
            }
            else if(!taken && id == "BUSH")
            {
              bushLocations.push_back(std::pair<int,int> (x, y));
            }
            else if(!taken && id == "CRATE")
            {
              specialLocations.push_back(std::pair<int,int> (x, y));
            }
            else if(!taken && id == "WATER")
            {
              waterLocations.push_back(std::pair<int,int> (x, y));
            }
            else
            {
              obstacleLocations.push_back(std::pair<int,int> (x, y));
            }
            taken = false;
          }
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

  baseStats.tankHealth = settings->getAttrHealth();
  baseStats.tankDamage = settings->getAttrDamage();
  baseStats.tankAP = settings->getAttrAP();
  baseStats.tankAmmo = settings->getAttrAmmo();
  baseStats.tankRadar = settings->getAttrRadar();
  baseStats.projRange = settings->getAttrRange();
  settings->setAttributes(baseStats);

  startActors = loadPlayers(quiet, tankLocations, AINames, startActorPointers, baseStats, height, width);
  //printf("Height: %d  Width: %d\n",height, width);
  tankGame = new GameField(width, height, startActors, displayWrapper, this, settings);
  tankGame->setSPECIAL(settings->getAttributes());
  if (!quiet)
    cout << "   ...Done\n" << endl;

// Add obstacles to the gamefield
  if (!quiet)
    cout << "Placing Obstacles...\n";
  for(auto o : obstacleLocations)
  {
    taken = false;
    for(auto tank : tankLocations)
    {
      if(tank.first == o.first && tank.second == o.second){
        taken = true;
      if (!quiet)
        printf("Spot %d, %d is being used for tank.\n", tank.first, tank.second);
      }
    }

    if(taken == false)
    {
      tankGame->addObstacle(o.first, o.second);
      tempOb = new Obstacles(50, convertGLXCoordinate(o.first), convertGLYCoordinate(o.second), o.first, o.second);
      constants.push_back(tempOb);
    }
  }
  if (!quiet)
    cout << "  ...hiding the ammo\n";
  for(auto c : specialLocations)
  {
    taken = false;
    for(auto tank : tankLocations)
    {
      if(tank.first == c.first && tank.second == c.second){
        taken = true;
        if (!quiet)
          printf("Spot %d, %d is being used for tank.\n", tank.first, tank.second);
      }
    }

    if(taken == false)
    {
    tankGame->addObstacle(c.first, c.second, 'C');
    temp = new Crate(convertGLXCoordinate(c.first), convertGLYCoordinate(c.second), c.first, c.second);
    specials.push_back(temp);
    }
  }
  if (!quiet)
    cout << "  ...letting the trees grow\n";
  for(auto t : treeLocations)
  {
    tankGame->addObstacle(t.first, t.second, 'T');
    tempOb = new Obstacles(0, convertGLXCoordinate(t.first), convertGLYCoordinate(t.second), t.first, t.second);
    trees.push_back(tempOb);
  }
  if (!quiet)
    cout << "  ...petting the rocks\n";
  for(auto r : rockLocations)
  {
    taken = false;
    for(auto tank : tankLocations)
    {
      if(tank.first == r.first && tank.second == r.second){
        taken = true;
      if (!quiet)
        printf("Spot %d, %d is being used for tank.\n", tank.first, tank.second);
      }
    }

    if(taken == false)
    {
    tankGame->addObstacle(r.first, r.second, 'R'); //No driving over rocks
    tempOb = new Obstacles(1, convertGLXCoordinate(r.first), convertGLYCoordinate(r.second), r.first, r.second);
    rocks.push_back(tempOb);
    }
  }
  if (!quiet)
    cout << "  ...finding some shrubberies\n";
  for(auto b : bushLocations)
  {
    tankGame->addObstacle(b.first, b.second, 'B');
    tempOb = new Obstacles(2, convertGLXCoordinate(b.first), convertGLYCoordinate(b.second), b.first, b.second);
    bushes.push_back(tempOb);
  }
  if (!quiet)
    cout << "  ...drilling for moisture\n";
  for(auto w : waterLocations)
  {
    taken = false;
    for(auto tank : tankLocations)
    {
      if(tank.first == w.first && tank.second == w.second){
        taken = true;
      printf("Spot %d, %d is being used for tank.\n", tank.first, tank.second);
      }
    }

    if(taken == false)
    {
    tankGame->addObstacle(w.first, w.second, 'W');
    temp = new Obstacles(3, convertGLXCoordinate(w.first), convertGLYCoordinate(w.second), w.first, w.second);
    waters.push_back(temp);
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
    if ( tankLocations[i].first < width &&
         tankLocations[i].first >= 0 &&
         tankLocations[i].second < height &&
         tankLocations[i].second >= 0){
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
      if (!quiet)
        cout << "Invalid location for " << AINames[i] << endl;
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
  fout << "#DISABLEUI UNCOMMENT TO DISABLE GUI\n";
  fout << "#DISABLEGUI \n\n";
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