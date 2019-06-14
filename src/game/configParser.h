/***************************************************************************//**
* @file configParser.h
* @author Jonathan McKee
* @brief Contains new INI parser
*******************************************************************************/
#ifndef __parseconfig_h
#define __parseconfig_h

#include <utilities/inireader.h>
#include <string>
#include <iostream>

#include <settings/Settings.h>

bool parseConfig(Settings *);

#endif