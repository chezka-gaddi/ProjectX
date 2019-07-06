/***************************************************************************//**
* @file Texture.cpp
* @author Chezka Gaddi
* @brief Contain the function that creates the game textures
*******************************************************************************/

#include "textureLoader.h"
#include <iostream>
using namespace std;

// Initialize texture arrays
GLuint tankTex[50];      /*!<Texture array for the tanks and their projectiles */
GLuint gameTex[20];     /*!<Texture array for game constants */
GLuint treeTex[20];     /*!<Texture array for the trees */
GLuint bushTex[20];     /*!<Texture array for the bushes */
GLuint rockTex[20];     /*!<Texture array for the rocks */
GLuint sfxTex[20];   /*<Texture array for the special effects */
GLuint waterTex[30]; /*<Texture array for water tiles */

//constants for gameplay
const std::vector<string> bImages = {"images/bush/bush.png"};
const std::vector<string> rImages = {"images/rock/rock.png"};
const std::vector<string> sImages = {"images/seffect/bTrail.png","images/seffect/bTrail2.png","images/seffect/bTrail3.png","images/seffect/bTrail4.png","images/seffect/campfire.png","images/seffect/explosiona.png","images/seffect/explosionsb.png","images/seffect/explosionsc.png","images/seffect/fire.png","images/seffect/fire2.png","images/seffect/fire3.png","images/seffect/marsh.png","images/seffect/smoke.png","images/seffect/smoke2.png","images/seffect/smoke3.png","images/seffect/smoke4.png"};
const std::vector<string> tImages = {"images/tree/tree.png","images/tree/treeS.png","images/tree/trees.png"};
const std::vector<string> gImages = {"images/UI/background.png","images/UI/green.png","images/UI/heart.png","images/UI/textbox.png","images/UI/bomb.png","images/UI/GAME.png","images/UI/hbar.png","images/misc/ammo.png","images/misc/hedgehog.png"}; 

/***************************************************************************//**
* @author Chezka Gaddi
* @modifiedby Jon McKee
* @brief LoadGLTextures
*
* Loads and saves all the textures needed for the game in texture arrays.
*******************************************************************************/
int LoadGLTextures(std::vector <std::string> images, std::vector <std::string> gameimgs,
                   std::vector <std::string> trees, std::vector <std::string> rocks, 
                   std::vector <std::string> bushes, std::vector <std::string> waters, bool quiet)
{
    //Load in the UI component texture information
    if(!quiet)
      cout << "\nLoading UI Textures:\n";
    if (!loadImageGroup(gImages, gameTex, 0, gImages.size(), quiet))
      return false;
    //Load in the SFX texture information
    if(!quiet)
        cout << "\nLoading SFX Textures:\n";
    if (!loadImageGroup(sImages, sfxTex, 0, sImages.size(), quiet))
        return false;
    //Load in the tank texture information
    if(!quiet)
        cout << "\nLoading Tank Textures:";
    if (!loadImageGroup(images, tankTex, 0, images.size(), quiet))
        return false;
    // Load in the tree texture information
    if(!quiet)
        cout << "\nLoading User Tree Textures:\n";
    if (!loadImageGroup(trees, treeTex, 0, trees.size(), quiet))
        return false;
    if(!quiet)
        cout << "\nLoading System Tree Textures:\n";
    if (!loadImageGroup(tImages, treeTex, trees.size(), trees.size() + tImages.size(), quiet))
        return false;
    // Load in the rock textures information
    if(!quiet)
        cout << "\nLoading User Rock Textures:\n";
    if (!loadImageGroup(rocks, rockTex, 0, rocks.size(), quiet))
        return false;
    if(!quiet)
        cout << "\nLoading System Rock Textures:\n";
    if (!loadImageGroup(rImages, rockTex, rocks.size(), rocks.size()+rImages.size(), quiet))
        return false;
    // Load in the bush texture information
    if(!quiet)
        cout << "\nLoading User Bush Textures:\n";
    if (!loadImageGroup(bushes, bushTex, 0, bushes.size(), quiet))
        return false;
    if(!quiet)
        cout << "\nLoading System Bush Textures:\n";
    if (!loadImageGroup(bImages, bushTex, bushes.size(), bushes.size()+bImages.size(), quiet))
        return false;
    // Load in the water textures
    if(!quiet)
      cout << "\nLoading Water Textures:\n";
    if (!loadImageGroup(waters, waterTex, 0, waters.size(), quiet))
      return false;
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    if(!quiet)
        cout << "\n";
    return true;
}

/***************************************************************************//**
* @author Jon McKee
* @brief loadImageGroup(std::vector <std::string> source, GLuint * imgArray, int start, int stop, bool quiet = false)
*
* This function takes a source array of file names, a destination Glut array to 
* store the image information, and the starting and stopping positions in the 
* the Glut array.  This information is used to correctly place system images
* after user images have been loaded.  Lastly, the quiet bool is forwarded to
* this function to respect quiet settings.
*******************************************************************************/
bool loadImageGroup(std::vector <std::string> source, GLuint * imgArray, int start, int stop, bool quiet = false){
    for(int i = start; i < stop; i++)
    {
        const char *c = source[i - start].c_str();
        if (stop == 0) //If there were no images don't error out
            return true;
        if(!quiet)
            cout << c << " ";
        imgArray[i] = SOIL_load_OGL_texture(
                        c,
                        SOIL_LOAD_AUTO,
                        SOIL_CREATE_NEW_ID,
                        SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );

        if(imgArray[i] == 0)
            return false;
        glBindTexture(GL_TEXTURE_2D, imgArray[i]);
    }
    return true;
}