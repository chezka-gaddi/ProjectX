/***************************************************************************//**
* @file Texture.cpp
* @author Chezka Gaddi
* @brief Contain the function that creates the game textures
*******************************************************************************/

#include "Texture.h"
#include <iostream>
using namespace std;

// Initialize texture arrays
GLuint gameTex[8];      /*!<Texture array for the tanks and their projectiles */
GLuint tankTex[18];      /*!<Texture array for game constants */


/***************************************************************************//**
* @author Chezka Gaddi
* @brief LoadGLTextures
*
* Loads and saves all the textures needed for the game in texture arrays.
*******************************************************************************/
int LoadGLTextures(std::vector <std::string> images, std::vector <std::string> gameimgs)
{
    // Load in the tank texure information
    for( int i = 0; i < 18; i++ )
    {
        cout << images.size() << endl;
        cout << images[i] << endl;
        const char *c = images[i].c_str();
        tankTex[i] = SOIL_load_OGL_texture(
                     c,
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

        if(tankTex[i] == 0)
        return false;

        glBindTexture(GL_TEXTURE_2D, tankTex[i]);
    }




    // Load in constant game images
    gameTex[0] = SOIL_load_OGL_texture(
                     "images/background.png",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

    if(gameTex[0] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, gameTex[0]);


    for( int i = 1; i < 4; i++ )
    {
        const char *c = gameimgs[i-1].c_str();
        cout << c << endl;
        gameTex[i] = SOIL_load_OGL_texture(
                     c,
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

        if(gameTex[i] == 0)
        return false;

        glBindTexture(GL_TEXTURE_2D, gameTex[i]);
    }


    gameTex[4] = SOIL_load_OGL_texture(
                     "images/heart.png",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

    if(gameTex[4] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, gameTex[4]);


    gameTex[5] = SOIL_load_OGL_texture(
                     "images/textbox.png",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

    if(gameTex[5] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, gameTex[5]);


    gameTex[6] = SOIL_load_OGL_texture(
                     "images/bomb.png",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

    if(gameTex[6] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, gameTex[6]);


    gameTex[7] = SOIL_load_OGL_texture(
                     "images/GAME.png",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

    if(gameTex[7] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, gameTex[7]);


    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    return true;
}
