/***************************************************************************//**
* @file util.h
* @author Chezka Gaddi
* @brief Contains all utility function prototypes
*******************************************************************************/
#ifndef __UTIL_H
#define __UTIL_H

#include <GL/glut.h>
#include <vector>

#include <ui/callbacks.h>
#include <ui/event.h>
#include <ui/Texture.h>

void initOpenGL(int, char**, int, int, Settings*);
void utilityCentral(Event *);

#endif
