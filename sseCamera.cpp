//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Camera Logic
//
//  Notes:
//    - M = T * R * S * T = TRST
//    - Right-Handed Coordinate System
//    Y
//    |
//    |__ X
//   /
//  Z 
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//=========================================================
#include "sseCamera.hpp"

void sseCamera::EnableQuaternions(bool bUseQuaternions)
{
	m_bUseQuaternion=bUseQuaternions;
}

void sseCamera::SetView(double xRight,    double yRight,    double zRight,
						double xView,     double yView,     double zView,
                        double xUp,       double yUp,       double zUp)
{
	m_vRight=dVector(1,0,0,0);
	m_vUp=dVector(0,1,0,0);
	m_vLookAt=dVector(0,0,1,0);

	m_viewTransformation.Identity();
	m_CamMatrix.Identity();

	m_CamMatrix.SetRight(xRight,yRight,zRight);
	m_CamMatrix.SetUpVector(xUp,yUp,zUp);
	m_CamMatrix.SetView(xView,yView,zView);
	
	m_bUseQuaternion=false;
}

void sseCamera::SetPosition(const dVector &v)
{
	m_CamMatrix.SetPosition(v);
}

void sseCamera::MoveCamera(const dVector &v)
{
	m_CamMatrix.SetPosition(m_CamMatrix.GetPosition()+v);
}

void sseCamera::SetPitch(double A)
{
	dMatrix44 m;

	if (m_bUseQuaternion) {
		dQuaternion qRotate;
		qRotate.AxisToQuat(m_vRight, A);
		m=qRotate.Get4x4Matrix();
	} else {
		m.AxisAngleRotate(m_vRight, A);	
	}

	m_vLookAt=(m_vLookAt*m).Normalize();
	m_vUp=(m_vUp*m).Normalize();
}

void sseCamera::SetRoll(double A)
{
	dMatrix44 m;

	if (m_bUseQuaternion) {
		dQuaternion qRotate;
		qRotate.AxisToQuat(m_vLookAt, A);
		m=qRotate.Get4x4Matrix();
	} else {
		m.AxisAngleRotate(m_vLookAt, A);	
	}
		
	m_vUp=(m_vUp*m).Normalize();
	m_vRight=(m_vRight*m).Normalize();
}

void sseCamera::SetYaw(double A)
{
	dMatrix44 m;

	if (m_bUseQuaternion) {
		dQuaternion qRotate;
		qRotate.AxisToQuat(m_vUp, A);
		m=qRotate.Get4x4Matrix();
	} else {
		m.AxisAngleRotate(m_vUp, A);	
	}

	m_vLookAt=(m_vLookAt*m).Normalize();
	m_vRight=(m_vRight*m).Normalize();
}

void sseCamera::UpdateView()
{
	if (m_bUpdateZoom)
	{
		m_pDisplay->SetProjectionMatrix(m_zDistance);
		m_bUpdateZoom=false;
	}

	m_CamMatrix.SetView(m_CamMatrix.GetRight()+m_vLookAt);
	m_CamMatrix.SetUpVector(m_vUp);

	// eyex, eyey, eyez	 	
    // Specifies the position of the eye point.
	// position of eye

	// centerx, centery, centerz	 	
	// Specifies the position of the reference point.
	// Position to look at

	// upx, upy, upz	 	
	// Specifies the direction of the up vector. 

	// Always:
	// [0] Position or Side    
	// [1] Up Vector
	// [2] View

	LookAt(m_CamMatrix);
}

void sseCamera::Update()
{
	HandleMotionEvents();
	UpdateView();
}

/*void sseCamera::LookAt(dVector position)
{
	m_vLookAt=position.Normalize();
}*/

void sseCamera::LookAt(dMatrix44 &matrix)
{
	dMatrix44 rotate;
	rotate.Identity();
	
	dVector viewDir=(matrix.GetView()-matrix.GetRight()).Normalize();
	dVector viewRight=viewDir.Cross(matrix.GetUpVector()).Normalize();
	dVector viewUp=viewRight.Cross(viewDir).Normalize();
	
	rotate.SetRows(viewRight, viewUp, -viewDir);

	rotate[0][3]=0;
	rotate[1][3]=0;
	rotate[2][3]=0;
	rotate[3][3]=1;

	rotate=rotate.Transpose();
	
	dMatrix44 translate;
	
	translate.Identity();
	
	translate[3][0]=-matrix.GetPosition()[0];
	translate[3][1]=-matrix.GetPosition()[1];
	translate[3][2]=-matrix.GetPosition()[2];
	
	m_viewTransformation=translate*rotate;
}

void sseCamera::Zoom(bool bForward)
{
	if (bForward){
		if (m_camZoom<10)
			m_camZoom+=1;
	} else if (m_camZoom>2) {
		m_camZoom-=1;
	}
	
	m_zDistance = m_camZoom/10.0;
	m_bUpdateZoom=true;
}

void sseCamera::SetClock(sseClock *pClock)
{
	m_pClock=pClock;
}

sseClock *sseCamera::getClock()
{
	return m_pClock;
}

void sseCamera::HandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion)
{ 
	if (m_pEventMappings->m_bMouseEventUp)
		SetPitch(-m_dRotSpeed);
	else if (m_pEventMappings->m_bMouseEventDown)
		SetPitch(m_dRotSpeed);

	if (m_pEventMappings->m_bMouseLBttnDown)
	{
		if (m_pEventMappings->m_bMouseEventRight)
			SetRoll((-m_dRotSpeed));
		else if (m_pEventMappings->m_bMouseEventLeft)
			SetRoll(m_dRotSpeed);
	}
	else if (m_pEventMappings->m_bMouseEventRight)
			SetYaw(m_dRotSpeed);
		else if (m_pEventMappings->m_bMouseEventLeft)
			SetYaw(-m_dRotSpeed);
}

void sseCamera::HandleMouseButtonEvents(SDL_MouseButtonEvent *pButton)
{
	if ((pButton->button==4)||(pButton->button==5))
	{
		Zoom(pButton->button==5);
	}
}

void sseCamera::HandleMotionEvents()
{
	double dt = m_pClock->GetElapsedTime();

	if (m_pEventMappings->m_bKeyEventFoward)
		MoveCamera(m_CamMatrix.GetDir()*(m_dSpeed*dt));
		
	if(m_pEventMappings->m_bKeyEventBackward)
		MoveCamera(m_CamMatrix.GetDir()*(-m_dSpeed*dt));

	if(m_pEventMappings->m_bKeyEventLeft)
		MoveCamera(m_CamMatrix.GetXAxis()*(m_dSpeed*dt));
	if(m_pEventMappings->m_bKeyEventRight)
		MoveCamera(m_CamMatrix.GetXAxis()*(-m_dSpeed*dt));

	if(m_pEventMappings->m_bKeyEventUp)
		MoveCamera(m_CamMatrix.GetYAxis()*(m_dSpeed*dt));
	if(m_pEventMappings->m_bKeyEventDown)
		MoveCamera(m_CamMatrix.GetYAxis()*(-m_dSpeed*dt));
}
