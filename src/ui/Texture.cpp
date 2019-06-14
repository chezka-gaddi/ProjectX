/***************************************************************************//**
* @file Texture.cpp
* @author Chezka Gaddi
* @brief Contain the function that creates the game textures
*******************************************************************************/

#include "Texture.h"
#include <iostream>
using namespace std;

// Initialize texture arrays
GLuint tankTex[80];      /*!<Texture array for the tanks and their projectiles */
GLuint gameTex[20];     /*!<Texture array for game constants */
GLuint treeTex[20];     /*!<Texture array for the trees */
GLuint bushTex[20];     /*!<Texture array for the bushes */
GLuint rockTex[20];     /*!<Texture array for the rocks */
GLuint sfxTex[20];   /*<Texture array for the special effects */
GLuint waterTex[30]; /*<Texture array for water tiles */

const std::vector<string> bImages = {"images/bush/bush.png"};
const std::vector<string> rImages = {"images/rock/rock.png"};
const std::vector<string> sImages = {"images/seffect/bTrail.png","images/seffect/bTrail2.png","images/seffect/bTrail3.png","images/seffect/bTrail4.png","images/seffect/campfire.png","images/seffect/explosiona.png","images/seffect/explosionsb.png","images/seffect/explosionsc.png","images/seffect/fire.png","images/seffect/fire2.png","images/seffect/fire3.png","images/seffect/marsh.png","images/seffect/smoke.png","images/seffect/smoke2.png","images/seffect/smoke3.png","images/seffect/smoke4.png"};
const std::vector<string> tImages = {"images/tree/tree.png","images/tree/treeS.png","images/tree/trees.png"};
const std::vector<string> gImages = {"images/UI/background.png","images/UI/green.png","images/UI/heart.png","images/UI/textbox.png","images/UI/bomb.png","images/UI/GAME.png","images/UI/hbar.png","images/misc/ammo.png","images/misc/hedgehog.png"}; 

/***************************************************************************//**
* @author Chezka Gaddi
* @brief LoadGLTextures
*
* Loads and saves all the textures needed for the game in texture arrays.
*******************************************************************************/
int LoadGLTextures(std::vector <std::string> images, std::vector <std::string> gameimgs,
                   std::vector <std::string> trees, std::vector <std::string> rocks, 
                   std::vector <std::string> bushes, std::vector <std::string> waters, bool quiet)
{
    // Load in the tank texure information
    if(!quiet)
        cout << "\nLoading Tank Textures:";
    for( unsigned int i = 0; i < images.size(); i++ )
    {
        const char *c = images[i].c_str();
        if(!quiet)
            (i%5 == 0) ? cout << "\n" << c << "  " : cout << c << "  ";
        tankTex[i] = SOIL_load_OGL_texture(
                         c,
                         SOIL_LOAD_AUTO,
                         SOIL_CREATE_NEW_ID,
                         SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

        if(tankTex[i] == 0){
          return false;
        }

        glBindTexture(GL_TEXTURE_2D, tankTex[i]);
    }

    if(!quiet)
    cout << "\nLoading User Tree Textures:\n";
    // Load in the tree texure information
    for( unsigned int i = 0; i < trees.size(); i++ )
    {
        const char *c = trees[i].c_str();
        if(!quiet)
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
    if(!quiet)
        cout << "\nLoading System Tree Textures:\n";
    // Load in the tree texure information
    for( unsigned int i = trees.size(); i < trees.size()+tImages.size(); i++ )
    {
        const char *c = tImages[i-trees.size()].c_str();
        if(!quiet)
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
    if(!quiet)
        cout << "\nLoading User Rock Textures:\n";
    // Load in the rock texures information
    for( unsigned int i = 0; i < rocks.size(); i++ )
    {
        const char *c = rocks[i].c_str();
        if(!quiet)
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
    if(!quiet)
        cout << "\nLoading System Rock Textures:\n";
    // Load in the rock texures information
    for( unsigned int i = rocks.size(); i < rocks.size()+rImages.size(); i++ )
    {
        const char *c = rImages[i-rocks.size()].c_str();
        if(!quiet)
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
    if(!quiet)
        cout << "\nLoading User Textures:\n";
    // Load in the bush texure information
    for( unsigned int i = 0; i < bushes.size(); i++ )
    {
        const char *c = bushes[i].c_str();
        if(!quiet)
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
    if(!quiet)
        cout << "\nLoading System Bush Textures:\n";
    // Load in the bush texure information
    for( unsigned int i = bushes.size(); i < bushes.size()+bImages.size(); i++ )
    {
        const char *c = bImages[i-bushes.size()].c_str();
        if(!quiet)
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
    if(!quiet)
      cout << "\nLoading Water Textures:\n";
    // Load in the bush texure information
    for( unsigned int i = 0; i < waters.size(); i++ )
    {
        const char *c = waters[i].c_str();
        if(!quiet)
          cout << c << "  ";
        waterTex[i] = SOIL_load_OGL_texture(
                     c,
                     SOIL_LOAD_AUTO,
                     SOIL_CREATE_NEW_ID,
                     SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

        if(waterTex[i] == 0)
        return false;

        glBindTexture(GL_TEXTURE_2D, bushTex[i]);
    }
    if(!quiet)
      cout << "\nLoading UI Textures:\n";
    // Load in constant game images
    for( unsigned int i = 0; i < gImages.size(); i++ )
    {
        const char *c = gImages[i].c_str();
        if(!quiet)
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
    if(!quiet)
    cout << "\nLoading SFX Textures:\n";
    // Load in sfx game images
    for(unsigned int i=0; i < sImages.size(); i++)
    {
    const char *c = sImages[i].c_str();
    if(!quiet)
    cout << c << " ";
    sfxTex[i] = SOIL_load_OGL_texture(
                    c,
                    SOIL_LOAD_AUTO,
                    SOIL_CREATE_NEW_ID,
                    SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

    if(sfxTex[i] == 0)
        return false;
    glBindTexture(GL_TEXTURE_2D, sfxTex[i]);
    }
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    if(!quiet)
    cout << "\n";
    return true;
}
