//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Camera Logic
//
// Notes:
// 
//    Y+
//    |
//    |__ X+
//   /
//  Z+ 
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
#ifndef __SSECAMERA__
#define __SSECAMERA__

#include "sseInclude.hpp"
#include "sseEventObjectHandler.hpp"
#include "sseDisplayManager.hpp"
#include "sseMathEngine.hpp"
#include "sseClock.hpp"

using namespace ssemath;

class sseCamera: protected sseEventObjectHandler
{
public:
	sseCamera(): m_bIsLocal(true), m_dSpeed(5), m_dRotSpeed(.04)
	{ 
		m_pDisplay=sseDisplayManager::Instance();
		AcceptEvents();
		SetView(0, 0, 0,  0, 1.0, 0.5,  0, 0, 1.0 );
		m_camZoom=10;
	    m_zDistance=1;
		m_bUpdateZoom=false;
	}

	void SetView(double xRight,    double yRight,    double zRight,
                 double xView,     double yView,     double zView,
                 double xUp,       double yUp,       double zUp);

	void UpdateView();
	void SetPosition(const dVector &v);
	dVector GetPosition() { return m_CamMatrix.GetPosition(); };
	void MoveCamera(const dVector &v);
	void SetPitch(double A);
	void SetRoll(double A);
	void SetYaw(double A);
	void Zoom(bool bForward);

	dVector *GetRight() {return &m_vRight;}
	dVector *GetLookAt() {return &m_vLookAt;}
	dVector *GetUp() {return &m_vUp;}
	
	void EnableQuaternions(bool bUseQuaternions);

	void SetClock(sseClock *pClock);
	sseClock *getClock();

	virtual String getName() 
	{
		return m_strName;
	}

	virtual void setName(String strName)
	{
		m_strName=strName;
	}
	 
public:
	void Update();
	dMatrix44 *GetCameraMatrix() {return &m_CamMatrix;};
	dMatrix44 *GetViewTransformation() {return &m_viewTransformation;};
	//void LookAt(dVector position);

protected:
	void LookAt(dMatrix44 &matrix);
	void HandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion);
	void HandleMouseButtonEvents(SDL_MouseButtonEvent *pButton);
	void HandleMotionEvents();

private:
	dMatrix44   m_viewTransformation;
	dMatrix44   m_CamMatrix;

	dVector m_vRight;
	dVector m_vLookAt;
	dVector m_vUp;

	String m_strName;

private:
	sseClock *m_pClock;
	sseDisplayManager *m_pDisplay;
	
	bool   m_bUseQuaternion;
	bool   m_bIsLocal;
	double m_dSpeed;
	double m_dRotSpeed;
	double m_camZoom;
	double m_zDistance;
	bool   m_bUpdateZoom;
};

#endif
