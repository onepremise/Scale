//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Vector Algebra Library
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//  02/01/2005    Added UNIT Vectors      JAH       
//=========================================================
#include "sseVector.hpp"

const sseVector<float> NEG_UNIT_X3( -1,  0,  0 );
const sseVector<float> NEG_UNIT_X4( -1,  0,  0, 0 );

const sseVector<float> NEG_UNIT_Y3(  0, -1,  0 );
const sseVector<float> NEG_UNIT_Y4(  0, -1,  0, 0 );

const sseVector<float> NEG_UNIT_Z3(  0,  0, -1 );
const sseVector<float> NEG_UNIT_Z4(  0,  0, -1, 0 );

const sseVector<float> UNIT_SCALE3(1, 1, 1);
const sseVector<float> UNIT_SCALE4(1, 1, 1, 0);
