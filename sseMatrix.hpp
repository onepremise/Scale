//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Matrix Algebra Library
//
//  Notes:
//
//  float matrix[16] = { a, b, c, d, 
//  	                 e, f, g, h, 
//  	                 i, j, k,l, 
//  	                 m, n, o, p };
//  
//  |a e i m|
//  |b f j n|
//  |c g k o|
//  |d h l p|
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
#ifndef __SSEMATRIX__
#define __SSEMATRIX__

#include "sseInclude.hpp"

template <class T> class sseVector;

template <class T>
class sseMatrix
{
public:
	typedef sseMatrix<T> _Mtrx;
	//Default Matrix
	sseMatrix()
	{ 
		m_vectors=NULL;
		Init(3,3);
	}
	
	sseMatrix(T *pOpenGLMatrix)
	{
		m_vectors=NULL;
		Copy(pOpenGLMatrix);
	}

	//Copy Contstructor
	sseMatrix(const _Mtrx& m)
	{
		m_vectors=NULL;
		Copy(m);
	}

	//Create Matrix with dimensions
	sseMatrix(int iRows, int iCols)
	{
		m_vectors=NULL;
		Init(iRows, iCols);
	}

	~sseMatrix()
	{
		if (m_vectors!=NULL)
			delete [] m_vectors;
	}

	//Initialize the Matrix for use
	void Init(int iRows, int iCols)
	{
		m_iMaxRows=iRows;
		m_iMaxCols=iCols;

		sseErrorHandler::_ThrowIfMatrixSizeError(m_iMaxRows, m_iMaxCols);

		if (m_vectors!=NULL)
			delete [] m_vectors;

		m_vectors=new sseVector<T>[m_iMaxRows];

		if (m_iMaxRows==3) 
		{
			m_vectors[0]=sseVector<T>(m_iMaxCols);
			m_vectors[1]=sseVector<T>(m_iMaxCols);
			m_vectors[2]=sseVector<T>(m_iMaxCols);
		}
		else if (m_iMaxRows==4)
		{
			m_vectors[0]=sseVector<T>(m_iMaxCols);
			m_vectors[1]=sseVector<T>(m_iMaxCols);
			m_vectors[2]=sseVector<T>(m_iMaxCols);
			m_vectors[3]=sseVector<T>(m_iMaxCols);
		}
		else
		{
			for (int i=0; i<m_iMaxRows; i++)
				m_vectors[i]=sseVector<T>(m_iMaxCols);
		}
	}

	// Clear Matrix
	virtual void Clear()
	{
		if (m_iMaxRows==1) 
		{
			m_vectors[0].Clear();
		}
		else if (m_iMaxRows==2) 
		{
			m_vectors[0].Clear();
			m_vectors[1].Clear();
		}
		else if (m_iMaxRows==3) 
		{
			m_vectors[0].Clear();
			m_vectors[1].Clear();
			m_vectors[2].Clear();
		}
		else if (m_iMaxRows==4)
		{
			m_vectors[0].Clear();
			m_vectors[1].Clear();
			m_vectors[2].Clear();
			m_vectors[3].Clear();
		}
		else
		{
			for (int i=0; i<GetRows(); i++)
				(*this)[i].Clear();
		}
	}

	void Copy(int size, const T *pOpenGLMatrix)
	{
		int c=0;
		
		sseErrorHandler::_ThrowIfMatrixError(pOpenGLMatrix==NULL);
		
		Init(size, size);

		if (m_iMaxRows==2) 
		{
			m_vectors[0][0]=pOpenGLMatrix[c++];
			m_vectors[0][1]=pOpenGLMatrix[c++];

			m_vectors[1][0]=pOpenGLMatrix[c++];
			m_vectors[1][1]=pOpenGLMatrix[c++];
		}
		else if (m_iMaxRows==3) 
		{
			m_vectors[0][0]=pOpenGLMatrix[c++];
			m_vectors[0][1]=pOpenGLMatrix[c++];
			m_vectors[0][2]=pOpenGLMatrix[c++];

			m_vectors[1][0]=pOpenGLMatrix[c++];
			m_vectors[1][1]=pOpenGLMatrix[c++];
			m_vectors[1][2]=pOpenGLMatrix[c++];

			m_vectors[2][0]=pOpenGLMatrix[c++];
			m_vectors[2][1]=pOpenGLMatrix[c++];
			m_vectors[2][2]=pOpenGLMatrix[c++];
		}
		else if (m_iMaxRows==4)
		{
			m_vectors[0][0]=pOpenGLMatrix[c++];
			m_vectors[0][1]=pOpenGLMatrix[c++];
			m_vectors[0][2]=pOpenGLMatrix[c++];
			m_vectors[0][3]=pOpenGLMatrix[c++];
			m_vectors[1][0]=pOpenGLMatrix[c++];
			m_vectors[1][1]=pOpenGLMatrix[c++];
			m_vectors[1][2]=pOpenGLMatrix[c++];
			m_vectors[1][3]=pOpenGLMatrix[c++];
			m_vectors[2][0]=pOpenGLMatrix[c++];
			m_vectors[2][1]=pOpenGLMatrix[c++];
			m_vectors[2][2]=pOpenGLMatrix[c++];
			m_vectors[2][3]=pOpenGLMatrix[c++];
			m_vectors[3][0]=pOpenGLMatrix[c++];
			m_vectors[3][1]=pOpenGLMatrix[c++];
			m_vectors[3][2]=pOpenGLMatrix[c++];
			m_vectors[3][3]=pOpenGLMatrix[c++];
		}
		else
		{
			for (int i=0; i<m_iMaxRows; i++)
			{
				for (int j=0; j<m_iMaxCols; j++)
				{
						m_vectors[i][j]=pOpenGLMatrix[c];
						c++;
				}
			}
		}
	}

	//Copy Matrix
	void Copy(const T *pOpenGLMatrix)
	{
		Copy(4, pOpenGLMatrix);
	}
	
	//Copy Matrix
	void Copy(const _Mtrx& m)
	{
		sseErrorHandler::_ThrowIfMatrixSizeError(m.GetRows(), m.GetCols());

		if (m_iMaxRows!=m.GetRows() || m_iMaxCols!=m.GetCols())
		{
			m_iMaxRows=m.GetRows();
			m_iMaxCols=m.GetCols();

			if (m_vectors!=NULL)
				delete [] m_vectors;

			m_vectors=new sseVector<T>[m_iMaxRows];
		} else if (m_vectors==NULL)
		{
			m_vectors=new sseVector<T>[m_iMaxRows];
		}

		if (m_iMaxRows==3) 
		{
			m_vectors[0]=m[0];
			m_vectors[1]=m[1];
			m_vectors[2]=m[2];
		}
		else if (m_iMaxRows==4)
		{
			m_vectors[0]=m[0];
			m_vectors[1]=m[1];
			m_vectors[2]=m[2];
			m_vectors[3]=m[3];
		}
		else
		{
			for (int i=0; i<m_iMaxRows; i++)
				m_vectors[i]=m[i];
		}
	}

	//Get Component
	T& operator() (int iRow, int iCol)
	{
		return m_vectors[iRow][iCol];
	}

	//Get Vector
	sseVector<T>& operator[] (int iRow)
	{
		return m_vectors[iRow];
	}

	//Get Constant Vector
	const sseVector<T>& operator[] (int iRow) const
	{
		return m_vectors[iRow];
	}
	
	//Assign Matrix
	virtual _Mtrx& operator= (const T *pOpenGLMatrix)
	{
		Copy(pOpenGLMatrix);
		
		return (*this);
	}	

	//Assign Matrix
	virtual _Mtrx& operator= (const _Mtrx& m)
	{
		if (this != &m) 
		{
			Copy(m);
		}
		return (*this);
	}

	//Equality Check
	virtual bool operator== (const _Mtrx& m)
	{
		return this->equals(m);
	}

	//InEquality Check
	virtual bool operator!= (const _Mtrx& m)
	{
		return !this->equals(m);
	}

	//Matrix Addition
	friend _Mtrx operator+ (const _Mtrx& mA, const _Mtrx& mB)
	{
		mA.isSameSizeAs(mB);
		_Mtrx m_sum(mA.GetRows(), mA.GetCols());

		for (int i=0; i<m_sum.m_iMaxRows; i++)
			for (int j=0; j<m_sum.m_iMaxCols; j++)
				m_sum[i][j]=(mA[i][j]+mB[i][j]);
		
		return m_sum;
	}

	//Matrix Subtraction
	friend _Mtrx operator- (const _Mtrx& mA, const _Mtrx& mB)
	{
		mA.isSameSizeAs(mB);
		_Mtrx m_sum(mA.GetRows(), mA.GetCols());

		for (int i=0; i<m_sum.m_iMaxRows; i++)
			for (int j=0; j<m_sum.m_iMaxCols; j++)
				m_sum[i][j]=(mA[i][j]-mB[i][j]);
		
		return m_sum;
	}
	
	friend sseVector<T> operator* (const _Mtrx& mA, const sseVector<T>& vB)
	{
		sseErrorHandler::_ThrowIfMatrixError((mA.GetCols() != vB.size()));
		sseVector<T> m_product(vB.size());

		for (int r=0; r<mA.m_iMaxRows; r++)
			for (int c=0; c<mA.m_iMaxCols; c++)
					if(c<vB.size())
						m_product[r]+=(mA[r][c]*vB[c]);

		return m_product;
	}	

	//Matrix Multiplication
	friend _Mtrx operator* (const _Mtrx& mA, const _Mtrx& mB)
	{
		sseErrorHandler::_ThrowIfMatrixError((mA.GetCols() != mB.GetRows()));
		_Mtrx m_product(mA.m_iMaxRows, mB.m_iMaxCols);

		if (mA.m_iMaxRows==4) 
		{
			m_product[0][0] = mA[0][0]*mB[0][0] + mA[0][1]*mB[1][0] + mA[0][2]*mB[2][0] + mA[0][3]*mB[3][0];
			m_product[0][1] = mA[0][0]*mB[0][1] + mA[0][1]*mB[1][1] + mA[0][2]*mB[2][1] + mA[0][3]*mB[3][1];
			m_product[0][2] = mA[0][0]*mB[0][2] + mA[0][1]*mB[1][2] + mA[0][2]*mB[2][2] + mA[0][3]*mB[3][2];
			m_product[0][3] = mA[0][0]*mB[0][3] + mA[0][1]*mB[1][3] + mA[0][2]*mB[2][3] + mA[0][3]*mB[3][3];

			m_product[1][0] = mA[1][0]*mB[0][0] + mA[1][1]*mB[1][0] + mA[1][2]*mB[2][0] + mA[1][3]*mB[3][0];
			m_product[1][1] = mA[1][0]*mB[0][1] + mA[1][1]*mB[1][1] + mA[1][2]*mB[2][1] + mA[1][3]*mB[3][1];
			m_product[1][2] = mA[1][0]*mB[0][2] + mA[1][1]*mB[1][2] + mA[1][2]*mB[2][2] + mA[1][3]*mB[3][2];
			m_product[1][3] = mA[1][0]*mB[0][3] + mA[1][1]*mB[1][3] + mA[1][2]*mB[2][3] + mA[1][3]*mB[3][3];

			m_product[2][0] = mA[2][0]*mB[0][0] + mA[2][1]*mB[1][0] + mA[2][2]*mB[2][0] + mA[2][3]*mB[3][0];
			m_product[2][1] = mA[2][0]*mB[0][1] + mA[2][1]*mB[1][1] + mA[2][2]*mB[2][1] + mA[2][3]*mB[3][1];
			m_product[2][2] = mA[2][0]*mB[0][2] + mA[2][1]*mB[1][2] + mA[2][2]*mB[2][2] + mA[2][3]*mB[3][2];
			m_product[2][3] = mA[2][0]*mB[0][3] + mA[2][1]*mB[1][3] + mA[2][2]*mB[2][3] + mA[2][3]*mB[3][3];

			m_product[3][0] = mA[3][0]*mB[0][0] + mA[3][1]*mB[1][0] + mA[3][2]*mB[2][0] + mA[3][3]*mB[3][0];
			m_product[3][1] = mA[3][0]*mB[0][1] + mA[3][1]*mB[1][1] + mA[3][2]*mB[2][1] + mA[3][3]*mB[3][1];
			m_product[3][2] = mA[3][0]*mB[0][2] + mA[3][1]*mB[1][2] + mA[3][2]*mB[2][2] + mA[3][3]*mB[3][2];
			m_product[3][3] = mA[3][0]*mB[0][3] + mA[3][1]*mB[1][3] + mA[3][2]*mB[2][3] + mA[3][3]*mB[3][3];
		} else {
			for (int i=0; i<mB.m_iMaxRows; i++)
				for (int j=0; j<mA.m_iMaxCols; j++)
					for (int k=0; k<mA.m_iMaxCols; k++)
						if(i<mA.m_iMaxRows && j<mB.m_iMaxCols)
							m_product[i][j]+=(mA[i][k]*mB[k][j]);
		}

		return m_product;
	}

	//Multiply by scalar
	friend _Mtrx operator* (const _Mtrx& mA, const T value)
	{
		_Mtrx m_product(mA.m_iMaxRows, mA.m_iMaxCols);

		for (int i=0; i<m_product.m_iMaxRows; i++)
			for (int j=0; j<m_product.m_iMaxCols; j++)
					m_product[i][j]=mA[i][j]*value;
		
		return m_product;
	}

	//divide by scalar
	friend _Mtrx operator/ (const _Mtrx& mA, const T value)
	{
		_Mtrx m_div(mA.m_iMaxRows, mA.m_iMaxCols);

		for (int i=0; i<m_div.m_iMaxRows; i++)
			for (int j=0; j<m_div.m_iMaxCols; j++)
				m_div[i][j]=mA[i][j]/value;
		
		return m_div;
	}

	//Matrix Addition
	_Mtrx& operator+= (const _Mtrx& m)
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				m_vectors[i][j]=(m_vectors[i][j]+m[i][j]);

		return (*this);
	}

	//Matrix Subtraction
	_Mtrx& operator-= (const _Mtrx& m)
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				m_vectors[i][j]=(m_vectors[i][j]-m[i][j]);

		return (*this);
	}

	//Matrix Multiplication
	_Mtrx& operator*= (const _Mtrx& m)
	{
		*this=(*this*m);
		return (*this);
	}

	//Multiply by scalar
	_Mtrx& operator*= (const T value)
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				m_vectors[i][j]=m_vectors[i][j]*value;
		return (*this);
	}

	//Divide by scalar
	_Mtrx& operator/= (const T value)
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				m_vectors[i][j]=m_vectors[i][j]/value;
		return (*this);
	}

	// Transpose
	friend _Mtrx operator~ (const	_Mtrx& m)
	{
		_Mtrx m_trans(m.GetRows(), m.GetCols());
		for (int i=0; i<m.m_iMaxRows; i++)
			for (int j=0; j<m.m_iMaxCols; j++)
				m_trans[j][i] = m[i][j];
		return m_trans;
	}

	// Get a sub Matrix Determinant (Minor)
	T Minor(int iRow, int iCol) const
	{
		sseErrorHandler::_ThrowIfMatrixError(!isSquare());
		sseErrorHandler::_ThrowIfMatrixError(m_iMaxRows <= 2);

		_Mtrx m(m_iMaxRows-1,m_iMaxCols-1);

		for (int i=0,i2=0; i<m_iMaxRows; i++)
		{
			if (i==iRow) continue;
			for (int j=0,j2=0; j<m_iMaxCols; j++)
			{
				if (j==iCol) continue;
				m[i2][j2]=(*this)[i][j];
				j2++;
			}
			i2++;
		}
		return m.Determinant();
	}

	// Cofactor to find final determinant of a given matrix
	T Cofactor(int iRow, int iCol) const
	{
		sseErrorHandler::_ThrowIfMatrixError(!isSquare());
		T neg=-1;
		T rc=(iRow+iCol);
		T minor=Minor(iRow,iCol);
		return (pow(neg,rc)*minor);
	}

	// Get Determinant of a given matrix
	T Determinant(void) const
	{
		sseErrorHandler::_ThrowIfMatrixError(!isSquare());
		T d=0;
		if (m_iMaxRows == 2)
			d=(((*this)[0][0]*(*this)[1][1])-((*this)[1][0]*(*this)[0][1]));
		else for (int j=0; j<m_iMaxCols; j++)
			d+=(*this)[0][j]*Cofactor(0,j);
		return d;
	}

	// Adjoint matrix = Transpose of cofactor matrix
	_Mtrx Adjoint() const
	{
		sseErrorHandler::_ThrowIfMatrixError(!isSquare());
		_Mtrx m(m_iMaxRows,m_iMaxCols);
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				m[j][i]=Cofactor(i,j);
		return m;
	}

	// Inverse matrix= Adjoint matrix/determinant
	_Mtrx Inverse() const
	{
		sseErrorHandler::_ThrowIfMatrixError(!isSquare());
		sseErrorHandler::_ThrowIfMatrixError(isSingular());
		return(Adjoint()/Determinant());
	}

	_Mtrx Transpose()
	{
	   _Mtrx m(m_iMaxRows,m_iMaxCols);

		if (m_iMaxRows==3) {
			m[0][0] = m_vectors[0][0];
			m[0][1] = m_vectors[1][0];
			m[0][2] = m_vectors[2][0];

			m[1][0] = m_vectors[0][1];
			m[1][1] = m_vectors[1][1];
			m[1][2] = m_vectors[2][1];

			m[2][0] = m_vectors[0][2];
			m[2][1] = m_vectors[1][2];
			m[2][2] = m_vectors[2][2];
		} else if (m_iMaxRows==4) {
			m[0][0] = m_vectors[0][0];
			m[0][1] = m_vectors[1][0];
			m[0][2] = m_vectors[2][0];
			m[0][3] = m_vectors[3][0];

			m[1][0] = m_vectors[0][1];
			m[1][1] = m_vectors[1][1];
			m[1][2] = m_vectors[2][1];
			m[1][3] = m_vectors[3][1];

			m[2][0] = m_vectors[0][2];
			m[2][1] = m_vectors[1][2];
			m[2][2] = m_vectors[2][2];
			m[2][3] = m_vectors[3][2];

			m[3][0] = m_vectors[0][3];
			m[3][1] = m_vectors[1][3];
			m[3][2] = m_vectors[2][3];
			m[3][3] = m_vectors[3][3];
		} else {
		   for ( int i=0 ; i<m_iMaxCols ; i++ ){
			  for ( int j=0 ; j<m_iMaxRows ; j++ )
		 		m[i][j]=m_vectors[j][i];
		   }
		}

	   return m;
	}

	// Set Matrix to identity if rows/cols equal
	void Identity(void)
	{
		sseErrorHandler::_ThrowIfMatrixError(!isSquare());
		Clear();

		if (m_iMaxRows>=2) 
		{
			m_vectors[0][0] = 1;
			m_vectors[0][1] = 0.0f;
			m_vectors[0][2] = 0.0f;
			m_vectors[0][3] = 0.0f;

			m_vectors[1][0] = 0.0f;
			m_vectors[1][1] = 1;
			m_vectors[1][2] = 0.0f;
			m_vectors[1][3] = 0.0f;
		}

		if (m_iMaxRows>=3) 
		{
			m_vectors[2][0] = 0.0f;
			m_vectors[2][1] = 0.0f;
			m_vectors[2][2] = 1;
			m_vectors[2][3] = 0.0f;

			m_vectors[3][0] = 0.0f;
			m_vectors[3][1] = 0.0f;
			m_vectors[3][2] = 0.0f;
			m_vectors[3][3] = 1.0f;
		}

		for (int i=0; i<GetRows(); i++)
			(*this)[i][i]=1;
	}

	// The norm of a mathematical object is a quantity that 
	// in some (possibly abstract) sense describes the length, 
	// size, or extent of the object.
	// L2 Norm
	// The L2-norm is also called the Euclidean Norm
	T L2Norm()
	{
		sseErrorHandler::_ThrowIfMatrixError(!isSquare());
		T Nrm;
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				Nrm+=pow((*this)[i][i],2);
		return Nrm;
	}

	// Get Trace
	// The trace of the matrix is the sum of the main diagonal
	T Trace(void)
	{
		sseErrorHandler::_ThrowIfMatrixError(!isSquare());
		T sum=0;
		for (int i=0; i<GetRows(); i++)
			sum+=(*this)[i][i];
		return sum;
	}

	_Mtrx& Scaling( const sseVector<T>& v )
	{
		if (v.size()>=2) 
		{
			m_vectors[0][0] = v[0];
			m_vectors[0][1] = 0.0f;
			m_vectors[0][2] = 0.0f;
			m_vectors[0][3] = 0.0f;

			m_vectors[1][0] = 0.0f;
			m_vectors[1][1] = v[1];
			m_vectors[1][2] = 0.0f;
			m_vectors[1][3] = 0.0f;
		}

		if (v.size()>=3) 
		{
			m_vectors[2][0] = 0.0f;
			m_vectors[2][1] = 0.0f;
			m_vectors[2][2] = v[2];
			m_vectors[2][3] = 0.0f;

			m_vectors[3][0] = 0.0f;
			m_vectors[3][1] = 0.0f;
			m_vectors[3][2] = 0.0f;
			m_vectors[3][3] = 1.0f;
		}

		if (v.size()>=4) 
		{
			m_vectors[3][0] = 0.0f;
			m_vectors[3][1] = 0.0f;
			m_vectors[3][2] = 0.0f;
			m_vectors[3][3] = v[3];

			m_vectors[4][0] = 0.0f;
			m_vectors[4][1] = 0.0f;
			m_vectors[4][2] = 0.0f;
			m_vectors[4][3] = 1.0f;
		}

		for (int i=4; i<v.size(); i++)
			(*this)[i][i]=v[i];

		return *this;
	} 

	//Check if Vector
	//A row vector is a matrix containing a single row
	bool isVector() const
	{
		return(m_iMaxRows==1 && m_iMaxCols>1);
	}

	// Check if Null
	// A zero, or null, matrix is one where every element is zero
	bool isNull() const
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				if (m_vectors[i][j] != 0) return false;
		return true;
	}

	// Check if matrix square
	// A square matrix is one where the number of rows and columns are equal
	bool isSquare() const
	{
		return (m_iMaxRows == m_iMaxCols);
	}

	bool isSingular() const
	{
		return (Determinant()==0);
	}

	// check if Diagonal
	// diagonal matrix is a square matrix in which all the elements are 
	// zero except for the elements on the leading diagonal
	bool isDiagonal() const
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				if (i==j && m_vectors[i][j]==0) return false;
				else if (i!=j && m_vectors[i][j]!=0) return false;
		return true;
	}

	// Check if Unit
	// A unit matrix is a square matrix in which all the elements on 
	// the leading diagonal are 1, and all the other elements are 0
	bool isUnit() const
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				if (i==j && m_vectors[i][j]!=1) return false;
				else if (i!=j && m_vectors[i][j]!=0) return false;
		return true;
	}

	// Check if symmetric
	// A symmetrix matrix is a square matrix where a.ij==a.ji for all elements.
	bool isSymmetric() const
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				if (m_vectors[i][j]!=m_vectors[j][i]) return false;
		return true;
	}

	// Check if Skew Symmetric
	// A skew symmetrix matrix is a square matrix where a.ij==-a.ji for all 
	// elements. Ie, the matrix is anti-symmetrical about the leading diagonal.
	// This of course requires that elements along the diagonal must be zero.
	bool isSkewSymmetric() const
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				if (i==j && (m_vectors[i][j]!=0)) return false;
				else if (i!=j && (m_vectors[i][j]!=-m_vectors[j][i]))
					return false;
		return true;
	}

	// Check if Orthagonal
	// An orthogonal matrix is a square matrix which produces a unit matrix 
	// if it is multiplied by its own transpose.
	bool isOrthogonal() const
	{
		if(((*this)*(~(*this))).isUnit()) return true;
		return false;
	}

	// Compare sizes
	void isSameSizeAs(const _Mtrx& m) const
	{
		sseErrorHandler::_ThrowIfMatrixError((m_iMaxRows != m.GetRows()));
		sseErrorHandler::_ThrowIfMatrixError((m_iMaxCols != m.GetCols()));
	}

	String toString(const char *tag="") const
	{
		std::ostringstream oss;

		oss<<tag;

		oss<<" Matrix:"<<endl;

		for (int i=0; i<m_iMaxRows; i++) {
			for (int j=0; j<m_iMaxCols; j++) {
				oss << std::setw(15) << (double)m_vectors[i][j]<<" ";
			}
			oss<<endl;
		}

		return oss.str();
	}

	bool equals(const _Mtrx& m)
	{
		for (int i=0; i<m_iMaxRows; i++)
			if (m_vectors[i]!=m[i]) 
				return false;

		return true;
	}

public:
	const int GetRows() const {return m_iMaxRows;}
	const int GetCols() const {return m_iMaxCols;}

// 3D routines
public:
	bool is3DMatrix()
	{
		return (is3x3Matrix() || is4x4Matrix());
	}

	bool is3x3Matrix()
	{
		return ((m_iMaxCols == 3) && (m_iMaxRows == 3));
	}

	bool is4x4Matrix()
	{
		return ((m_iMaxCols == 4) && (m_iMaxRows == 4));
	}
	
	void SetRows(const sseVector<T>& right, const sseVector<T>& up, const sseVector<T>& view)
	{
		this->SetRight(right);
		this->SetUpVector(up);
		this->SetView(view);
	}
	
	void SetRight(const sseVector<T>& row)
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());
		
		(*this)[0]=row;
	}

	void SetRight(T x, T y, T z)
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());
		(*this)[0][0]=x;
		(*this)[0][1]=y;
		(*this)[0][2]=z;
	}

	void SetUpVector(const sseVector<T>& row)
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());
		
		(*this)[1]=row;
	}	

	void SetUpVector(T x, T y, T z)
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());
		(*this)[1][0]=x;
		(*this)[1][1]=y;
		(*this)[1][2]=z;
	}
	
	void SetView(const sseVector<T>& row)
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());
		
		(*this)[2]=row;
	}	

	void SetView(T x, T y, T z)
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());
		(*this)[2][0]=x;
		(*this)[2][1]=y;
		(*this)[2][2]=z;
	}

	void SetPosition(const sseVector<T>& row)
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());
		
		(*this)[3]=row;
	}	

	void SetPosition(T x, T y, T z)
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());
		(*this)[3][0]=x;
		(*this)[3][1]=y;
		(*this)[3][2]=z;
	}

	sseVector<T> GetRight() const
	{
		return ((*this)[0]);
	}

	sseVector<T> GetUpVector() const
	{
		return ((*this)[1]);
	}

	sseVector<T> GetView() const
	{
		return ((*this)[2]);
	}

	sseVector<T> GetPosition() const
	{
		return ((*this)[3]);
	}

	sseVector<T> GetDir()
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());
		return (GetView() - GetRight());
	}

	sseVector<T> GetXAxis()
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());
		return (GetUpVector().Cross(GetZAxis()).Normalize());
	}

	sseVector<T> GetYAxis()
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());
		return ((GetZAxis().Cross(GetXAxis())).Normalize());
	}

	sseVector<T> GetZAxis()
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());
		return (GetDir().Normalize());
	}

	T *GetOGLMatrix()
	{
		static T m[16]={0};

		int c=0;

		if (m_iMaxRows==4)
		{
			m[c++]=m_vectors[0][0];
			m[c++]=m_vectors[0][1];
			m[c++]=m_vectors[0][2];
			m[c++]=m_vectors[0][3];
			m[c++]=m_vectors[1][0];
			m[c++]=m_vectors[1][1];
			m[c++]=m_vectors[1][2];
			m[c++]=m_vectors[1][3];
			m[c++]=m_vectors[2][0];
			m[c++]=m_vectors[2][1];
			m[c++]=m_vectors[2][2];
			m[c++]=m_vectors[2][3];
			m[c++]=m_vectors[3][0];
			m[c++]=m_vectors[3][1];
			m[c++]=m_vectors[3][2];
			m[c++]=m_vectors[3][3];
		} else {
			for (int i=0; i<m_iMaxRows; i++)
			{
				for (int j=0; j<m_iMaxCols; j++)
				{
						m[c]=m_vectors[i][j];
						c++;
				}
			}
		}

		return m;
	}

	// Sets the matrix to a rotation matrix (by axis and angle).
	_Mtrx& AxisAngleRotate(sseVector<T> &v, const float A)
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());

		sseErrorHandler::_ThrowIfMatrixError(v.size()<3||v.size()>4);

		double c = cos(A);
		double s = sin(A);
		double t = 1 - c;

		v.Normalize();
		v.Clean();

		Identity();

		(*this)[0][0]=(t*(v[0]*v[0]) + c);
		(*this)[0][1]=(t*(v[0]*v[1]) - v[2]*s);
		(*this)[0][2]=(t*(v[0]*v[2]) + v[1]*s);

		(*this)[1][0]=(t*(v[0]*v[1]) + v[2]*s);
		(*this)[1][1]=(t*(v[1]*v[1]) + c);
		(*this)[1][2]=(t*(v[1]*v[2]) - v[0]*s);

		(*this)[2][0]=(t*(v[0]*v[2]) - v[1]*s);
		(*this)[2][1]=(t*(v[1]*v[2]) + v[0]*s);
		(*this)[2][2]=(t*(v[2]*v[2]) + c);

		return (*this);
	}

	_Mtrx& RotationX( double angle )
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());

		double cThetaX = cos(angle);
		double sThetaX = sin(angle);

		sseMatrix<T> RX(m_iMaxCols,m_iMaxRows);

		RX.Identity();

		RX[1][1]=cThetaX;  RX[1][2]=sThetaX;
		RX[2][1]=-sThetaX; RX[2][2]=cThetaX;

		(*this)=RX;

		return (*this);
	}

    _Mtrx& RotationY( double angle )
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());

		double cThetaY = cos(angle);
		double sThetaY = sin(angle);

		sseMatrix<T> RY(m_iMaxCols,m_iMaxRows);

		RY.Identity();

		RY[0][0]=cThetaY;  RY[0][2]=-sThetaY;
		RY[2][0]=sThetaY;  RY[2][2]=cThetaY;

		(*this)=RY;

		return (*this);
	}

    _Mtrx& RotationZ( double angle )
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());

		double cThetaZ = cos(angle);
		double sThetaZ = sin(angle);

		sseMatrix<T> RZ(m_iMaxCols,m_iMaxRows);

		RZ.Identity();

		RZ[0][0]=cThetaZ;  RZ[0][1]=sThetaZ;
		RZ[1][0]=-sThetaZ; RZ[1][1]=cThetaZ;

		(*this)=RZ;

		return (*this);
	}

	// The Euler angle representation of a rotation, defined by Euler Angle Form
	// Experience Gimbal Lock
	_Mtrx& Rotate(const double Ax, const double Ay, const double Az)
	{
		sseErrorHandler::_ThrowIfMatrixError(!is3DMatrix());

		double cThetaX = cos(Ax);
		double sThetaX = sin(Ax);
		double cThetaY = cos(Ay);
		double sThetaY = sin(Ay);
		double cThetaZ = cos(Az);
		double sThetaZ = sin(Az);

		sseMatrix<T> RX(m_iMaxCols,m_iMaxRows);
		sseMatrix<T> RY(m_iMaxCols,m_iMaxRows);
		sseMatrix<T> RZ(m_iMaxCols,m_iMaxRows);

		RX.Identity();
		RY.Identity();
		RZ.Identity();
		
		RX[1][1]=cThetaX;  RX[1][2]=sThetaX;
		RX[2][1]=-sThetaX; RX[2][2]=cThetaX;

		RY[0][0]=cThetaY;  RY[0][2]=-sThetaY;
		RY[2][0]=sThetaY;  RY[2][2]=cThetaY;

		RZ[0][0]=cThetaZ;  RZ[0][1]=sThetaZ;
		RZ[1][0]=-sThetaZ; RZ[1][1]=cThetaZ;

		(*this)=(RX*RY*RZ);

		return (*this);
	}

protected:
	int m_iMaxRows;
	int m_iMaxCols;

private:
	sseVector<T> *m_vectors;
};

#endif
