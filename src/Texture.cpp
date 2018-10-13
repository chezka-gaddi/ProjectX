#include "Texture.h"

GLuint texture[7];

int LoadGLTextures()     
{
    texture[0] = SOIL_load_OGL_texture(
            "tank1.png", 
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(texture[0] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    
    
    texture[1] = SOIL_load_OGL_texture(
            "tank3.png", 
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(texture[1] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    
    texture[2] = SOIL_load_OGL_texture(
            "green.jpg",
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
    
    if(texture[2] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, texture[2]);
   
 
    texture[3] = SOIL_load_OGL_texture(
            "tree.png", 
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(texture[3] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    
    
    texture[4] = SOIL_load_OGL_texture(
            "bullet1.png", 
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(texture[4] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, texture[4]);
   
 
    texture[5] = SOIL_load_OGL_texture(
            "bullet2.png", 
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(texture[5] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    
    
    texture[6] = SOIL_load_OGL_texture(
            "heart.png", 
            SOIL_LOAD_AUTO, 
            SOIL_CREATE_NEW_ID, 
            SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA );
    
    if(texture[6] == 0)
        return false;
    
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	return true;
}

