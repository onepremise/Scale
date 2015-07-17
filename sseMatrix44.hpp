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
#ifndef __SSEMATRIX44__
#define __SSEMATRIX44__

#include "sseMatrix.hpp"

template <class T>
class sseMatrix44: public sseMatrix<T>
{
public:
	typedef sseMatrix<T> _Mtrx;
	typedef sseMatrix44<T> _Mtrx44;

	sseMatrix44():sseMatrix<T>(4,4) {}

	_Mtrx& operator= (const _Mtrx& m)
	{
		sseErrorHandler::_ThrowIfMatrixError(!sseMatrix<T>::is3DMatrix());
		if (this != &m) 
			Copy(m);

		return (*this);
	}
	
	void Copy3x3(const _Mtrx& mA)
	{
		sseMatrix<T>::Clear();
		
		for (int i=0; i<3; i++)
			for (int j=0; j<3; j++)
				(*this)[i][j]=mA[i][j];
	}

	// Only works on homogenous coordinates
	_Mtrx44& Translate(const sseVector<float> &v)
	{
		sseErrorHandler::_ThrowIfMatrixError(!sseMatrix<T>::is4x4Matrix());

		_Mtrx44 mt;

		//Setup Translation Matrix
		/*mt[0][0]=1.0f;
		mt[1][1]=1.0f;
		mt[2][2]=1.0f;
		mt[3]=v;
		mt[3][3]=1.0f;*/

		mt.Identity();

		//mt[3]=v;
		mt[0][3]=v[0];
		mt[1][3]=v[1];
		mt[2][3]=v[2];

		//(*this)*=mt;
		(*this)=mt;
		return (*this);
	}
};

#endif
