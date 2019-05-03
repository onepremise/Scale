//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Includes
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//=========================================================
#ifndef __SSEINCLUDE__
#define __SSEINCLUDE__

#pragma warning(disable:4786)

#ifdef _WINDOWS
#include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <iterator>
#include <iomanip>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <GL/glut.h>
#endif

using namespace std;

#include <GLFW/glfw3.h>

//#include "SDL.h"                                           // The SDL Header File
#include "sseErrorHandler.hpp"
#include "sseLog.h"

typedef basic_string<char> String;

#endif
