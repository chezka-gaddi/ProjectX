/***************************************************************************//**
* @file util.h
* @author Chezka Gaddi
* @brief Contains all utility function prototypes
*******************************************************************************/
#ifndef __UTIL_H
#define __UTIL_H

#include <GL/glut.h>
#include <vector>

#include "callbacks.h"
#include "event.h"
#include "Texture.h"

void initOpenGL(int, char**, int, int, Settings);
void utilityCentral(Event *);

#endif
