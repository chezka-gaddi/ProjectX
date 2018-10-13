#include "Drawable.h"
#include <iostream>
#include <cstring>

using namespace std;

void drawBitmapText( char *string, float x, float y );


Menu::Menu( int id, int hp, int ammo )
{
    if( id == 1 )
    {
        strncpy(name, "Player 1", 9);
        screen_x = -0.8;
    }
    
    else
    {
        strncpy(name, "Player 2", 9);
        screen_x = 0.5;
    }

    screen_y = 0.7;
    health = hp;
    bullet = ammo;
}


void Menu::draw()
{
    glEnable(GL_TEXTURE_2D);
    glColor4ub(255,255,255,255);
    glPushMatrix();
    
    drawPlayerStats();
    
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}


void Menu::drawPlayerStats()
{
    drawBitmapText(name, screen_x, screen_y);
    
    char strHealth[10] = "HP: ";
    char hp[3];
    sprintf(hp, "%d", health);
    strcat(strHealth, hp);
    drawBitmapText(strHealth, screen_x, screen_y - 0.05);
    
    char strAmmo[10] = "Ammo: ";
    char ammo[4];
    sprintf(ammo, "%d", bullet);
    strcat(strAmmo, ammo);
    drawBitmapText(strAmmo, screen_x, screen_y - 0.10);
}


void drawBitmapText( char *string, float x, float y )
{
    glDisable(GL_TEXTURE_2D);
    char *c;
    glColor3f( 250, 250, 250 );
    glRasterPos3f( x, y, -2.0 );
    
    for( c = string; *c != '\0'; c++ )
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, *c );
}
