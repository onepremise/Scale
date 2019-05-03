//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Error Exception Handling
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//=========================================================
#ifndef __SSEERRORHANDLE__
#define __SSEERRORHANDLE__

#pragma warning(disable:4786)

#include <iostream>
#include <string>
#include <list>
#include <map>

//#include "SDL.h"
//#include "SDL_ttf.h"

using namespace std;

class sseErrorHandler;
class sseErrorCodes;
class sseDisplayManager;

typedef map<const int, const char *> multimap_error;
typedef list<sseErrorCodes> lstErrors;

#define DEBUG_NULL 0xcdcdcdcd

class sseErrorCodes
{
friend class sseErrorHandler;
public:

	enum errIdentifier
	{
		ERROR_UNEXPECTED,
		ERROR_NULLPOINTER,
		ERROR_INIT,
		ERROR_QUERY,
		ERROR_WINDOW,
		ERROR_UPDATE,
		ERROR_FULLSCREEN,
		ERROR_CURSOR,
		ERROR_ENABLE_KEY_REPEAT,
		ERROR_TEXTURE_LOAD,
		ERROR_DISPLAY_INIT,
		ERROR_MATRIX_SIZE,
		ERROR_MATRIX_INVALID_SIZE,
		ERROR_VECTOR,
		ERROR_UNIT_VECTOR,
		ERROR_FONT_INIT,
		ERROR_FONT_LOAD,
		ERROR_FONT_RENDER,
		ERROR_AC3D_INIT,
		ERROR_AC3D_DISP_RENDER,
		ERROR_OGL_RENDERER_FAILED,
		ERROR_UNIT_TEST_FAILED
	};

	const char *getErrMessage(int errCode) {return m_errCodes[errCode];}

private:
// ===================================================================
// sseErrorCodes                                              [public]
// ===================================================================
// Constructor - constructs list of error message translations

	sseErrorCodes()
	{
		m_errCodes[ERROR_UNEXPECTED]="Unexpected Error!";
		m_errCodes[ERROR_NULLPOINTER]="Null Exception!";
		m_errCodes[ERROR_INIT]="Failed initializing SDL Video!";
		m_errCodes[ERROR_QUERY]="SDL Cannot query your video hardware!";
		m_errCodes[ERROR_WINDOW]="SDL failed to create window!";
		m_errCodes[ERROR_UPDATE]="Failed to swap the buffers!";
		m_errCodes[ERROR_FULLSCREEN]="Failed to switch to Fullscreen mode!";
		m_errCodes[ERROR_CURSOR]="Failed to switch to Fullscreen mode!";
		m_errCodes[ERROR_ENABLE_KEY_REPEAT]="Failed to enable key repeat!";
		m_errCodes[ERROR_TEXTURE_LOAD]="Failed to load texture!";
		m_errCodes[ERROR_DISPLAY_INIT]="Display Initialization Error!";
		m_errCodes[ERROR_MATRIX_SIZE]="Matrix Algebra Error!";
		m_errCodes[ERROR_MATRIX_INVALID_SIZE]="Matrix Algebra Error, invalid size!";
		m_errCodes[ERROR_VECTOR]="Vector Algebra Error!";
		m_errCodes[ERROR_UNIT_VECTOR]="Not a Unit Vector!";
		m_errCodes[ERROR_FONT_INIT]="Couldn't initialize font library!";
		m_errCodes[ERROR_FONT_LOAD]="Couldn't load font!";
		m_errCodes[ERROR_FONT_RENDER]="Couldn't render font!";
		m_errCodes[ERROR_AC3D_INIT]="Couldn't load AC3D!";
		m_errCodes[ERROR_AC3D_DISP_RENDER]="Couldn't initialize display list for AC3D!";
		m_errCodes[ERROR_OGL_RENDERER_FAILED]="Exception occured in renderer!";
		m_errCodes[ERROR_UNIT_TEST_FAILED]="Exception occured running unit tests!";
	}

	multimap_error m_errCodes;
};

class sseErrorHandler
{
public:
	sseErrorHandler();
	sseErrorHandler(int errCode) {m_errCode=errCode;}

	const int getErrorCode() {return m_errCode;}

	const char *getErrMessage()
	{
		return m_errorCodes.getErrMessage(m_errCode);
	}

	static void _ThrowIfNull(void *ptr);
	static void _ThrowIfInitFailed(int iError);
	//static void _ThrowIfSDLQueryFailed(SDL_RendererInfo *pVidInfo);
	static void _ThrowIfWindowFail(void *ptr);
	static void _ThrowIfSDLUpdateFail(int iError);
	static void _ThrowIfSDLFullScreenSwitch(int iError);
	static void _LogIfSDLCursorFail(int iSDLCALL);
	static void _ThrowIfSDLTextureLoadError();
	static void _ThrowIfEnableKeyRepFail(int iCall);
	static void _ThrowIfDisplayFail(sseDisplayManager *pCDisp);
	static void _ThrowIfMatrixError(bool bTest);
	static void _ThrowIfMatrixSizeError(int rowSize, int colSize);
	static void _ThrowIfVectorError(bool bTest);
	static void _ThrowIfUnitVectorError(bool bTest);
	static void _ThrowIfFontError(int iError);
	//static void _ThrowIfFontLoadError(TTF_Font *font);
	//static void _ThrowIfFontRenderError(SDL_Surface *text);
	static void _ThrowIfAC3DInitError(void *ptr, char *szFile);
	static void _ThrowIfAC3DDispError(int ac3dReturn, char *szFile);
	static void _ThrowIfOGLError(sseErrorCodes::errIdentifier e, const char *szArea);
	static void _ThrowIfOGLDisplayError();
	static void _ThrowIfOGLRendererError();
	static void _ThrowIfUnitTestFail(bool bTest, char *szTestName);

private:
	static sseErrorCodes m_errorCodes;
	int                  m_errCode;

};

#endif
