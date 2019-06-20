#include <game/gameover.h>

/***************************************************************************//**
 * @author Chezka Gaddi
 * @brief gameOver
 *
 * Display the screen that reads game over
 *******************************************************************************/
void gameOver(std::vector<ActorInfo> dead, std::vector<ActorInfo> winner, Settings * settings, int turn)
{
  std::ofstream fout(settings->getResultsFile(), std::ios::out | std::ios::app);
  unsigned int winDex = 0;

  if(winner.size() != 0)
  {
    while(winDex < winner.size() && winner[winDex].id <= 0)
      winDex++; 
    fout << "\n\nGame ended on turn: " << turn;
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
  }else{ //Draw Game
    fout << "\n\nGame ended on turn: " << turn;
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

  if (settings->showUI())
    displayScoreBoard(dead, winner, settings, winDex);
}

void displayScoreBoard(std::vector<ActorInfo> dead, std::vector<ActorInfo> winner, Settings * settings, int winDex){
  const char *str;
  std::string scoreDetails[4] = {"Place:", "Player Number:", "Kills:","Hits:"};
  float color[] = {1.0f, 1.0f, 1.0f};
  float j = -0.7f;
  float k = -0.5;
  bool flag = false;
  int count = 1;
  int timer_pause = settings->getIdleSpeed() * 133;

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
  timer_pause = settings->getIdleSpeed() * 533;
  timer_pause >= 0 ? usleep(timer_pause) : usleep(0);
  printf("Exiting!\n");
}