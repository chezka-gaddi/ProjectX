/***************************************************************************//**
* @file global.h
* @author Chezka Gaddi
* @brief Contains all globals for the program
*******************************************************************************/
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <GL/glut.h>
#include <vector>

extern GLuint gameTex[20];   /*!<Texture array for the game constants */

extern GLuint treeTex[10]; /*!<Texture array for the trees */
extern GLuint bushTex[10]; /*!<Texture array for the bushes */
extern GLuint rockTex[10]; /*!<Texture array for the rocks */
extern GLuint sfxTex[20]; /*<Texture array for the special effects */
extern GLuint waterTex[20];
// Tank tex has all the tanks images for all 4 tanks.
extern GLuint tankTex[60];   /*!<Texture array for the tanks and their projectiles */

#endif
