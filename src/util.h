#ifndef __UTIL_H
#define __UTIL_H

#include <GL/glut.h>
#include <vector>

#include "callbacks.h"
#include "event.h"
#include "Texture.h"
//#include "game.h"

void initOpenGL(int, char**, int, int, gameMode);
void utilityCentral(int, char**, Event *);

#endif
