//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Math Routines
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
#ifndef __SSEMATH__
#define __SSEMATH__

#include "sseInclude.hpp"

#define kEpsilon 1.1e-6f
#define COUNTELEMENTS(X) sizeof(X)/sizeof(X[0])
#define MIN(A,B) ((A < B) ? (A) : (B))
#define MAX(A,B) ((A > B) ? (A) : (B))
#define FEQUAL(X,V)	( ((V) - kEpsilon) < (X) && (X) < ((V) + kEpsilon) )
#define SSE_PI 3.14159265359
#define SSE_2PI 2*SSE_PI

// Returns a random percent between 0 - 1
#define RAND_PERCENT() ((rand() & 0x7FFF) / ((float)0x7FFF))

// Returns a random number between (and including) "min" and "max"
// Assumes "min" < "max"
#define RAND(min, max) (min + (max - min) * RAND_PERCENT())

inline bool isZero( double fValue ) 
{
    return ( fabsf(fValue) < kEpsilon );
}

inline double deg_to_rad(const double c) 
{
	return 0.01745329251994329547 * c;
}

inline double rad_to_deg(const double c)
{
	return 57.29577951308232286465 * c;
}

inline double arctan2(const double dy, const double dx)
{
	const double half_pi = SSE_PI/2;
	double a = 0;

	if (abs((long)dx) > abs((long)dy))
		a = atan (dy/dx);
	else
	{
		a = atan(dx/dy);
		if (a<0)
			a = -half_pi-a;
		else
			a = half_pi-a;
	}

	if (dx<0)
	{
		if (dy<0)
			a = a-SSE_PI;
		else
			a = a+SSE_PI;
	}

	return a;
}

#endif
