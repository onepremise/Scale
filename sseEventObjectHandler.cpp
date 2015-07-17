//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Object Event Handler
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//=========================================================
#include "sseEventObjectHandler.hpp"
#include "sseEventHandler.hpp"

sseEventObjectHandler::sseEventObjectHandler()
{
	DeclineEvents();
}

sseEventObjectHandler::~sseEventObjectHandler()
{
	DeclineEvents();
}

void sseEventObjectHandler::AcceptEvents()
{
	sseEventHandler::AddObjectToQueue(this);
	m_pEventMappings=sseEventHandler::GetEventMappings();
}

void sseEventObjectHandler::DeclineEvents()
{
	sseEventHandler::RemoveObjectFromQueue(this);
	m_pEventMappings=&m_EmptyMap;
}