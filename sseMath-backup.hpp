//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Matrix Algebra Library
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
#include <math.h>

using namespace std;

//begin ssemath namespace
namespace ssemath {

#define SSEMATRIXTEMPLATE template <class T>
#define SSEVECTORTEMPLATE template <class T>

SSEVECTORTEMPLATE
class sseVector: public vector<T>
{
	sseVector(): vector()
	{

	}
};

SSEMATRIXTEMPLATE
class sseMatrix
{
public:
	typedef sseMatrix<T> _Mtrx;
	//Default Matrix
	sseMatrix(): m_vComponents(3, vector<T>(3)) { }

	//Copy Contstructor
	sseMatrix(const _Mtrx& m)
	{
		Copy(m);
	}

	//Copy Matrix
	void Copy(const _Mtrx& m)
	{
		m_iMaxRows=m.GetRows();
		m_iMaxCols=m.GetCols();

		for (int i=0; i<m_iMaxRows; i++)	
			m_vComponents.push_back(m[i]);
	}

	//Create Matrix with dimensions
	sseMatrix(int iRows, int iCols)
	{
		Init(iRows, iCols);
	}

	//Initialize the Matrix for use
	void Init(int iRows, int iCols)
	{
		Clear();

		m_iMaxRows=iRows;
		m_iMaxCols=iCols;

		for (int i=0; i<iRows; i++)
		{
			vector<T> vInit;
			for (int j=0; j<iCols; j++)
				vInit.push_back(0);
			m_vComponents.push_back(vInit);
		}
	}

	//Get Component
	T& operator() (int iRow, int iCol)
	{
		return m_vComponents[iRow][iCol];
	}

	//Get Vector
	vector<T>& operator[] (int iRow)
	{
		return m_vComponents[iRow];
	}

	//Get Constant Vector
	const vector<T>& operator[] (int iRow) const
	{
		return m_vComponents[iRow];
	}

	//Assign Matrix
	_Mtrx& operator= (const _Mtrx& m)
	{
		if (this != &m) 
		{
			Clear();
			Copy(m);
		}
		return (*this);
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

	//Matrix Multiplication
	friend _Mtrx operator* (const _Mtrx& mA, const _Mtrx& mB)
	{
		sseErrorHandler::_ThrowIfMatrixError((mA.GetCols() != mB.GetRows()));
		_Mtrx m_product(mA.m_iMaxRows, mB.m_iMaxCols);

		for (int i=0; i<mB.m_iMaxRows; i++)
			for (int j=0; j<mA.m_iMaxCols; j++)
				for (int k=0; k<mA.m_iMaxCols; k++)
					if(i<mA.m_iMaxRows && j<mB.m_iMaxCols)
						m_product[i][j]+=(mA[i][k]*mB[k][j]);

		return m_product;
	}

	//Multiply by scalar
	friend _Mtrx operator* (const _Mtrx& mA, const T value)
	{
		_Mtrx m_product(mA.m_iMaxRows, mA.m_iMaxCols);

		for (int i=0; i<m_div.m_iMaxRows; i++)
			for (int j=0; j<m_div.m_iMaxCols; j++)
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
				m_vComponents[i][j]=(m_vComponents[i][j]+m[i][j]);

		return (*this);
	}

	//Matrix Subtraction
	_Mtrx& operator-= (const _Mtrx& m)
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				m_vComponents[i][j]=(m_vComponents[i][j]-m[i][j]);

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
				m_vComponents[i][j]=m_vComponents[i][j]*value;
		return (*this);
	}

	//Divide by scalar
	_Mtrx& operator/= (const T value)
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				m_vComponents[i][j]=m_vComponents[i][j]/value;
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
		return ((pow((-1),(iRow+iCol)))*Minor(iRow,iCol));
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
		return(Adjoint()/Determinant());
	}

	// Set Matrix to identity if rows/cols equal
	void Identity(void)
	{
		sseErrorHandler::_ThrowIfMatrixError(!isSquare());
		Reset();
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
				if (m_vComponents[i][j] != 0) return false;
		return true;
	}

	// Check if matrix square
	// A square matrix is one where the number of rows and columns are equal
	bool isSquare() const
	{
		return (m_iMaxRows == m_iMaxCols);
	}

	// check if Diagonal
	// diagonal matrix is a square matrix in which all the elements are 
	// zero except for the elements on the leading diagonal
	bool isDiagonal() const
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				if (i==j && m_vComponents[i][j]==0) return false;
				else if (i!=j && m_vComponents[i][j]!=0) return false;
		return true;
	}

	// Check if Unit
	// A unit matrix is a square matrix in which all the elements on 
	// the leading diagonal are 1, and all the other elements are 0
	bool isUnit() const
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				if (i==j && m_vComponents[i][j]!=1) return false;
				else if (i!=j && m_vComponents[i][j]!=0) return false;
		return true;
	}

	// Check if symmetric
	// A symmetrix matrix is a square matrix where a.ij==a.ji for all elements.
	bool isSymmetric() const
	{
		for (int i=0; i<m_iMaxRows; i++)
			for (int j=0; j<m_iMaxCols; j++)
				if (m_vComponents[i][j]!=m_vComponents[j][i]) return false;
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
				if (i==j && (m_vComponents[i][j]!=0)) return false;
				else if (i!=j && (m_vComponents[i][j]!=-m_vComponents[j][i]))
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
	void isSameSizeAs(_Mtrx& m)
	{
		sseErrorHandler::_ThrowIfMatrixError((m_iMaxRows != m.GetRows()));
		sseErrorHandler::_ThrowIfMatrixError((m_iMaxCols != m.GetCols()));
	}

	// Clear Matrix
	virtual void Clear()
	{
		m_iMaxRows=m_iMaxCols=0;
		if (m_vComponents.size()>0)
			m_vComponents.erase(m_vComponents.begin(),m_vComponents.end());
	}

	// Reset Matrix Only
	void Reset()
	{
		for (int i=0; i<GetRows(); i++)
			for (int j=0; j<GetCols(); j++)
				(*this)[i][j]=0;
	}

	// Debug Output for testing
	void debugPrint() const
	{
		cerr << "Matrix:" << endl;
		for (int i=0; i<m_iMaxRows; i++)
		{
			for (int j=0; j<m_iMaxCols; j++)
					cerr << m_vComponents[i][j] << " ";
			cerr << endl;
		}
	}

public:
	int GetRows() const {return m_iMaxRows;}
	int GetCols() const {return m_iMaxCols;}

private:
	int m_iMaxRows;
	int m_iMaxCols;

	vector< vector<T> > m_vComponents;
};

typedef sseMatrix<int> iMatrix;
typedef sseMatrix<float> fMatrix;
typedef sseMatrix<double> dMatrix;

} //End ssemath namespace

#endif