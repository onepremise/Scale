//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Includes
//
// Notes:
//
//    Y+
//    |
//    |__ X+
//   /
//  Z+ 
//
// License:
//
// Licensed under the Apache License, Version 2.0 
// (the "License"); you may not use this file except in 
// compliance with the License. You may obtain a copy of 
// the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in 
// writing, software distributed under the License is 
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing 
// permissions and limitations under the License.
//
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
#include <GL/gl.h>  // Header File For The OpenGL32 Library
#include <GL/glu.h> // Header File For The GLu32 Library
#include <GL/glut.h>
#include <SDL2/SDL.h>

using namespace std;

#include "sseErrorHandler.hpp"
#include "sseLog.h"

typedef basic_string<char> String;

#endif
