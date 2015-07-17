#pragma once

#include "sseInclude.hpp"
#include "sseMathEngine.hpp"

using namespace ssemath;

class sseUnitTests
{
public:
	sseUnitTests();
	~sseUnitTests();

	void Run();

protected:
	void RunEqualityTests();
	void RunDeterminantTests();
	void RunTransposeTests();
	void RunMultiplicationRegresssion();
	dMatrix GenerateRandomSquareMatrix(int size);

private:
	sseLog *m_log;
};