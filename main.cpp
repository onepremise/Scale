//========================================================
//              Scaled Simulator Engine
//
//  Author:       Jason Huntley
//
//  Description:  Entry Point
//
//  Notes:
//  
//     Date         Description         Initials  Location
//---------------------------------------------------------
//  12/11/2004    Initial Coding          JAH
//=========================================================
#include "sseInclude.hpp"
#include "sseEngine.hpp"
#include "sseMath.hpp"

sseErrorCodes sseErrorHandler::m_errorCodes;

int main(int argc, char *argv[])
{
	sseEngine *engine;

	try {
		engine=sseEngine::Instance();

		engine->StartSimulation();
	} catch (sseErrorHandler error) {
		SDL_Quit();

		sseLog *log=sseLog::Instance();

		log->Error(error.getErrMessage());

		cerr << error.getErrMessage()  << endl;
	}

	delete engine;

	return 0;
}
