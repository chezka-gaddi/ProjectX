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
  /*
     if (fieldx < 19){
     fscaler = x * ((-.013 * fieldx) + .445);
     }else if (fieldx >= 20 && fieldx <= 25){
     fscaler = x * ((-0.0075 * fieldx) + 0.335);
     }else if (fieldx > 25){
     fscaler = x * ((-0.005050 * fieldx) + .273750);
     }*/
  // Function:fscalar = 4.0717x^-1.031
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
float Game::convertGLYCoordinate(int y)
{
  // Formula: fscalar = y * (3.1923fieldy^-1.08)
  //float fscalar = y * 2.7/(fieldy);
  //float fscalar = y * .3; //9
  //float fscalar = y * .215; //12
  //float fscalar = y * .170; //15
  //float fscalar = .142; //18
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
void gameOver(std::vector<ActorInfo> dead, std::vector<ActorInfo> winner)
{

  const char *str;
  std::string scoreDetails[4] = {"Place:", "Player Number:", "Kills:","Hits:"};

  float color[] = {1.0f, 1.0f, 1.0f};
  float pause;

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

  float j = -0.7f;
  bool flag = false;

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

    int count = 1;
    int winDex = 0;
    float k = -0.5;

    while(winner[winDex].name == "default\n" && winDex < winner.size())
      winDex++;

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

  sleep(1);
  glutSwapBuffers();
  sleep(4);
  printf("Exiting!\n");
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
  //printf("Current Turns:  %d of %d\n",tankGame->getTurnCount(), max_turns);
  if(tankGame->getTurnCount() == max_turns)
  {
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
    tankGame->turnCount++;
    tankGame->cull();//Let game play one more turn and quit itself
  }
  else if(isplayable(tankGame->getActorsConst())) //If we still have tanks keep playing
  {
    tankGame->nextTurn();
  }
  else   //If maxturns is not hit, and no longer playable print results
  {
    ofstream fout("results.txt", ios::out | ios::app);
    fout << tankGame->getWinner() << endl;
    fout.close();
    gameOver(tankGame->getDeceased(), tankGame->getActors());
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
float Drawable::xscalar = 1.0;
float Drawable::yscalar = 1.0;
int TimerEvent::idle_speed = 750;
void Game::initGameState()
{
  std::cout << "Game::Loading config.txt\n";
  ifstream fin("config.txt");
  std::string configLine;
  int x=0, y=0, i=0; //Temp Holders
  Obstacles* tempOb;
  Drawable *temp = nullptr;
  bool taken, done;

  //Game Setting defaults
  int ai_speed = 1000, width = 15, height = 9, maxT = 20, hPad = 0, wPad = 0;
  //Tank Defaults
  int damage = 1, health = 3, range = 4, radar = 4, ap = 1, ammo = 6;
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
        for(y; y < height - hPad; y++)
        {
          if(y == height/3)
            cout << "  Planting trees...\n";
          else if(y == height/3*2)
            cout << "  Moving rocks...\n";
          else if(y == height-1)
            cout << "  Trimming bushes...\n";
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
        }
        cout << endl;
        for(y; y < height; y++)
        {
          for(x = 0; x < width; x++)
          {
            obstacleLocations.push_back(std::pair<int, int> (x, y));
          }
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
            cout << "Waking up the tank commanders...\n";
          cout << "   Checking player " << AINames.size()+1 << "...";
          int x, y;
          i = args.find(' ');
          AINames.push_back(args.substr(0, i));
          std::stringstream(args.substr(i+1)) >> x >> y;
          //printf("\nTank at: Actual: %d, %d Modified: %d, %d.\n",x, y, x+wPad,y+hPad);
          tankLocations.push_back(std::pair<int,int>(x+wPad,y+hPad));
          for(int x=0; x < tankLocations.size(); x++)
          {
            for(int y = x + 1; y < tankLocations.size(); y++)
            {
              if(tankLocations.at(x) == tankLocations.at(y))
              {
                cout << "Tanks cannot spawn on the same tile!" << endl;
                exit(1);
              }
            }
          }
          cout << "  finding spawn...";
          i = args.find(' ', i+1);    //skip x
          i = args.find(' ', i+1);    //skip y

          args = args.substr(i+1);
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
          cout << "  ...done.\n";
        }
        else if(id == "AI_SPEED")
        {
          cout << "Speeding up the AI's...  \n";
          stringstream(args) >> ai_speed;
          if(ai_speed > 1500)
          {
            cout << "Speeds above 1500 are extremely slow, defaulting at 1500\n";
            ai_speed = 1500;
          }
          TimerEvent::idle_speed = ai_speed;
          idle_speed = ai_speed;
          cout << "   ...done.\n";
        }
        else if(id == "ANIMATION_SPEED")
        {
          cout << "Slowing down time...  \n";
          stringstream(args) >> aniSpeed;
          if(aniSpeed > 30)
          {
            cout << "Speeds above 30 are slow, defaulting to 30\n";
            aniSpeed = 30;
          }else if (aniSpeed < 0){
            cout << "Speed below 0 are now allowed, defaulting to 0\n";
            aniSpeed = 0;
          }
          cout << "   ...done.\n";
        }
        else if(id == "TANK_SPEED")
        {
          cout << "Greasing the wheels...  \n";
          stringstream(args) >> tank_speed;
          if(tank_speed > 400)
          {
            cout << "Tank speeds above 400 are extremely slow, defaulting to 400\n";
            tank_speed = 30;
          }else if (tank_speed < 0){
            cout << "Tank speed below 0 are now allowed, defaulting to 0\n";
            tank_speed = 0;
          }
          cout << "   ...done.\n";
        }
        else if(id == "BULLET_SPEED")
        {
          cout << "Putting helium in the bullets...  \n";
          stringstream(args) >> bullet_speed;
          if(bullet_speed > 70)
          {
            cout << "Bullet speeds above 70 are extremely slow, defaulting to 70\n";
            bullet_speed = 70;
          }else if (bullet_speed < 0){
            cout << "Bullet speeds below 0 are now allowed, defaulting to 0\n";
            aniSpeed = 0;
          }
          cout << "   ...done.\n";
        }
        //field params
        else if(id == "WIDTH")
        {
          cout << "S t r e t c h i n g   t h e   m a p . . .  ";
          stringstream(args) >> width;
          if(width < 5)
          {
            width < 5;
            printf("\nInvalid width parameter, defaulting to %d.\n", width);
          }
          else if(width > 50)
          {
            width = 50;
            cout << "\nWidth parameter too high, defaulting to 50.\n";
          }
          cout << "...done.\n";
        }
        else if(id == "HEIGHT")
        {
          cout << "Elon\n    gati\n        ng t\n            he ma\n                p...  ";
          stringstream(args) >> height;
          if(height < 5)
          {
            height = 5;
            printf("Invalid height parameter, defaulting to %d.\n", height);
          }
          else if(height > 21)
          {
            height = 21;
            cout << "Height parameter too high, defaulting to 21.\n";
          }
          cout << "\n                                                                   ...done.\n";
        }
        else if(id == "MAXTURNS")
        {
          cout << "Reducing camping spots...\n";
          stringstream(args) >> maxT;
          if(maxT < 1)
          {
            maxT = 1;
            cout << "Invalid max_turn parameter, defaulting to 1.\n";
          }
          else if(maxT > 200)
          {
            width = 200;
            cout << "Max turns set too high, defaulting to 200.\n";
          }
          max_turns = maxT;
          cout << "   ...done.\n";
        }
        else if(id == "DISABLEGUI")
        {
          cout << "Hiding Everything\n";
          ui = false;
          cout << "   ...done.\n";
        }
        else if(id == "FIELDIMAGE")
        {
          cout << "Painting the background...\n";
          stringstream(args) >> name;
          gameImages.push_back(name);
          cout << "   ...done\n";
        }
        else if(id == "OBSTACLE" || id == "TREE" || id == "ROCK" || id == "BUSH" || id == "CRATE" || id =="WATER")
        {
          stringstream(args) >> x >> y;
          if(x > width - 1 || x < 0 || y > height - 1 || y < 0)
          {
            printf("Invalid obstacle location: (%d, %d). Ranges: (0-%d, 0-%d)\n", x, y, width-1, height-1);
          }
          else
          {
            for(int i = 0; i < tankLocations.size(); i ++)
            {
              if(tankLocations[i].first == x && tankLocations[i].second == y)
              {
                taken = true;
                printf("Invalid obstacle location: (%d, %d) aleady taken by tank\n", x, y);
              }
            }
            if(!taken)
            {
              for(int i = 0; i < obstacleLocations.size(); i ++)
              {
                if(obstacleLocations[i].first == x && obstacleLocations[i].second == y)
                {
                  taken = true;
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
          if(damage < 0)
          {
            damage = 0;
            printf("Invalid damage value, defaulting to %d\n", damage);
          }
          else if(damage > 8)
          {
            printf("%d damage might be a little excesive, setting to 10\n", damage);
            damage = 8;
          }
        }
        else if(id == "HEALTH")
        {
          stringstream(args) >> health;
          if(health < 0)
          {
            health = 0;
            printf("Invalid health value, defaulting to %d\n", health);
          }
          else if(health > 8)
          {
            printf("%d health might be a little excesive, setting to 8\n", health);
            health = 8;
          }
        }
        else if(id == "AP")
        {
          stringstream(args) >> ap;
          if(ap < 0)
          {
            ap = 0;
            printf("Invalid number of action points value, defaulting to %d\n", ap);
          }
          else if(ap > 6)
          {
            printf("%d range might be a little excesive, setting to 6\n", ap);
            ap = 6;
          }
        }
        else if(id == "RADAR")
        {
          stringstream(args) >> radar;
          if(radar < 0)
          {
            radar = 0;
            printf("Invalid radar value, defaulting to %d\n", radar );
          }
          else if(radar > width)
          {
            printf("%d radar might be a little excesive, setting to %d\n", radar, width);
            radar = width;
          }
        }
        else if(id == "RANGE")
        {
          stringstream(args) >> range;
          if(range < 0)
          {
            range = 0;
            printf("Invalid range value, defaulting to %d\n", range);
          }
          else if(range > 10)
          {
            printf("%d range might be a little excesive, setting to %d\n", range, 10);
            range = 10;
          }
        }
        else if(id == "SPECIAL")
        {
          stringstream(args) >> attributePoints;
          if(attributePoints < 0)
          {
            attributePoints = 0;
            printf("Invalid special value, defaulting to %d\n", attributePoints);
          }
          else if(attributePoints > 20)
          {
            printf("%d specials might be a little excesive, setting to 20.\n", attributePoints);
            attributePoints = 20;
          }
        }
        else if(id == "AMMO")
        {
          stringstream(args) >> ammo;
          if(ammo < 0)
          {
            ammo = 0;
            printf("Invalid ammo amount, defaulting to %d\n", ammo);
          }
          else if(ammo > 10)
          {
            printf("%d ammo might be a little excesive, setting to 10.\n", ammo);
            ammo = 10;
          }
        }
        else if(id != "")
        {
          std::cout << "BAD ARGUMENT: " << id << '\n';
        }

      }
    }
  }

  Drawable::xscalar = (3.75/width)/.32;
  Drawable::yscalar = Drawable::xscalar;
  //Drawable::yscalar = (3.75/height)/.50;
  fieldx = width;
  fieldy = height;

  glEnable(GL_TEXTURE_2D);
  if(!LoadGLTextures(tankImages, gameImages, treeImages, rockImages, bushImages, waterImages))
    cout << "Failed to open image(s).\n" << endl;
  glDisable(GL_TEXTURE_2D);

  cout << "Loading Shared Objects...\n";
  std::vector<Actor*> startActorPointers = dynamicTankLoader(AINames);

  std::vector<ActorInfo> startActors;


  fout << "Players: ";
  cout << "Creating Player Tanks...\n";
  for(int i = 0; i < startActorPointers.size(); ++i)
  {
    startActors.push_back(ActorInfo(startActorPointers[i]
                                    , health
                                    , damage
                                    , tankLocations[i].first
                                    , tankLocations[i].second
                                    , i + 1
                                    , ap
                                    , range
                                    , 0
                                    , radar
                                    , ammo
                                    , AINames[i]));
    //printf("Actor %d name: %s\n", i, AINames[i].c_str());
    fout << AINames[i] << " ";
  }
  fout << "Winner: ";
  cout << "  ...Done" << endl;
  fout.close();
  int count = 0;

  cout << "Finalizing game settings...\n";
  //printf("Height: %d  Width: %d\n",height, width);
  tankGame = new GameField(width, height, startActors, displayWrapper, this);
  baseStats.tankHealth = health;
  baseStats.tankDamage = damage;
  baseStats.tankAP = ap;
  baseStats.tankAmmo = ammo;
  baseStats.tankRadar = radar;
  baseStats.tankRange = range;

  tankGame->setSPECIAL(attributePoints, baseStats);
  cout << "   ...Done\n" << endl;

// Add obstacles to the gamefield
  cout << "Placing Obstacles...\n";
  for(auto o : obstacleLocations)
  {
    taken = false;
    for(auto tank : tankLocations)
    {
      if(tank.first == o.first && tank.second == o.second){
        taken = true;
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
  cout << "  ...hiding the ammo\n";
  for(auto c : specialLocations)
  {
    taken = false;
    for(auto tank : tankLocations)
    {
      if(tank.first == c.first && tank.second == c.second){
        taken = true;
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
  cout << "  ...letting the trees grow\n";
  for(auto t : treeLocations)
  {
    tankGame->addObstacle(t.first, t.second, 'T');
    tempOb = new Obstacles(0, convertGLXCoordinate(t.first), convertGLYCoordinate(t.second), t.first, t.second);
    trees.push_back(tempOb);
  }
  cout << "  ...petting the rocks\n";
  for(auto r : rockLocations)
  {
    taken = false;
    for(auto tank : tankLocations)
    {
      if(tank.first == r.first && tank.second == r.second){
        taken = true;
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
  cout << "  ...finding some shrubberies\n";
  for(auto b : bushLocations)
  {
    tankGame->addObstacle(b.first, b.second, 'B');
    tempOb = new Obstacles(2, convertGLXCoordinate(b.first), convertGLYCoordinate(b.second), b.first, b.second);
    bushes.push_back(tempOb);
  }
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
  cout << "...done.\n" << endl;
}
/***************************************************************************//**
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
  fout << "#Max Turns\n";
  fout << "#MAXTURNS 200\n";
  fout << "MAXTURNS 200\n\n";
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
