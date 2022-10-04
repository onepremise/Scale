//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Object Class
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
#include "sseObject.hpp"
#include "sseQuaternion.hpp"
#include "sseSceneLoader.hpp"

sseObject::sseObject() : sseEventObjectHandler(), sseConcurrentContextGuard()
{
	static int iObjID=0;
	stringstream sstm;

	m_parent=NULL;

	m_objectMatrix.Identity();
	m_center.Identity();
	m_rotation.Identity();
	m_scale.Identity();

	m_vPos=dVector(0, 0, 0, 1);
	m_velocity=dVector(0, 0, 0, 1);
	m_rotationalVelX=0;
    m_rotationalVelY=0;
    m_rotationalVelZ=0;

	m_PitchAdjust=0;
	m_RollAdjust=0;
	m_YawAdjust=0;

	m_Pitch=0;
	m_Roll=0;
	m_Yaw=0;

	m_fTime=1;

	m_iID = iObjID++;

	sstm << "Object-" << iObjID;

	m_strName=sstm.str();

	setName(m_strName);

	m_cullFace=true;

	m_destroy=false;
	m_isCollisionEnabled=false;
	m_isEnabled=true;
	m_isLocalSubNode=true;

	m_centerSet=false;
	m_scaleSet=false;

	m_numNodes=0;
	m_nodes=NULL;

	m_materialOff.presetColor(NONE);
}

sseObject::~sseObject()
{
	for (int i =0; i<m_numNodes; i++)
		delete m_nodes[i];

	delete [] m_nodes;
}

void sseObject::SetEnabled(bool enabled, bool includeChildren)
{
	m_isEnabled=enabled;

	if (!m_isLocalSubNode)
	{
		if (m_parent!=NULL) {
			
 			this->setPosition(m_parent->getWorldPosition());
		}
	}

	if (includeChildren)
	{
		for (int i=0; i<m_numNodes; i++)
			m_nodes[i]->SetEnabled(enabled);
	}
}

void sseObject::enableCulling(bool cull) {
	m_cullFace=cull;
}

void sseObject::setParent(sseObject *p) 
{ 
	m_parent=p;
};
	
sseObject *sseObject::getParent() 
{ 
	return m_parent;
};

void sseObject::AddNode(sseObject *pNode, bool bCollidable, bool enabled, bool isLocal)
{
	pNode->setParent(this);
	
	m_numNodes+=1;

	sseObject **nodes = new sseObject*[m_numNodes];

	//copy existing nodes and add new node
	for ( int i = 0; i < m_numNodes; i++ )
	{
		if (i<(m_numNodes-1))
			nodes[i]=m_nodes[i];
		else
			nodes[i]=pNode;
	}

	if (m_nodes!=NULL)
		delete [] m_nodes;

	m_nodes = nodes;
	
	pNode->SetCommandProcessor(m_command);
	pNode->SetCollisionEnabled(bCollidable);
	pNode->SetEnabled(enabled);
	pNode->SetClock(getClock());
	pNode->SetLocalNode(isLocal);

	if (!isLocal) {
		m_command->addSceneGraphNode(pNode);
	} else {
		pNode->affineTransform();
	}
}

void sseObject::Destroy() 
{
	m_destroy=true;
	m_isCollisionEnabled=false;
}

void sseObject::setCenter(double x, double y, double z)
{
	m_center.Identity();
	m_center[3][0]=x;
	m_center[3][1]=y;
	m_center[3][2]=z;

	m_centerSet=true;
}

void sseObject::setOrientation(double x, double y, double z) 
{
	m_Pitch=x;
	m_Yaw=y;
	m_Roll=z;
}

void sseObject::setPosition(double x, double y, double z)
{
	m_vPos[0]=x;
	m_vPos[1]=y;
	m_vPos[2]=z;
	m_vPos[3]=1;

	m_objectMatrix[3]=m_vPos;
}

void sseObject::setPosition(dVector vPosition)
{
	setPosition(vPosition[0], vPosition[1], vPosition[2]);
}

dVector sseObject::getWorldPosition()
{
	dMatrix concat=getWorldTransform();

	return dVector(concat[3][0],concat[3][1],concat[3][2],1);
}

dMatrix sseObject::getWorldTransform()
{
	dMatrix44 concat;

	concat.Identity();

	if (getParent()!=NULL) {
		concat=getParent()->getWorldTransform();
	}

	dMatrix44 &localT=*getLocalTransform();
		
	concat=localT*concat;

	return concat;
}

void sseObject::MoveForward(double length)
{
	m_vPos+=(m_objectMatrix.GetView()*length);
}

void sseObject::MoveLateral(double length)
{
	m_vPos+=(m_objectMatrix.GetRight()*length);
}

void sseObject::MoveUp(double length)
{
	m_vPos+=(m_objectMatrix.GetUpVector()*length);
}

void sseObject::SetXVelocity(double x)
{
	m_velocity[0]=x;
}

void sseObject::SetYVelocity(double y)
{
	m_velocity[1]=y;
}

void sseObject::SetZVelocity(double z)
{
	m_velocity[2]=z;
}

void sseObject::SetVelocity(double x, double y, double z)
{
	m_velocity[0]=x;
	m_velocity[1]=y;
	m_velocity[2]=z;
}

void sseObject::SetVelocity(dVector vVelocity)
{
	m_velocity[0]=vVelocity[0];
	m_velocity[1]=vVelocity[1];
	m_velocity[2]=vVelocity[2];

	vVelocity.Normalize();

	setOrientation(vVelocity.toPitch(), vVelocity.toYaw(), 0.0);
}

void sseObject::SetRotationalVel(double x, double y, double z)
{
	m_rotationalVelX=x;
	m_rotationalVelY=y;
	m_rotationalVelZ=z;
}

void sseObject::SetScale(double x, double y, double z)
{
	m_scale.Identity();
	m_scale.Scaling(dVector(x,y,z));
	m_scaleSet=true;
}

void sseObject::SetPitchAdjust(double p)
{
	m_PitchAdjust=p;
}

void sseObject::SetYawAdjust(double y)
{
	m_RollAdjust=y;
}

void sseObject::SetRollAdjust(double r)
{
	m_YawAdjust=r;
}

void sseObject::SetTimeStep(double fTime, bool includeChildren)
{
	m_fTime=fTime;
}

void sseObject::SetClock(sseClock *pClock, bool includeChildren)
{
	m_pClock=pClock;

	if (includeChildren)
	{
		for (int i=0; i<m_numNodes; i++)
			m_nodes[i]->SetClock(pClock);
	}
}

sseClock *sseObject::getClock()
{
	return m_pClock;
}

void sseObject::SetCommandProcessor(sseCommand *pCommand)
{
	m_command = pCommand;

	for (int i=0; i<m_numNodes; i++)
		m_nodes[i]->SetCommandProcessor(m_command);
}

void sseObject::processPhysics()
{
	if (!m_destroy) {
		double dt = m_pClock->GetElapsedTime();

		m_Pitch+=m_rotationalVelX*dt;
		m_Roll+=m_rotationalVelZ*dt;
		m_Yaw+=m_rotationalVelY*dt;

		m_vPos[0]+=(m_velocity[0]/m_fTime)*dt;
		m_vPos[1]+=(m_velocity[1]/m_fTime)*dt;
		m_vPos[2]+=(m_velocity[2]/m_fTime)*dt;
	}
}

void sseObject::affineTransform() 
{
	dQuaternion qRot;

	dQuaternion qRotX(vRight,m_PitchAdjust+m_Pitch);
	dQuaternion qRotY(vUp,m_YawAdjust+m_Yaw);
	dQuaternion qRotZ(vLookAt,m_RollAdjust+m_Roll);

	m_rotation=(qRotX*qRotY*qRotZ).Get4x4Matrix();
	
	m_rotation[3]=m_vPos;
	m_rotation[0][3]=0;
	m_rotation[1][3]=0;
	m_rotation[2][3]=0;
	m_rotation[3][3]=1;

	//TRST
	if (m_centerSet && m_scaleSet)
		m_objectMatrix=m_center*m_scale*m_rotation;
	else if (m_centerSet)
		m_objectMatrix=m_center*m_rotation;
	else if (m_scaleSet)
		m_objectMatrix=m_scale*m_rotation;
	else
		m_objectMatrix=m_rotation;
}

void sseObject::PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader) {
	if (m_cullFace)
		pRenderer->enableCulling(true);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0); //Sun

	pRenderer->setMaterial(m_materialDefault);
}

void sseObject::PostProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader) {
	if (m_cullFace)
		pRenderer->enableCulling(false);

	pRenderer->setMaterial(m_materialOff);

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, NULL);
}

void sseObject::HandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion)
{
	double dt = m_pClock->GetElapsedTime();

	if (m_pEventMappings->m_bMouseEventUp)
		m_Pitch+=0.08;
	else if (m_pEventMappings->m_bMouseEventDown)
		m_Pitch-=0.08;

	if (m_pEventMappings->m_bMouseLBttnDown)
	{
		if (m_pEventMappings->m_bMouseEventRight)
			m_Roll-=0.08;
		else if (m_pEventMappings->m_bMouseEventLeft)
			m_Roll+=0.08;
	}
	else if (m_pEventMappings->m_bMouseEventRight)
		m_Yaw+=0.05;
	else if (m_pEventMappings->m_bMouseEventLeft)
		m_Yaw-=0.08;
}

void sseObject::HandleMouseButtonEvents(SDL_MouseButtonEvent *pButton)
{

}

void sseObject::HandleKeyPressEvents(SDL_Scancode *pKeyCode)
{
	double dt = m_pClock->GetElapsedTime();

	if (m_pEventMappings->m_bKeyEventFoward)
		m_vPos=m_vPos+(m_objectMatrix.GetView()*10)*dt;
		
	if(m_pEventMappings->m_bKeyEventBackward)
		m_vPos=m_vPos-(m_objectMatrix.GetView()*10)*dt;

	if(m_pEventMappings->m_bKeyEventLeft)
		m_vPos=m_vPos+(m_objectMatrix.GetRight()*10)*dt;
	if(m_pEventMappings->m_bKeyEventRight)
		m_vPos=m_vPos-(m_objectMatrix.GetRight()*10)*dt;

	if(m_pEventMappings->m_bKeyEventUp)
		m_vPos=m_vPos+(vUp*10)*dt;
	if(m_pEventMappings->m_bKeyEventDown)
		m_vPos=m_vPos+(vUp*-10)*dt;
}

void sseObject::HandleKeyReleaseEvents(SDL_Scancode *pKeyCode)
{

}
