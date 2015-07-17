//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  4x4 Matrix Class
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
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
