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
GLuint waterTex[30];

const std::vector<string> bImages = {"images/bush/bush1.png","images/bush/bush2.png","images/bush/bush3.png","images/bush/bush4.png"};
const std::vector<string> mImages = {"images/misc/ammo.png","images/misc/hedgehog.png"};
const std::vector<string> rImages = {"images/rock/rockc.png","images/rock/rockb.png","images/rock/rock.png"};
const std::vector<string> sImages = {"images/seffect/bTrail.png","images/seffect/bTrail2.png","images/seffect/bTrail3.png","images/seffect/bTrail4.png","images/seffect/campfire.png","images/seffect/explosiona.png","images/seffect/explosionsb.png","images/seffect/explosionsc.png","images/seffect/fire.png","images/seffect/fire2.png","images/seffect/fire3.png","images/seffect/marsh.png","images/seffect/smoke.png","images/seffect/smoke2.png","images/seffect/smoke3.png","images/seffect/smoke4.png"};
const std::vector<string> tImages = {"images/tree/tree.png","images/tree/treeb.png","images/tree/treec.png","images/tree/treed.png","images/tree/treeS.png","images/tree/trees.png"};
const std::vector<string> gImages = {"images/UI/background.png","images/UI/green.png","images/misc/hedgehog.png","images/misc/hedgehog.png","images/UI/heart.png","images/UI/textbox.png","images/UI/bomb.png","images/UI/GAME.png","images/UI/hbar.png","images/misc/ammo.png"}; 

/***************************************************************************//**
* @author Chezka Gaddi
* @brief LoadGLTextures
*
* Loads and saves all the textures needed for the game in texture arrays.
*******************************************************************************/
int LoadGLTextures(std::vector <std::string> images, std::vector <std::string> gameimgs,
                   std::vector <std::string> trees, std::vector <std::string> rocks, 
                   std::vector <std::string> bushes, std::vector <std::string> waters)
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

        if(tankTex[i] == 0){
          return false;
        }

        glBindTexture(GL_TEXTURE_2D, tankTex[i]);
    }

    cout << "\nLoading Tree Textures:\n";
    // Load in the tree texure information
    for( int i = 0; i < tImages.size(); i++ )
    {
        const char *c = tImages[i].c_str();
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
    cout << "\nLoading User Tree Textures:\n";
    // Load in the tree texure information
    for( int i = tImages.size(); i < trees.size()+tImages.size(); i++ )
    {
        const char *c = trees[i-tImages.size()].c_str();
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
    cout << "\nLoading Rock Textures:\n";
    // Load in the rock texures information
    for( int i = 0; i < rImages.size(); i++ )
    {
        const char *c = rImages[i].c_str();
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
    cout << "\nLoading User Rock Textures:\n";
    // Load in the rock texures information
    for( int i = rImages.size(); i < rocks.size()+rImages.size(); i++ )
    {
        const char *c = rocks[i-rImages.size()].c_str();
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
    for( int i = 0; i < bImages.size(); i++ )
    {
        const char *c = bImages[i].c_str();
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
    cout << "\nLoading User Bush Textures:\n";
    // Load in the bush texure information
    for( int i = bImages.size(); i < bushes.size()+bImages.size(); i++ )
    {
        const char *c = bushes[i-bImages.size()].c_str();
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

    cout << "\nLoading Water Textures:\n";
    // Load in the bush texure information
    for( int i = 0; i < waters.size(); i++ )
    {
        const char *c = waters[i].c_str();
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


    cout << "\nLoading UI Textures:\n";
    // Load in constant game images
    for( int i = 0; i < gImages.size(); i++ )
    {
        const char *c = gImages[i].c_str();
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


    cout << "\nLoading SFX Textures:\n";
    // Load in sfx game images
    for(int i=0; i < sImages.size(); i++)
    {
    const char *c = sImages[i].c_str();
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
    cout << "\n";
    return true;
}
