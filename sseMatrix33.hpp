//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  4x4 Matrix Class
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
#ifndef __SSEMATRIX33__
#define __SSEMATRIX33__

#include "sseMatrix.hpp"

template <class T>
class sseMatrix33: public sseMatrix<T>
{
public:
	typedef sseMatrix<T> _Mtrx;
	typedef sseMatrix33<T> _Mtrx33;

	sseMatrix33() : sseMatrix<T>(3,3) { }

	// Copy Larger components into smaller
	void Copy4x4(const _Mtrx& mA)
	{
		sseErrorHandler::_ThrowIfMatrixError((mA.GetCols() != 4)||
											 (mA.GetRows() != 4));
		sseMatrix<T>::Init(3,3);

		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				(*this)[i][j]=mA[i][j];
	}
	
	_Mtrx& operator= (const _Mtrx& m)
	{
		sseErrorHandler::_ThrowIfMatrixError(!sseMatrix<T>::is3x3Matrix());
		if (this != &m) 
		{
			sseMatrix<T>::Clear();
			Copy(m);
		}
		return (*this);
	}
};

#endif
