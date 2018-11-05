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
GLuint tankTex[20];     /*!<Texture array for game constants */
GLuint treeTex[10];     /*!<Texture array for the trees */
GLuint bushTex[10];     /*!<Texture array for the bushes */
GLuint rockTex[10];     /*!<Texture array for the rocks */
GLuint sfxTex[10];   /*<Texture array for the special effects */

/***************************************************************************//**
* @author Chezka Gaddi
* @brief LoadGLTextures
*
* Loads and saves all the textures needed for the game in texture arrays.
*******************************************************************************/
int LoadGLTextures(std::vector <std::string> images, std::vector <std::string> gameimgs,
                   std::vector <std::string> trees, std::vector <std::string> rocks, 
                   std::vector <std::string> bushes)
{
    // Load in the tank texure information
    cout << "\nLoading Tank Textures:";
    for( int i = 0; i < images.size(); i++ )
    {
        const char *c = images[i].c_str();
        (i%5 == 0) ? cout << "\n" << c << "  " : cout << c << "  ";
        tankTex[i] = SOIL_load_OGL_texture(
                     c,
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

        if(tankTex[i] == 0)
        return false;
        
        glBindTexture(GL_TEXTURE_2D, tankTex[i]);
    }

    cout << "\nLoading Tree Textures:\n";
    // Load in the tree texure information
    for( int i = 0; i < trees.size(); i++ )
    {
        const char *c = trees[i].c_str();
        cout << c << "  ";
        treeTex[i] = SOIL_load_OGL_texture(
                     c,
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

        if(treeTex[i] == 0)
        return false;

        glBindTexture(GL_TEXTURE_2D, treeTex[i]);
    }
    cout << "\nLoading rock Textures:\n";
    // Load in the rock texures information
    for( int i = 0; i < rocks.size(); i++ )
    {
        const char *c = rocks[i].c_str();
        cout << c << "  ";
        rockTex[i] = SOIL_load_OGL_texture(
                     c,
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

        if(rockTex[i] == 0)
        return false;

        glBindTexture(GL_TEXTURE_2D, rockTex[i]);
    }
    cout << "\nLoading Bush Textures:\n";
    // Load in the bush texure information
    for( int i = 0; i < bushes.size(); i++ )
    {
        const char *c = bushes[i].c_str();
        cout << c << "  ";
        bushTex[i] = SOIL_load_OGL_texture(
                     c,
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

        if(bushTex[i] == 0)
        return false;

        glBindTexture(GL_TEXTURE_2D, bushTex[i]);
    }

    cout << "\nLoading UI Textures:\n";
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
        cout << c << "  ";
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

    cout << "\nLoading SFX Textures:\n";
    // Load in sfx game images
    sfxTex[0] = SOIL_load_OGL_texture(
                     "images/seffect/explosiona.png",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

    if(sfxTex[0] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, sfxTex[0]);
    sfxTex[1] = SOIL_load_OGL_texture(
                     "images/seffect/explosionsb.png",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

    if(sfxTex[1] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, sfxTex[1]);
    sfxTex[2] = SOIL_load_OGL_texture(
                     "images/seffect/explosionsc.png",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

    if(sfxTex[2] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, sfxTex[2]);
    sfxTex[3] = SOIL_load_OGL_texture(
                     "images/seffect/smoke.png",
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

    if(sfxTex[3] == 0)
        return false;

    glBindTexture(GL_TEXTURE_2D, sfxTex[3]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    cout << "\n";
    return true;
}
