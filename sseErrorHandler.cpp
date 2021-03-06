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
#include "sseErrorHandler.hpp"
#include "sseLog.h"
#include "SDL_opengl.h"

sseErrorHandler::sseErrorHandler()
{
	
}

// ===================================================================
// _ThrowIfNull                                               [public]
// ===================================================================
// Throw exception if the given pointer is NULL.
void sseErrorHandler::_ThrowIfNull(void *ptr)
{
	if (ptr == NULL || ptr == (void *)DEBUG_NULL) {
		sseLog *log=sseLog::Instance();
		log->Error("Null Pointer Encountered!");
		throw sseErrorHandler (sseErrorCodes::ERROR_NULLPOINTER);
	}
}

void sseErrorHandler::_ThrowIfSDLInitFailed(int iError)
{
	if( iError < 0 )
	{
		sseLog *log=sseLog::Instance();
		log->Error("Failed initializing SDL Video: %s", SDL_GetError());
		cerr << "Failed initializing SDL Video : " << SDL_GetError() << endl;
		throw sseErrorHandler (sseErrorCodes::ERROR_NULLPOINTER);
	}
}

void sseErrorHandler::_ThrowIfSDLQueryFailed(SDL_RendererInfo *pVidInfo)
{
	if (pVidInfo == NULL || pVidInfo == (void *)DEBUG_NULL)
	{
		sseLog *log=sseLog::Instance();
		log->Error("Failed quering SDL Video hardware: %s", SDL_GetError());
		cerr << "Failed quering SDL Video hardware: " << SDL_GetError() << endl;
		throw sseErrorHandler (sseErrorCodes::ERROR_SDL_QUERY);
	}
}

void sseErrorHandler::_ThrowIfSDLWindowFail(SDL_Surface *pWindow)
{
	if (pWindow == NULL || pWindow == (void *)DEBUG_NULL)
	{
		sseLog *log=sseLog::Instance();
		log->Error("Failed to create window: %s", SDL_GetError());
		cerr << "Failed to create window: " << SDL_GetError() << endl;
		throw sseErrorHandler (sseErrorCodes::ERROR_SDL_WINDOW);
	}
}

void sseErrorHandler::_ThrowIfSDLFullScreenSwitch(int iError)
{
	if(iError == 0)
	{
		sseLog *log=sseLog::Instance();
		log->Error("Failed to Toggle Fullscreen mode: %s", SDL_GetError());
		cerr << "Failed to Toggle Fullscreen mode: " << SDL_GetError() << endl;
		throw sseErrorHandler (sseErrorCodes::ERROR_SDL_FULLSCREEN);
	}
}

void sseErrorHandler::_ThrowIfSDLUpdateFail(int iError)
{
	if(iError != 0)
	{
		sseLog *log=sseLog::Instance();
		log->Error("Failed to swap the buffers: %s", SDL_GetError());
		cerr << "Failed to swap the buffers: " << SDL_GetError() << endl;
		throw sseErrorHandler (sseErrorCodes::ERROR_SDL_FULLSCREEN);
	}
}

void sseErrorHandler::_LogIfSDLCursorFail(int iSDLCALL)
{
	if ( iSDLCALL != SDL_DISABLE ) {
		sseLog *log=sseLog::Instance();
		log->Error("Cursor Fail: %s", SDL_GetError());
		cerr << SDL_GetError() << endl;
	}
}

void sseErrorHandler::_ThrowIfSDLTextureLoadError()
{
	GLenum gl_error=glGetError();
	if ( gl_error != GL_NO_ERROR ) {
		/* If this failed, the text may exceed texture size limits */
		cout << gluErrorString(gl_error) << endl;
		printf("Warning: Couldn't create texture: 0x%x\n", gl_error);

		sseLog *log=sseLog::Instance();
		log->Error("Warning: Couldn't create texture: 0x%x\n", gl_error);

		throw sseErrorHandler (sseErrorCodes::ERROR_SDL_TEXTURE_LOAD);
	}
}

void sseErrorHandler::_ThrowIfEnableKeyRepFail(int iCall)
{
	if (iCall)
		throw sseErrorHandler (sseErrorCodes::ERROR_SDL_ENABLE_KEY_REPEAT);
}

void sseErrorHandler::_ThrowIfDisplayFail(sseDisplayManager *pCDisp)
{
	if (pCDisp == NULL || pCDisp == (void *)DEBUG_NULL)
		throw sseErrorHandler (sseErrorCodes::ERROR_DISPLAY_INIT);
}

void sseErrorHandler::_ThrowIfMatrixError(bool bTest)
{
	if (bTest) {
		sseLog *log=sseLog::Instance();
		log->Error("Matrix Math Error!");
		throw sseErrorHandler (sseErrorCodes::ERROR_MATRIX_SIZE);
	}
}

void sseErrorHandler::_ThrowIfMatrixSizeError(int rowSize, int colSize)
{
	if ((rowSize<=0) || (colSize<=0)) {
		sseLog *log=sseLog::Instance();
		log->Error("Matrix Size Error!");
		throw sseErrorHandler (sseErrorCodes::ERROR_MATRIX_INVALID_SIZE);
	}
}


void sseErrorHandler::_ThrowIfVectorError(bool bTest)
{
	if (bTest) {
		sseLog *log=sseLog::Instance();
		log->Error("Vector Error!");
		throw sseErrorHandler (sseErrorCodes::ERROR_VECTOR);
	}
}

void sseErrorHandler::_ThrowIfUnitVectorError(bool bTest)
{
	if (bTest) {
		sseLog *log=sseLog::Instance();
		log->Error("Unit Vector Error!");
		throw sseErrorHandler (sseErrorCodes::ERROR_UNIT_VECTOR);
	}
}

void sseErrorHandler::_ThrowIfFontError(int iError)
{
	if (iError<0)
		throw sseErrorHandler (sseErrorCodes::ERROR_FONT_INIT);
}

void sseErrorHandler::_ThrowIfFontLoadError(TTF_Font *font)
{
	if (font == NULL)
		throw sseErrorHandler (sseErrorCodes::ERROR_FONT_LOAD);
}

void sseErrorHandler::_ThrowIfFontRenderError(SDL_Surface *text)
{
	if (text == NULL)
		throw sseErrorHandler (sseErrorCodes::ERROR_FONT_RENDER);
}

void sseErrorHandler::_ThrowIfAC3DInitError(void *ptr, char *szFile)
{
	if(ptr == NULL)
	{
		sseLog *log=sseLog::Instance();
		log->Error("Failed to load AC3D: %s.", szFile);

		cerr << "Failed to load AC3D: " << szFile << endl;
		throw sseErrorHandler (sseErrorCodes::ERROR_AC3D_INIT);
	}
}

void sseErrorHandler::_ThrowIfAC3DDispError(int ac3dReturn, char *szFile)
{
	if((ac3dReturn == GL_INVALID_VALUE) || (ac3dReturn == GL_INVALID_OPERATION))
	{
		sseLog *log=sseLog::Instance();
		log->Error("Failed to load AC3D: %s.", szFile);

		cerr << "Failed to load AC3D: " << szFile << endl;
		throw sseErrorHandler (sseErrorCodes::ERROR_AC3D_DISP_RENDER);
	}
}

void sseErrorHandler::_ThrowIfOGLRendererError()
{
	GLenum gl_error=glGetError();
	if ( gl_error != GL_NO_ERROR ) {
		/* If this failed, the text may exceed texture size limits */
		cout << gluErrorString(gl_error) << endl;
		printf("Error: sseGrafxRenderer failed: 0x%x\n", gl_error);

		sseLog *log=sseLog::Instance();
		log->Error("Error: sseGrafxRenderer failed: 0x%x\n", gl_error);

		throw sseErrorHandler (sseErrorCodes::ERROR_OGL_RENDERER_FAILED);
	}
}

void sseErrorHandler::_ThrowIfUnitTestFail(bool bTest, char *szTestName)
{
	if (bTest) {
		cerr << "Failed to Run Unit Test: " << szTestName << "!" << endl;

		sseLog *log=sseLog::Instance();
		log->Error("Failed to Run Unit Test: %s!", szTestName);

		throw sseErrorHandler (sseErrorCodes::ERROR_UNIT_TEST_FAILED);
	}

	GLenum gl_error=glGetError();
	if ( gl_error != GL_NO_ERROR ) {
		/* If this failed, the text may exceed texture size limits */
		cout << gluErrorString(gl_error) << endl;
		printf("Error: OGL Unit Test Failed: 0x%x\n", gl_error);

		sseLog *log=sseLog::Instance();
		log->Error("Error: OGL Unit Test Failed: 0x%x\n", gl_error);

		throw sseErrorHandler (sseErrorCodes::ERROR_OGL_RENDERER_FAILED);
	}
}
