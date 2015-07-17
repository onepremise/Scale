//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Vector Algebra Library
//
//  Notes:
//          Add constant time operations for fixed sizes
//          of 3 and 4 for mainstream math.
//
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//  01/13/2005    Customized vector class JAH       @001
//=========================================================
#ifndef __SSEVECTOR__
#define __SSEVECTOR__

#include "sseInclude.hpp"
#include "sseMath.hpp"

template <class T> class sseMatrix;

//@001
//Added more operators to vector class for additional algebra
template <class T>
class sseVector
{
private:
	T *m_components;
	int m_size;

public:
	typedef sseVector<T> _Vctr;

	sseVector()
	{
		m_components=NULL;
		m_size=0;
		Init(4);
	}

	sseVector(const _Vctr &VC)
	{
		m_components=NULL;
		m_size=0;
		Copy(VC);
	}

	sseVector(const int iSize)
	{
		m_components=NULL;
		m_size=iSize;
		Init(iSize);
	}

	sseVector(T x, T y, T z)
	{
		m_components=NULL;
		m_size=0;

		Init(3);
		
		m_components[0]=x;
		m_components[1]=y;
		m_components[2]=z;
	}

	sseVector(T x, T y, T z, T w)
	{
		m_components=NULL;
		m_size=0;

		Init(4);

		m_components[0]=x;
		m_components[1]=y;
		m_components[2]=z;
		m_components[3]=w;
	}

	~sseVector()
	{
		if (m_components!=NULL)
			delete [] m_components;
	}

	void Init(const int iSize)
	{
		if (m_components!=NULL)
			delete [] m_components;

		m_components=new T[iSize];

		m_size=iSize;

		Clear();
	}

	void Clear()
	{
		if (m_size==1)
			m_components[0]=0;
		else if (m_size==2)
		{
			m_components[0]=0;
			m_components[1]=0;
		}
		else if (m_size==3)
		{
			m_components[0]=0;
			m_components[1]=0;
			m_components[2]=0;
		}
		else if (m_size==4)
		{
			m_components[0]=0;
			m_components[1]=0;
			m_components[2]=0;
			m_components[3]=0;
		}
		else
		{
			for (int j=0; j<m_size; j++)
				m_components[j]=0;
		}
	}

	void Copy(const _Vctr &VC)
	{
		if (m_size!=VC.getSize())
			Init(VC.getSize());

		m_components[0]=VC[0];

		if (m_size==3)
		{
			m_components[1]=VC[1];
			m_components[2]=VC[2];
		}
		else if (m_size==4)
		{
			m_components[1]=VC[1];
			m_components[2]=VC[2];
			m_components[3]=VC[3];
		}
		else
		{
			for (int j=0; j<m_size; j++)
				m_components[j]=VC[j];
		}
	}

	int size() const
	{
		return m_size;
	}

	_Vctr& operator=(const _Vctr &v)
	{
		Copy(v);
		return *this;
	}

	T& operator[] (int index)
	{
		return m_components[index];
	}

	//Get Constant Vector
	const T& operator[] (int index) const
	{
		return m_components[index];
	}

	_Vctr operator* ( const _Vctr& v) const
    {
		int iSize=(*this).size();
		sseErrorHandler::_ThrowIfVectorError(iSize!=v.size());

		_Vctr vProd(iSize);

		if (iSize==3)
		{
			vProd[0] = vProd[0]*v[0];
			vProd[1] = vProd[1]*v[1];
			vProd[2] = vProd[2]*v[2];
		}
		else if (iSize==4)
		{
			vProd[0] = vProd[0]*v[0];
			vProd[1] = vProd[1]*v[1];
			vProd[2] = vProd[2]*v[2];
			vProd[3] = vProd[3]*v[3];
		}
		else
		{
			for ( int i=0; i<iSize; i++ )
				vProd[i]=(*this)[i]*v[i];
		}

        return vProd;
    }


	bool operator== ( const _Vctr& v)
    {
		int iSize=(int)size();
		sseErrorHandler::_ThrowIfVectorError(iSize!=v.size());

		if (iSize==3)
		{
			if ((*this)[0]!=v[0]) return false;
			if ((*this)[1]!=v[1]) return false;
			if ((*this)[2]!=v[2]) return false;
		}

		if (iSize==4)
		{
			if ((*this)[3]!=v[3]) return false;
		}
		else
		{
			for ( int i=0; i<iSize; i++ )
				if ((*this)[i]!=v[i]) return false;
		}

        return true;
    }

	bool operator!= ( const _Vctr& v)
    {
		int iSize=(int)size();
		sseErrorHandler::_ThrowIfVectorError(iSize!=v.size());

		if (iSize==3) {
			if ((*this)[0]!=v[0]) return true;
			if ((*this)[1]!=v[1]) return true;
			if ((*this)[2]!=v[2]) return true;
		} else if (iSize==4) {
			if ((*this)[0]!=v[0]) return true;
			if ((*this)[1]!=v[1]) return true;
			if ((*this)[2]!=v[2]) return true;
			if ((*this)[3]!=v[3]) return true;
		} else {
			for ( int i=0; i<iSize; i++ )
				if ((*this)[i]!=v[i]) return true;
		}

        return false;
    }

	_Vctr& operator*= (const T C)
	{
		if (size()==3)
		{
			(*this)[0]*=C;
			(*this)[1]*=C;
			(*this)[2]*=C;
		}
		else if (size()==4)
		{
			(*this)[0]*=C;
			(*this)[1]*=C;
			(*this)[2]*=C;
			(*this)[3]*=C;
		}
		else
		{
			for ( int i=0 ; i<m_size ; i++ )
				(*this)[i]*=C;
		}

		return (*this);
	}

	friend _Vctr operator* (const _Vctr& vA, const T C)
	{
		_Vctr newV=vA;
		return newV*=C;
	}

	_Vctr& operator*= (const sseMatrix<T> M)
	{
		sseErrorHandler::_ThrowIfVectorError(size()!=M.GetRows());
		_Vctr newV(m_size);

		if (size()==3)
		{
			newV[0] = (*this)[0]*M[0][0] + (*this)[1]*M[1][0] + (*this)[2]*M[2][0];
			newV[1] = (*this)[0]*M[0][1] + (*this)[1]*M[1][1] + (*this)[2]*M[2][1];
			newV[2] = (*this)[0]*M[0][2] + (*this)[1]*M[1][2] + (*this)[2]*M[2][2];
		}
		else if (size()==4)
		{
			newV[0] = (*this)[0]*M[0][0] + (*this)[1]*M[1][0] + (*this)[2]*M[2][0] + (*this)[3]*M[3][0];
			newV[1] = (*this)[0]*M[0][1] + (*this)[1]*M[1][1] + (*this)[2]*M[2][1] + (*this)[3]*M[3][1];
			newV[2] = (*this)[0]*M[0][2] + (*this)[1]*M[1][2] + (*this)[2]*M[2][2] + (*this)[3]*M[3][2];
			newV[3] = (*this)[0]*M[0][3] + (*this)[1]*M[1][3] + (*this)[2]*M[2][3] + (*this)[3]*M[3][3];
		}
		else
		{
			for (int i=0; i<M.GetCols(); i++)
				for (int j=0; j<M.GetRows(); j++)
					newV[i]+=(*this)[j]*M[j][i];
		}

		(*this)=newV;
		return (*this);
	}

	friend _Vctr operator* (const _Vctr& vA, const sseMatrix<T> M)
	{
		_Vctr newV=vA;
		return newV*=M;
	}

	friend _Vctr operator- (const _Vctr& vA, const _Vctr& vB)
	{
		sseErrorHandler::_ThrowIfVectorError(vA.size()!=vB.size());
		_Vctr v(vA.size());

		if (vA.size()==3)
		{
			v[0]=vA[0]-vB[0];
			v[1]=vA[1]-vB[1];
			v[2]=vA[2]-vB[2];
		}
		else if (vA.size()==4)
		{
			v[0]=vA[0]-vB[0];
			v[1]=vA[1]-vB[1];
			v[2]=vA[2]-vB[2];
			v[3]=vA[3]-vB[3];
		}
		else
		{
			for (int i=0; i<vB.size(); i++)
				v[i]=vA[i]-vB[i];
		}

		return v;
	}

	_Vctr& operator-()
	{
		if (size()==3)
		{
			(*this)[0]=(*this)[0]*-1;
			(*this)[1]=(*this)[1]*-1;
			(*this)[2]=(*this)[2]*-1;
		}
		else if (size()==4)
		{
			(*this)[0]=(*this)[0]*-1;
			(*this)[1]=(*this)[1]*-1;
			(*this)[2]=(*this)[2]*-1;
			(*this)[3]=(*this)[3]*-1;
		}
		else
		{
			for (int i=0; i<m_size; i++)
				(*this)[i]=(*this)[i]*-1;
		}

		return (*this);
	}

	_Vctr& operator-= (const _Vctr& v)
	{
		if (size()==3)
		{
			(*this)[0]=(*this)[0]-v[0];
			(*this)[1]=(*this)[1]-v[1];
			(*this)[2]=(*this)[2]-v[2];
		}
		else if (size()==4)
		{
			(*this)[0]=(*this)[0]-v[0];
			(*this)[1]=(*this)[1]-v[1];
			(*this)[2]=(*this)[2]-v[2];
			(*this)[3]=(*this)[3]-v[3];
		}
		else
		{
			for (int i=0; i<v.size(); i++)
				(*this)[i]=(*this)[i]-v[i];
		}

		return (*this);
	}

	friend _Vctr operator+ (const _Vctr& vA, const _Vctr& vB)
	{
		sseErrorHandler::_ThrowIfVectorError(vA.size()!=vB.size());
		_Vctr vProduct=vA;

		if (vA.size()==3)
		{
			vProduct[0]=vProduct[0]+vB[0];
			vProduct[1]=vProduct[1]+vB[1];
			vProduct[2]=vProduct[2]+vB[2];
		}
		else if (vA.size()==4)
		{
			vProduct[0]=vProduct[0]+vB[0];
			vProduct[1]=vProduct[1]+vB[1];
			vProduct[2]=vProduct[2]+vB[2];
			vProduct[3]=vProduct[3]+vB[3];
		}
		else
		{
			for (int i=0; i<vB.size(); i++)
				vProduct[i]=vProduct[i]+vB[i];
		}

		return vProduct;
	}

	_Vctr& operator+= (const _Vctr& v)
	{
		sseErrorHandler::_ThrowIfVectorError(size()!=v.size());

		if (size()==3)
		{
			(*this)[0]=(*this)[0]+v[0];
			(*this)[1]=(*this)[1]+v[1];
			(*this)[2]=(*this)[2]+v[2];
		}
		else if (size()==4)
		{
			(*this)[0]=(*this)[0]+v[0];
			(*this)[1]=(*this)[1]+v[1];
			(*this)[2]=(*this)[2]+v[2];
			(*this)[3]=(*this)[3]+v[3];
		}
		else
		{
			for (int i=0; i<v.size(); i++)
				(*this)[i]=(*this)[i]+v[i];
		}

		return (*this);
	}

	// Geometrically, the dot product of two vectors is the magnitude
	// of one times the projection of the other along the first.
	T Dot(const _Vctr &Other) const
	{
		sseErrorHandler::_ThrowIfVectorError(size()!=Other.size());
		T sum=0;

	   if (size()==3)
	   {
			sum+=((*this)[0])*(Other[0]);
			sum+=((*this)[1])*(Other[1]);
			sum+=((*this)[2])*(Other[2]);
	   }
	   else if (size()==4)
	   {
			sum+=((*this)[0])*(Other[0]);
			sum+=((*this)[1])*(Other[1]);
			sum+=((*this)[2])*(Other[2]);
			sum+=((*this)[3])*(Other[3]);
	   }
	   else
	   {
			for ( int i=0 ; i<m_size; i++ )
				sum+=((*this)[i])*(Other[i]);
	   }

		return sum;
	}

	// the cross product of two vectors is the area of the parallelogram
	// between them.
	_Vctr Cross(const _Vctr &Other) const
	{
		int iSize1=size();
		int iSize2=Other.size();

		sseErrorHandler::_ThrowIfVectorError(iSize1!=iSize2);
		sseErrorHandler::_ThrowIfVectorError(iSize1<3 || iSize2<3);

		if (MAX(iSize1,iSize2)<4)
			return _Vctr((*this)[1]*Other[2]-(*this)[2]*Other[1],
					 	 (*this)[2]*Other[0]-(*this)[0]*Other[2],
					 	 (*this)[0]*Other[1]-(*this)[1]*Other[0]);
		else if (MAX(iSize1,iSize2)==4)
			return _Vctr((*this)[1]*Other[2]-(*this)[2]*Other[1],
					 	 (*this)[2]*Other[0]-(*this)[0]*Other[2],
					 	 (*this)[0]*Other[1]-(*this)[1]*Other[0],0);

		_Vctr v(MAX(iSize1,iSize2));

		v[0]=(*this)[1]*Other[2]-(*this)[2]*Other[1];
		v[1]=(*this)[0]*Other[2]-(*this)[2]*Other[0];
		v[2]=(*this)[0]*Other[1]-(*this)[1]*Other[0];

		return v;
	}

	inline T toYaw()
	{
		T yaw = 0.0f;

		if ((*this)[0] == 0.0f && (*this)[2] == 0.0f)
			yaw = 0.0f;
		else
			yaw = (T)(atan2 ((*this)[0],(*this)[2]));

		return (T) yaw;
	}

	inline T toPitch()
	{
		T pitch = 0.0f;
		if ((*this)[0] == 0.0f && (*this)[2] == 0.0f)
		{
		    if ((*this)[1] > 0.0f)
				pitch = 4.71238898;
			else
				pitch = 1.57079633;
		}
		else
		{
			T forward = sqrt((*this)[0] * (*this)[0] + (*this)[2] * (*this)[2]);
			pitch = (T)(atan2((*this)[2], forward));

			if ((*this)[2] < 0.0)
                pitch =  -pitch;
		}

		return pitch;
	}

	T Distance(const _Vctr &vPoint2)
	{
		// This is the classic formula used in beginning algebra to return the
		// distance between 2 points.  Since it's 3D, we just add the z dimension:
		//
		// Distance = sqrt(  (P2.x - P1.x)^2 + (P2.y - P1.y)^2 + (P2.z - P1.z)^2 )
		//
		T distance = sqrt( (vPoint2[0] - (*this)[0]) * (vPoint2[0] - (*this)[0]) +
								(vPoint2[1] - (*this)[1]) * (vPoint2[1] - (*this)[1]) +
								(vPoint2[2] - (*this)[2]) * (vPoint2[2] - (*this)[2]) );

		// Return the distance between the 2 points
		return distance;
	}


	T Length() const
	{
		return SumOfSquares();
	}

	T SumOfSquares() const
	{
	   T sum=0;

       if (size()==3)
	   {
			sum+=(*this)[0]*(*this)[0];
			sum+=(*this)[1]*(*this)[1];
			sum+=(*this)[2]*(*this)[2];
	   }
	   else if (size()==4)
	   {
			sum+=(*this)[0]*(*this)[0];
			sum+=(*this)[1]*(*this)[1];
			sum+=(*this)[2]*(*this)[2];
			sum+=(*this)[3]*(*this)[3];
	   }
	   else
	   {
		   for ( int i=0 ; i<size() ; i++ )
				sum+=(*this)[i]*(*this)[i];
	   }

	   return sum;
	}

	T RowNorm() const
	{
		T norm = fabs((*this)[0]);
		T ret  = 0;
		for ( int i=0 ; i<size() ; i++ )
		{
			ret=fabs((*this)[i]);
			if ( ret > norm ) norm=ret;
		}
		return norm;
	}

	//length (magnitude)
	T Norm() const
	{
		return sqrt(SumOfSquares());
	}

	_Vctr& Normalize()
	{
		T n = Norm();
		// too close to 0, can't make a normalized vector
		if (n < .000001) {
			for ( int i=0 ; i<size() ; i++ )
				(*this)[i]=0.0f;
		} else {
			if (size()==3)
			{
				(*this)[0]/=n;
				if (::isZero((*this)[0])) (*this)[0]=0.0f;

				(*this)[1]/=n;
				if (::isZero((*this)[1])) (*this)[1]=0.0f;

				(*this)[2]/=n;
				if (::isZero((*this)[2])) (*this)[2]=0.0f;
			}
			else if (size()==4)
			{
				(*this)[0]/=n;
				if (::isZero((*this)[0])) (*this)[0]=0.0f;

				(*this)[1]/=n;
				if (::isZero((*this)[1])) (*this)[1]=0.0f;

				(*this)[2]/=n;
				if (::isZero((*this)[2])) (*this)[2]=0.0f;

				(*this)[3]/=n;
				if (::isZero((*this)[3])) (*this)[3]=0.0f;
			}
			else
			{
				for ( int i=0 ; i<size() ; i++ )
				{
					(*this)[i]/=n;
					if(::isZero((*this)[i]))
						(*this)[i]=0.0f;
				}
			}
		}

		return (*this);
	}

	_Vctr& Clean()
	{
		for (int i=0; i<size(); i++)
			if(::isZero((*this)[i]))
				(*this)[i]=0.0f;
		return (*this);
	}

	_Vctr& UnitVector()
	{
		return (*this)*(1.0/Norm());
	}

	bool IsUnit() const
	{
		T val= 1.0f;

		for (int i=0; i<size(); i++)
			val-=(*this)[i]*(*this)[i];

		return ::isZero(val);
	}

	bool IsNull()
	{
		for (int i=0; i<size(); i++)
			if(!isZero((*this)[i]))
				return false;
		return true;
	}

	const float *GetGLArray(float result[4])
	{
		result[0] = (*this)[0];
		result[1] = (*this)[1];
		result[2] = (*this)[2];
		result[3] = 1.0;

		return result;
	}

	const double *GetGLArray(double result[4])
	{
		result[0] = (*this)[0];
		result[1] = (*this)[1];
		result[2] = (*this)[2];
		result[3] = 1.0;

		return result;
	}

	int getSize() const
	{
		return m_size;
	}

	//For debugging purposes only
	String toString(char *tag="") const
	{
		std::ostringstream oss;
		oss<<tag;

		oss<<" Vector:"<<endl;

		for (int i=0; i<size(); i++)
		{
			oss << std::setw(15) << (double)(*this)[i];
		}

		oss<<endl;

		return oss.str();
	}
};

static const sseVector<float> UNIT_X3( 1, 0, 0 );
static const sseVector<float> UNIT_X4( 1, 0, 0, 0 );

static const sseVector<float> UNIT_Y3( 0, 1, 0 );
static const sseVector<float> UNIT_Y4( 0, 1, 0, 0 );

static const sseVector<float> UNIT_Z3( 0, 0, 1 );
static const sseVector<float> UNIT_Z4( 0, 0, 1, 0 );

static const sseVector<float> ZERO3( 0, 0, 0 );
static const sseVector<float> ZERO4( 0, 0, 0, 0 );


#endif
