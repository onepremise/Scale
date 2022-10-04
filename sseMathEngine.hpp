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
