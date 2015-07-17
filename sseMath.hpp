//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Math Routines
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
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
