//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Debris Field
//
// License:
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
#include "sseDebrisField.h"
#include "sseParticle.hpp"
#include "sseCamera.hpp"
#include "sseCommand.hpp"
#include "sseParticleEmitter.hpp"
#include <fstream>
#include "sseTestObjects.hpp"

#define MAX_NUM_DEBRIS       10000

#if defined MAX_INTERLACE
#define INTERLACING          10 // Release
#else
#define INTERLACING          80 // Debug
#endif

sseDebrisField::sseDebrisField(void) : sseObject()
{
	stringstream sstm;

	sstm << "DebrisField-" << getID();

	setName(sstm.str());

	//m_strDelimiter="	";
	m_strDelimiter="       ";

	color[0]=0.7;
	color[1]=0.7;
	color[2]=0.7;

	m_bStart=false;
	this->AcceptEvents();
}

void sseDebrisField::Load(sseTexture *pTextureLoader)
{
	LoadExplosion();
}

void sseDebrisField::LoadExplosion()
{
	sseParticleEmitter *emitter=new sseParticleEmitter();

	AddNode(emitter, false, false, false);
}

void sseDebrisField::LoadFragments(String strFilename)
{
	fstream fsInFile(strFilename.c_str(), ios::in | ios::binary);
	char   szBuffer[1024]={0};
	int    iLine=1;
	int    iInterlace=INTERLACING;

	while(fsInFile.getline(szBuffer, 1024) && iLine<=MAX_NUM_DEBRIS)
	{
		if (iLine==iInterlace)
		{
			ProcessRow(szBuffer);
			iInterlace+=INTERLACING;
		}

		memset(szBuffer,0,sizeof(szBuffer));
		iLine++;
	}

	cerr << "Lines processed: " << iLine << endl;

	fsInFile.close();
}

void sseDebrisField::ProcessRow(String strBufRow)
{
	int iDelPos    = 0;
	int iDemLen    = m_strDelimiter.length();
	int iIndex     = 0;
	String strFld;

	sseDebris *debris=new sseDebris();

	debris->SetTimeStep(GetTimeStep());
	debris->SetScale(2,2,2);
	debris->SetColor(color[0], color[1], color[2]);

	do
	{
		iDelPos=strBufRow.find(m_strDelimiter);

		if(iDelPos<String::npos)
		{
			strFld=strBufRow.substr(0, iDelPos);
			strBufRow=strBufRow.substr((iDelPos+iDemLen), strBufRow.length());
		}
		else
		{
			iDelPos=strBufRow.find_last_of("\"");
			strFld=strBufRow.substr(1,(iDelPos>0) ? iDelPos-1 : iDelPos);
			iDelPos=String::npos;
		}

		if(!strFld.empty()) ProcessField(iIndex,strFld,*debris);
		
		iIndex++;
	} while (iDelPos<String::npos);

	AddNode(debris, false, false);
}

void sseDebrisField::ProcessField(int iIndex, String StrFld, sseDebris &debris)
{
	double value;
	stringstream sstm;

	sstm.precision(5);

	sstm << StrFld;
	sstm >> value;
	//sstm << scientific << StrFld << endl;

	if (iIndex==0)
	{
		//Xdot (m/s)

		debris.SetXVelocity(value/1000);//convert to km/s
	} 
	else if (iIndex==1)
	{
		//Ydot (m/s)
		//Swap y and z to convert to left handed system
		//debris.SetZVelocity(value);

		debris.SetYVelocity(value/1000);
	}
	else if (iIndex==2)
	{
		//Zdot (m/s)
		//Swap y and z to convert to left handed system

		debris.SetZVelocity(value/1000);

		//debris.SetYVelocity(value);
	}
	else if (iIndex==3)
	{
		//beta
	}
	else if (iIndex==4)
	{
		//Temp
	}
	else if (iIndex==5)
	{
		//length
		debris.SetLength(value);
	}
	else if (iIndex==6)
	{
		//width
		debris.SetWidth(value);
	}
	else if (iIndex==7)
	{
		//height
		debris.SetHeight(value);
	}
	else if (iIndex==8)
	{
		//min
	}
	else if (iIndex==9)
	{
		//max
	}
	else if (iIndex==10)
	{
		//spin is in hertz
		//float radians=deg_to_rad(value);
		//convert to rads/sec
		//w(rad/s) = 2pxf(Hz)
		float radspersec=SSE_2PI*value;

		//m/s
		//the tangential velocity is equal to the angular 
		//velocity multiplied by the radius
		//divide by 1000 to convert to km/s

		float xVel=(radspersec*debris.GetWidth()/2); 
		float yVel=(radspersec*debris.GetHeight()/2);
		float zVel=(radspersec*debris.GetLength()/2);

		debris.SetRotationalVel(xVel, yVel, zVel);
	}
	else if (iIndex==11)
	{
		//mass
	}
}

void sseDebrisField::setColor(int R, int G, int B)
{
	color[0]=R;
	color[1]=G;
	color[2]=B;
}

void sseDebrisField::HandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion)
{

}

void sseDebrisField::HandleMouseButtonEvents(SDL_MouseButtonEvent *pButton)
{

}

void sseDebrisField::HandleKeyPressEvents(SDL_Scancode *pKeyEvent)
{

}

void sseDebrisField::HandleKeyReleaseEvents(SDL_Scancode *pKeyEvent)
{

}
