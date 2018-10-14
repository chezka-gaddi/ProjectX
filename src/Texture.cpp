/***************************************************************************//**
* @file Texture.cpp
* @author Chezka Gaddi
* @brief Contain the function that creates the game textures
*******************************************************************************/

#include "Texture.h"

// Initialize texture arrays
GLuint gameTex[8];      /*!<Texture array for the tanks and their projectiles */
GLuint tankTex[4];      /*!<Texture array for game constants */


/***************************************************************************//**
* @author Chezka Gaddi
* @brief LoadGLTextures
*
* Loads and saves all the textures needed for the game in texture arrays.
*******************************************************************************/
int LoadGLTextures()     
{
    // Load in the tank texure information
    tankTex[0] = SOIL_load_OGL_texture(
            "images/tank1.png", 
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(tankTex[0] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, tankTex[0]);
    
    
    tankTex[1] = SOIL_load_OGL_texture(
            "images/bullet1.png", 
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(tankTex[1] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, tankTex[1]);
    
    
    tankTex[2] = SOIL_load_OGL_texture(
            "images/tank2.png", 
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(tankTex[2] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, tankTex[2]);
   
 
    tankTex[3] = SOIL_load_OGL_texture(
            "images/bullet2.png", 
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(tankTex[3] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, tankTex[3]);
    
    
    // Load in constant game images
    gameTex[0] = SOIL_load_OGL_texture(
            "images/background.png",
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(gameTex[0] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, gameTex[0]);
    
    
    gameTex[1] = SOIL_load_OGL_texture(
            "images/green.png",
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(gameTex[1] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, gameTex[1]);
   
 
    gameTex[2] = SOIL_load_OGL_texture(
            "images/tree.png", 
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(gameTex[2] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, gameTex[2]);
   

    gameTex[3] = SOIL_load_OGL_texture(
            "images/rock.png", 
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(gameTex[3] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, gameTex[3]);
    

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
