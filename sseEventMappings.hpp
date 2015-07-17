//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Event Mappings to Keyboard
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//=========================================================
#ifndef __SSEEVENTMAPPINGS__
#define __SSEEVENTMAPPINGS__

class sseEventMappings
{
public:
	sseEventMappings()
	{
		m_bKeyEventFoward=false;
		m_bKeyEventBackward=false;
		m_bKeyEventDown=false;
		m_bKeyEventUp=false;
		m_bKeyEventLeft=false;
		m_bKeyEventRight=false;

		m_bMouseEventRight=false;
		m_bMouseEventUp=false;
		m_bMouseEventLeft=false;
		m_bMouseEventDown=false;

		m_bMouseLBttnDown=false;
		m_bMouseMBttnDown=false;
		m_bMouseRBttnDown=false;

		m_bMouseLBttnUp=false;
		m_bMouseMBttnUp=false;
		m_bMouseRBttnUp=false;

		m_eScrollButton=SSENOMOTION;
	}

public:
	bool m_bKeyEventFoward;
	bool m_bKeyEventBackward;
	bool m_bKeyEventDown;
	bool m_bKeyEventUp;
	bool m_bKeyEventLeft;
	bool m_bKeyEventRight;

	bool m_bMouseEventRight;
	bool m_bMouseEventLeft;
	bool m_bMouseEventUp;
	bool m_bMouseEventDown;

	bool m_bMouseLBttnDown;
	bool m_bMouseMBttnDown;
	bool m_bMouseRBttnDown;

	bool m_bMouseLBttnUp;
	bool m_bMouseMBttnUp;
	bool m_bMouseRBttnUp;

public:
	enum ScrollButton
	{
		SSESCROLLUP,
		SSENOMOTION,
		SSESCROLLDOWN
	};

	ScrollButton m_eScrollButton;
};

#endif
