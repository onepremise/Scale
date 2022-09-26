//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Event Handler Queue
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//=========================================================
#include "sseEventHandler.hpp"
#include "sseEngine.hpp"
#include "sseDisplayManager.hpp"
#include "sseObject.hpp"

objEventHandlerQueue sseEventHandler::m_objEHQueue;
objEventHandlerQueue sseEventHandler::m_objInactiveEHQueue;
sseEventMappings sseEventHandler::m_EventMappings;

float sseEventHandler::m_fCurrentX;
float sseEventHandler::m_fCurrentY;
float sseEventHandler::m_fLastX;
float sseEventHandler::m_fLastY;

sseEventHandler::sseEventHandler(sseEngine *pEngine)
{
	m_pEngine=pEngine;
	m_pDisplay=sseDisplayManager::Instance();

	m_fCurrentX=m_pDisplay->GetCenterX();
	m_fCurrentY=m_pDisplay->GetCenterY();
	m_fLastX=m_pDisplay->GetCenterX();
	m_fLastY=m_pDisplay->GetCenterY();

	m_bHasFocus=true;
}

void sseEventHandler::HandleEvents()
{
	SDL_Event sdlEvent;

	while( SDL_PollEvent(&sdlEvent))
	{
		if (sdlEvent.type == SDL_WINDOWEVENT)
		{
			switch (sdlEvent.window.event) {
	        case SDL_WINDOWEVENT_SHOWN:
	        	m_bHasFocus=true;
	        	m_pDisplay->SetCursorCenter();
	            break;
	        case SDL_WINDOWEVENT_HIDDEN:
	        	m_bHasFocus=false;
	        	break;
	        case SDL_WINDOWEVENT_FOCUS_GAINED:
	        	m_bHasFocus=true;
	        	m_pDisplay->SetCursorCenter();
	            break;
	        case SDL_WINDOWEVENT_FOCUS_LOST:
	        	m_bHasFocus=false;
	        	break;
	        case SDL_WINDOWEVENT_ENTER:
	        	m_bHasFocus=true;
	        	m_pDisplay->SetCursorCenter();
	            break;
	        case SDL_WINDOWEVENT_LEAVE:
	        	m_bHasFocus=false;
	        	break;
			case SDL_WINDOWEVENT_RESIZED:
				m_pDisplay->ReSizeOpenGLWindow(sdlEvent.window.data1, sdlEvent.window.data2);
				break;
			}
		}
		else if((sdlEvent.type == SDL_WINDOWEVENT_RESIZED) || (sdlEvent.type == SDL_WINDOWEVENT_SIZE_CHANGED))
        {	
			m_pDisplay->ReSizeOpenGLWindow(sdlEvent.window.data1, sdlEvent.window.data2);
		}
		else if( sdlEvent.type == SDL_WINDOWEVENT_EXPOSED )
        {	
			m_pDisplay->Flip();
		}
		else if (m_bHasFocus)
			ProcessEvents(sdlEvent);
	}
}

void sseEventHandler::ProcessEvents(SDL_Event &sdlEvent) 
{
	switch ( sdlEvent.type )
	{
	case SDL_KEYDOWN:
		HandleKeyPressEvents( &sdlEvent.key.keysym.scancode );
		break;
	case SDL_KEYUP:
		HandleKeyReleaseEvents(&sdlEvent.key.keysym.scancode);
		break;
	case SDL_MOUSEMOTION:
		HandleMouseMotionEvents(&sdlEvent.motion);
		break;
	case SDL_MOUSEBUTTONDOWN:
		HandleMouseButtonEvents(&sdlEvent.button);
		break;
	case SDL_MOUSEBUTTONUP:
		HandleMouseButtonEvents(&sdlEvent.button);
		break;
    case SDL_MOUSEWHEEL:
        break;
	default: 
		break;
	}
}

void sseEventHandler::AddObjectToQueue(sseEventObjectHandler *pOEH)
{
	objEHQIter it = find (m_objInactiveEHQueue.begin(), m_objInactiveEHQueue.end(), pOEH);

	if (it!=m_objInactiveEHQueue.end())
	{
		m_objInactiveEHQueue.erase(it);
		m_objEHQueue.push_back(pOEH);
	} else {
		it = find (m_objEHQueue.begin(), m_objEHQueue.end(), pOEH);

		if (it==m_objEHQueue.end())
			m_objEHQueue.push_back(pOEH);
	}
}

void sseEventHandler::RemoveObjectFromQueue(sseEventObjectHandler *pOEH)
{
	objEHQIter it = find (m_objEHQueue.begin(), m_objEHQueue.end(), pOEH);

	if (it!=m_objEHQueue.end())
		m_objEHQueue.erase(it);

	it = find (m_objInactiveEHQueue.begin(), m_objInactiveEHQueue.end(), pOEH);

	if (it==m_objInactiveEHQueue.end())
		m_objInactiveEHQueue.push_back(pOEH);
}

void sseEventHandler::HandleKeyPressEvents(SDL_Scancode *pKeyCode)
{
    switch(*pKeyCode)
    {
        case SDL_SCANCODE_F1:
            printHelp();
            break;
		case SDL_SCANCODE_F2:
			m_pEngine->PauseSimulation();
            break;
		case SDL_SCANCODE_F3:
			m_pEngine->ResetSimulation();
            break;
		case SDL_SCANCODE_F4:
            break;
		case SDL_SCANCODE_F5:
            break;
		case SDL_SCANCODE_F6:
            break;
		case SDL_SCANCODE_F7:
            break;
		case SDL_SCANCODE_F8:
            break;
		case SDL_SCANCODE_F9:
            break;
		case SDL_SCANCODE_F10:
            break;
		case SDL_SCANCODE_F11:
			cycleHandling();
            break;
		case SDL_SCANCODE_F12:
			m_pDisplay->SwitchToFullScreen();
            break;
        case SDL_SCANCODE_ESCAPE:
			m_pEngine->ShutdownSimulator();
			break;
		case SDL_SCANCODE_UP:
		case SDL_SCANCODE_W:
			m_EventMappings.m_bKeyEventFoward=true;
			break;
		case SDL_SCANCODE_DOWN:
		case SDL_SCANCODE_S:
			m_EventMappings.m_bKeyEventBackward=true;
			break;
        case SDL_SCANCODE_Q:
            m_EventMappings.m_bKeyEventUp=true; 
            break;            
       case SDL_SCANCODE_Z:
            m_EventMappings.m_bKeyEventDown=true;
            break;
       case SDL_SCANCODE_RIGHT:
       case SDL_SCANCODE_D:
            m_EventMappings.m_bKeyEventRight=true;
            break;
       case SDL_SCANCODE_LEFT:
       case SDL_SCANCODE_A:
            m_EventMappings.m_bKeyEventLeft=true;
            break;
        default:
            break;
    }
	objHandleKeyPressEvents(pKeyCode);
}

void sseEventHandler::printHelp()
{
	fprintf(stdout, "\nSSE - uses keyboard input to control the "
		"location of the reference point point\n\n"
		"F1 Key			 - print Help information\n"
		"F2 Key			 - start/stop simulation\n"
		"F3 Key			 - reset simulation\n"
		"F11 Key		 - switch to camera or back to object\n"
		"F12 Key         - toggle fullscreen mode (Exprimental!)\n"
		"Left Arrow Key	 - move reference point to the left\n"
		"Right Arrow Key - move reference point to the right\n"
		"Up Arrow Key	 - move reference point up\n"
		"Down Arrow Key	 - move reference point down\n"
		"Escape Key		 - exit the program\n\n");
}

void sseEventHandler::cycleHandling()
{
	objEHQIter it = m_objEHQueue.begin();

	while (!m_objEHQueue.empty()) {
		(*it)->DeclineEvents();
		it = m_objEHQueue.begin();
	}

	it = m_objInactiveEHQueue.begin();

	sseEventObjectHandler *pObjHandle=(*it);

	pObjHandle->AcceptEvents();

	String strName="Switching to object: ";

	strName+=pObjHandle->getName();
	strName+="...\n";

	fprintf(stdout, strName.c_str());
}

void sseEventHandler::HandleKeyReleaseEvents(SDL_Scancode *pKeyCode)
{
	switch(*pKeyCode)
    {
        case SDL_SCANCODE_UP:
		case SDL_SCANCODE_W:
			m_EventMappings.m_bKeyEventFoward=false;
			break;
		case SDL_SCANCODE_DOWN:
		case SDL_SCANCODE_S:
			m_EventMappings.m_bKeyEventBackward=false;
			break;
        case SDL_SCANCODE_Q:
            m_EventMappings.m_bKeyEventUp=false; 
            break;            
       case SDL_SCANCODE_Z:
            m_EventMappings.m_bKeyEventDown=false;
            break;
        case SDL_SCANCODE_RIGHT:
        case SDL_SCANCODE_D:
            m_EventMappings.m_bKeyEventRight=false;
            break;
        case SDL_SCANCODE_LEFT:
        case SDL_SCANCODE_A :
            m_EventMappings.m_bKeyEventLeft=false;
            break;

        default:
            break;
    }
	objHandleKeyReleaseEvents(pKeyCode);
}

void sseEventHandler::objHandleKeyPressEvents(SDL_Scancode *pKeyCode)
{
	for (objEHQIter it = m_objEHQueue.begin(); it != m_objEHQueue.end(); it++)
		(*it)->HandleKeyPressEvents(pKeyCode);
}

void sseEventHandler::objHandleKeyReleaseEvents(SDL_Scancode *pKeyCode)
{
	for (objEHQIter it = m_objEHQueue.begin(); it != m_objEHQueue.end(); it++)
		(*it)->HandleKeyReleaseEvents(pKeyCode);
}

void sseEventHandler::AssignCurMouseCoordinates(SDL_MouseMotionEvent *pMotion)
{
	if(pMotion->x!=0)
	{
		m_fCurrentX=pMotion->x;
		if (m_fCurrentX>m_fLastX)
			m_EventMappings.m_bMouseEventRight=true;
		if (m_fCurrentX<m_fLastX)
			m_EventMappings.m_bMouseEventLeft=true;
	}

	if(pMotion->y!=0)
	{
		m_fCurrentY=pMotion->y;
		if (pMotion->y>m_fLastY)
			m_EventMappings.m_bMouseEventUp=true;
		if (pMotion->y<m_fLastY)
			m_EventMappings.m_bMouseEventDown=true;
	}
}

void sseEventHandler::AssignLastMouseCoordinates(SDL_MouseMotionEvent *pMotion)
{
	float x=m_pDisplay->GetWidth();
	float y=m_pDisplay->GetHeight();

	m_fLastX=m_fCurrentX;
	m_fLastY=m_fCurrentY;

	m_EventMappings.m_bMouseEventRight=false;
	m_EventMappings.m_bMouseEventUp=false;
	m_EventMappings.m_bMouseEventLeft=false;
	m_EventMappings.m_bMouseEventDown=false;
}

void sseEventHandler::HandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion)
{
	AssignCurMouseCoordinates(pMotion);

	objHandleMouseMotionEvents(pMotion);

	AssignLastMouseCoordinates(pMotion);
}

void sseEventHandler::objHandleMouseMotionEvents(SDL_MouseMotionEvent *pMotion)
{
	for (objEHQIter it = m_objEHQueue.begin(); it != m_objEHQueue.end(); it++)
		(*it)->HandleMouseMotionEvents(pMotion);
}

void sseEventHandler::HandleMouseButtonEvents(SDL_MouseButtonEvent *pButton)
{
	if ((pButton->button==1) && (pButton->state==SDL_PRESSED))
	{
		m_EventMappings.m_bMouseLBttnDown=true;
		cerr << "Left Button " << endl;
	}
	if ((pButton->button==2) && (pButton->state==SDL_PRESSED))
	{
		m_EventMappings.m_bMouseMBttnDown=true;
		cerr << "Middle Button " << endl;
	}
	if ((pButton->button==3) && (pButton->state==SDL_PRESSED))
	{
		m_EventMappings.m_bMouseRBttnDown=true;
		cerr << "Right Button " << endl;
	}

	if ((pButton->button==4) && (pButton->state==SDL_PRESSED))
	{
		m_EventMappings.m_eScrollButton=sseEventMappings::SSESCROLLUP;
		cerr << "Scroll Up " << endl;
	}

	if ((pButton->button==5) && (pButton->state==SDL_PRESSED))
	{
		m_EventMappings.m_eScrollButton=sseEventMappings::SSESCROLLDOWN;
		cerr << "Scroll Down " << endl;
	}

	if ((pButton->button==1) && (pButton->state==SDL_RELEASED))
		m_EventMappings.m_bMouseLBttnDown=false;
	if ((pButton->button==2) && (pButton->state==SDL_RELEASED))
		m_EventMappings.m_bMouseMBttnDown=false;
	if ((pButton->button==3) && (pButton->state==SDL_RELEASED))
		m_EventMappings.m_bMouseRBttnDown=false;
	if ((pButton->button==4) && (pButton->state==SDL_RELEASED))
		m_EventMappings.m_eScrollButton=sseEventMappings::SSENOMOTION;
	if ((pButton->button==5) && (pButton->state==SDL_RELEASED))
		m_EventMappings.m_eScrollButton=sseEventMappings::SSENOMOTION;

	cerr << "x " << pButton->x << endl;
	cerr << "y " << pButton->y << endl;
	cerr << endl;

	objHandleMouseButtonEvents(pButton);
}

void sseEventHandler::objHandleMouseButtonEvents(SDL_MouseButtonEvent *pButton)
{
	for (objEHQIter it = m_objEHQueue.begin(); it != m_objEHQueue.end(); it++)
		(*it)->HandleMouseButtonEvents(pButton);
}
