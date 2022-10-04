//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Quaternion Library
//
// Notes:
//  Quaternions were developed by William Rowan Hamilton 
//  around 1843.
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
#ifndef __SSEQUAT__
#define __SSEQUAT__

#include "sseInclude.hpp"

template <class T> class sseVector;
template <class T> class sseMatrix33;
template <class T> class sseMatrix44;

template <class T>
class sseQuaternion: public sseVector<T>
{
public:
	typedef sseQuaternion<T> _Q;

	sseQuaternion(): sseVector<T>(4)
	{
		
	}
	
	sseQuaternion(T x, T y, T z, T angle)
	{
		sseVector<T>::Init(4);
		
		sseVector<T> vAxis(x, y, z, 0);
		
		AxisToQuat(vAxis, angle);
	}

	sseQuaternion(const sseVector<T> &vAxis, T angle)
	{
		sseVector<T>::Init(4);

		AxisToQuat(vAxis, angle);
	}
	
	sseQuaternion(const sseVector<T> &v)
	{
		sseVector<T>::Init(4);

		(*this)[0]=v[0];
		(*this)[1]=v[1];
		(*this)[2]=v[2];
		(*this)[3]=0;
	}	

	sseQuaternion( const sseVector<T> &from, const sseVector<T> &to )
	{
		Set( from, to );
	}

	void Set( const sseVector<T> &from, const sseVector<T> &to )
	{
		sseErrorHandler::_ThrowIfUnitVectorError(!from.IsUnit());
		sseErrorHandler::_ThrowIfUnitVectorError(!to.IsUnit());

		// get axis of rotation
		sseVector<T> axis = from.Cross( to );
		// get cos of angle between vectors
		T costheta = from.Dot( to );

		// if vectors are 180 degrees apart
		if ( costheta <= -1.0f )
		{
			// find orthogonal vector
			sseVector<T> orthoVector;
			orthoVector.Normalize();

			(*this)[3] = 0.0f;
			(*this)[0] = orthoVector[0];
			(*this)[1] = orthoVector[1];
			(*this)[2] = orthoVector[2];

			return;
		}

		// use trig identities to get the values we want
		double factor = sqrt( 2.0f*(1.0f + costheta) );
		double scaleFactor = 1.0f/factor;

		// set values
		(*this)[3] = 0.5f*factor;
		(*this)[0] = scaleFactor*axis[0];
		(*this)[1] = scaleFactor*axis[1];
		(*this)[2] = scaleFactor*axis[2];
	}

	void Identity()
	{
		(*this)[0]=1;

		if (this->size()==3)
		{
			(*this)[1]=0;
			(*this)[2]=0;
		}
		else if (this->size()==4)
		{
			(*this)[1]=0;
			(*this)[2]=0;
			(*this)[3]=0;
		}
		else
		{
			for (int j=1; j<(sseVector<T>::size()-1); j++)
				(*this)[j]=0;
		}
	}
	
	_Q operator* ( const _Q& q) const
    {
    	_Q qProd;
    	
    	qProd[0]=(*this)[3]*q[0] + (*this)[0]*q[3] + (*this)[1]*q[2] - (*this)[2]*q[1];
    	qProd[1]=(*this)[3]*q[1] + (*this)[0]*q[2] + (*this)[1]*q[3] - (*this)[2]*q[0];
    	qProd[2]=(*this)[3]*q[2] + (*this)[0]*q[1] + (*this)[1]*q[0] - (*this)[2]*q[3];
    	qProd[3]=(*this)[3]*q[3] + (*this)[0]*q[0] + (*this)[1]*q[1] - (*this)[2]*q[2];
    	
    	return qProd;
    }
    
	// Multiplying a quaternion with a vector, applying the rotation
	sseVector<T> operator* (const sseVector<T> &vec) const
	{
		sseVector<T> vn(vec);
		_Q conjQ(*this);
		
		vn.Normalize();
	 
		_Q vecQuat, resQuat;
		vecQuat[0] = vn[0];
		vecQuat[1] = vn[1];
		vecQuat[2] = vn[2];
		vecQuat[3] = 0.0f;
	 
		resQuat = vecQuat * conjQ.Conjugate();
		resQuat = *this * resQuat;
	 
		return (sseVector<T>(resQuat[0], resQuat[1], resQuat[2],0));
	}    

	_Q& Conjugate()
	{
		(*this)[0]=-(*this)[0];
		(*this)[1]=-(*this)[1];
		(*this)[2]=-(*this)[2];
		
		//No change for rotation [3]
		return (*this);
	}

	/*void GetAxisAngle( sseVector<T> &axis, float &angle )
	{
		angle = 2.0f*acosf( w );
		float length = sqrt( 1.0f - w*w );
		if ( isZero(length) )
			axis.Clean();
		else
		{
			length = 1.0f/length;
			axix[0]=x*length;
			axix[1]=y*length;
			axix[2]=z*length;
		}
	}*/

	T getRoll(void) const
	{
		sseQuaternion<T> copy((*this));
		copy.Normalize();

		return atan2(2*(copy[1]*copy[2] + copy[3]*copy[0]), copy[3]*copy[3] - copy[0]*copy[0] - copy[1]*copy[1] + copy[2]*copy[2]);
	}
    //-----------------------------------------------------------------------
	T getPitch(void) const
	{
		sseQuaternion<T> copy((*this));
		copy.Normalize();

		return asin(-2*(copy[0]*copy[2] - copy[3]*copy[1]));
	}
    //-----------------------------------------------------------------------
	T getYaw(void) const
	{
		sseQuaternion<T> copy((*this));
		copy.Normalize();

		return atan2(2*(copy[0]*copy[1] + copy[3]*copy[2]), copy[3]*copy[3] + copy[0]*copy[0] - copy[1]*copy[1] - copy[2]*copy[2]);
	}

	sseMatrix44<T> Get4x4Matrix()
	{
		sseErrorHandler::_ThrowIfUnitVectorError(!this->IsUnit());

		sseMatrix44<T> m;

		T xx = (*this)[0]*(*this)[0];
		T xy = (*this)[0]*(*this)[1];
		T xz = (*this)[0]*(*this)[2];
		T xw = (*this)[0]*(*this)[3];
		T yy = (*this)[1]*(*this)[1];
		T yz = (*this)[1]*(*this)[2];
		T yw = (*this)[1]*(*this)[3];
		T zz = (*this)[2]*(*this)[2];
		T zw = (*this)[2]*(*this)[3];

		m.Identity();

		m[0][0] = 1.0f - 2 * ( yy + zz );
		m[0][1] =     2 * ( xy - zw );
		m[0][2] =     2 * ( xz + yw );

		m[1][0] =     2 * ( xy + zw );
		m[1][1] = 1.0f - 2 * ( xx + zz );
		m[1][2] =     2 * ( yz - xw );

		m[2][0] =     2 * ( xz - yw );
		m[2][1] =     2 * ( yz + xw );
		m[2][2] = 1.0f - 2 * ( xx + yy );

		return m;
	}
	
	// Convert from Axis Angle
	void AxisToQuat(sseVector<T> vAxis, T angle)
	{
		T length = vAxis.Length();
		if ( isZero( length ) )
		{
			Identity();
			return;
		}

		angle *= 0.5f;

		double sintheta=sin(angle); 
		double costheta=cos(angle);
		double scaleFactor = sintheta/sqrt(length);

		(*this)[0] = vAxis[0] * scaleFactor;
		(*this)[1] = vAxis[1] * scaleFactor;
		(*this)[2] = vAxis[2] * scaleFactor;
		(*this)[3] = costheta;
	}
	
	// Convert from Euler Angles
	void EulerToQuat(double pitch, double yaw, double roll)
	{
		pitch*=0.05f;
		yaw*=0.05f;
		roll*=0.05f;
	 
		double sinp = sin(pitch);
		double siny = sin(yaw);
		double sinr = sin(roll);
		double cosp = cos(pitch);
		double cosy = cos(yaw);
		double cosr = cos(roll);
	 
		(*this)[0] = sinr * cosp * cosy - cosr * sinp * siny;
		(*this)[1] = cosr * sinp * cosy + sinr * cosp * siny;
		(*this)[2] = cosr * cosp * siny - sinr * sinp * cosy;
		(*this)[3] = cosr * cosp * cosy + sinr * sinp * siny;
	 
		sseVector<T>::Normalize();
	}	

	_Q& lerp(const _Q &q2, T t) 
	{ 
		return ((*this)*(1-t) + q2*t).normalized();
	}

	_Q& slerp(const _Q &q2, T t) 
	{
		_Q q3;
		T dot = Dot((*this), q2);

		/*	dot = cos(theta)
			if (dot < 0), q1 and q2 are more than 90 degrees apart,
			so we can invert one to reduce spinning	*/
		if (dot < 0)
		{
			dot = -dot;
			q3 = -q2;
		} else q3 = q2;
		
		if (dot < 0.95f)
		{
			T angle = acos(dot);
			return ((*this)*sinf(angle*(1-t)) + q3*sinf(angle*t))/sinf(angle);
		} else							
			return lerp((*this),q3,t);		
	}

	_Q& slerpNoInvert(const _Q &q2, float t) 
	{
		T dot = Dot((*this), q2);

		if (dot > -0.95f && dot < 0.95f)
		{
			double angle = acos(dot);	

			return ((*this)*sinf(angle*(1-t)) + q2*sinf(angle*t))/sinf(angle);
		} else 							
			return lerp((*this),q2,t);			
	}

	
	void debugPrint()
	{
		cerr << "Quaternion:" << endl;
		
		for (int j=0; j<sseVector<T>::size(); j++)
			cerr << (*this)[j] << " ";

		cerr << endl;
	}	
};

#endif
