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
#ifndef __SSEMATHLIBRARY__
#define __SSEMATHLIBRARY__

#include "sseInclude.hpp"
#include "sseMath.hpp"

//begin ssemath namespace

namespace ssemath {

#include "sseVector.hpp"
#include "sseMatrix.hpp"
#include "sseMatrix33.hpp"
#include "sseMatrix44.hpp"
#include "sseQuaternion.hpp"

typedef sseVector<int>    iVector;
typedef sseVector<float>  fVector;
typedef sseVector<double> dVector;

typedef sseMatrix<int>    iMatrix;
typedef sseMatrix<float>  fMatrix;
typedef sseMatrix<double> dMatrix;

typedef sseMatrix33<int>    iMatrix33;
typedef sseMatrix33<float>  fMatrix33;
typedef sseMatrix33<double> dMatrix33;

typedef sseMatrix44<int>    iMatrix44;
typedef sseMatrix44<float>  fMatrix44;
typedef sseMatrix44<double> dMatrix44;

typedef sseQuaternion<int>    iQuaternion;
typedef sseQuaternion<float>  fQuaternion;
typedef sseQuaternion<double> dQuaternion;

} //End ssemath namespace

#endif
