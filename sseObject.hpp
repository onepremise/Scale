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
#ifndef __SSEOBJECT__
#define __SSEOBJECT__

#include "sseInclude.hpp"
#include "sseConcurrentContextGuard.hpp"
#include "sseEventObjectHandler.hpp"
#include "sseMathEngine.hpp"
#include "GRFX/sseGrafxInterface.hpp"
#include "sseTexture.h"
#include "sseMaterial.h"
#include "sseClock.hpp"

using namespace ssemath;

const static dVector vRight(1,0,0,0);
const static dVector vLookAt(0,0,1,0);
const static dVector vUp(0,1,0,0);

class sseCommand;

class sseObject: public sseEventObjectHandler, public sseConcurrentContextGuard
{
public:
	sseObject();
	virtual ~sseObject();

	int getID() { return m_iID; };

	void setParent(sseObject *p);
	sseObject *getParent();

	virtual void AddNode(sseObject *pNode, bool bCollidable, bool enabled=true, bool isLocal=true);
	sseObject **getNodes() { return m_nodes; };

	int getNumNodes() { return m_numNodes; };

	void SetLocalNode(bool isLocal) {m_isLocalSubNode=isLocal;}
	bool isLocalNode() {return m_isLocalSubNode;}

	virtual bool isEnabled() {return m_isEnabled;}
	virtual void SetEnabled(bool enabled, bool includeChildren=true);

	virtual bool isCollisionEnabled() {return m_isCollisionEnabled;}
	virtual void SetCollisionEnabled(bool enabled) {m_isCollisionEnabled=enabled;}

	virtual bool isDestroyed() {return m_destroy;}
	virtual void Destroy();

	virtual void setCenter(double x, double y, double z);
	virtual void setOrientation(double x, double y, double z);
	virtual void setPosition(double x, double y, double z);
	virtual void setPosition(dVector vPosition);
	virtual dVector getPosition() {return m_vPos;};
	virtual dVector getWorldPosition();

	virtual dMatrix getWorldTransform();

	virtual void MoveForward(double length);
	virtual void MoveLateral(double length);
	virtual void MoveUp(double length);

	virtual void SetXVelocity(double x);
	virtual void SetYVelocity(double y);
	virtual void SetZVelocity(double z);
	virtual void SetVelocity(double x, double y, double z);
	virtual void SetVelocity(dVector vVelocity);
	virtual void SetRotationalVel(double x, double y, double z);
	virtual void SetScale(double x, double y, double z);

	virtual void SetPitchAdjust(double p);
	virtual void SetYawAdjust(double y);
	virtual void SetRollAdjust(double r);

	virtual void SetTimeStep(double fTime, bool includeChildren=true);
	virtual double GetTimeStep() { return m_fTime; };

	void SetClock(sseClock *pClock, bool includeChildren=true);
	sseClock *getClock();

	void SetCommandProcessor(sseCommand *pCommand);

	void enableCulling(bool cull);

	dMatrix44 *getLocalTransform() { return &m_objectMatrix; };

	//make opengl stack calls on event handlers
	virtual void HandleKeyPressEvents(SDL_Scancode *pKeyEvent);
	virtual void HandleKeyReleaseEvents(SDL_Scancode *pKeyEvent);
	virtual void HandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion);
	virtual void HandleMouseButtonEvents(SDL_MouseButtonEvent *pButton);

	virtual String getName() 
	{
		return m_strName;
	}

	virtual void setName(String strName)
	{
		m_strName=strName;
	}

protected:
 	virtual void Load(sseTexture *pTextureLoader) {return;};
	virtual void processPhysics();
	virtual void affineTransform();
	virtual void PreProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);
	virtual void DrawObject(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader) {return;}
	virtual void PostProcess(sseGrafxInterface *pRenderer, sseTexture *pTextureLoader);

protected:
	dMatrix44 m_objectMatrix;
	dMatrix44 m_scale;
	dMatrix44 m_center;
	dMatrix44 m_rotation;
	dVector m_vPos;
	dVector m_velocity;

	double m_rotationalVelX;
	double m_rotationalVelY;
	double m_rotationalVelZ;

	double m_Pitch;
	double m_Roll;
	double m_Yaw;

	double m_PitchAdjust;
	double m_RollAdjust;
	double m_YawAdjust;

	double m_fTime;

	bool m_centerSet;
	bool m_scaleSet;
	bool m_destroy;

protected:
	sseMaterial m_materialOff;
	sseMaterial m_materialDefault;

protected:
	sseClock *m_pClock;
	sseCommand *m_command;

private:
	String m_strName;

	bool m_isCollisionEnabled;
	bool m_isEnabled;

	int  m_iID;

	sseObject *m_parent;

	int m_numNodes;
	sseObject **m_nodes;

private:
	bool m_usingCenter;
	bool m_cullFace;

	bool m_isLocalSubNode;
};

#endif
