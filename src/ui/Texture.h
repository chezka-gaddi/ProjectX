/***************************************************************************//**
* @file Texture.h
* @author Chezka Gaddi
* @brief Contains libraries needed for loading textures
*******************************************************************************/
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <GL/glut.h>
#include <fstream>
#include <SOIL.h>
#include <global.h>

//int LoadGLTextures(std::vector <std::string>,std::vector <std::string>);
int LoadGLTextures(std::vector <std::string> images, std::vector <std::string> gameimgs,
                   std::vector <std::string> trees, std::vector <std::string> rocks, 
                   std::vector <std::string> bushes, std::vector <std::string> waters, bool quiet = false);

#endif
