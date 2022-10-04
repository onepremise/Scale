//========================================================
//              Scaled Simulator Engine
//
// Author:       Jason Huntley
//
// Description:  Unit Tests
//
// Notes:
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
#include "sseUnitTests.hpp"
#include <time.h>

sseUnitTests::sseUnitTests()
{
	m_log=sseLog::Instance();
}

sseUnitTests::~sseUnitTests()
{

}

dMatrix sseUnitTests::GenerateRandomSquareMatrix(int size)
{
	dMatrix testMatrix(size,size);

	srand(time(NULL));

	for (int i=0; i<size; i++)
	{
		for (int j=0; j<size; j++)
		{
			int randomValue=rand()%100;
			testMatrix[i][j]=randomValue;
		}
	}

	//Keep going until not singular
	if (testMatrix.isSingular())
		testMatrix=GenerateRandomSquareMatrix(size);

	return testMatrix;
}

void sseUnitTests::Run()
{
	m_log->Info("Running Unit Tests...");

	//RunEqualityTests();

	//RunDeterminantTests();

	//RunTransposeTests();

	RunMultiplicationRegresssion();

	m_log->Info("Unit Tests Completed Successfully.");
}

void sseUnitTests::RunEqualityTests()
{
	m_log->Info("Running Equality Tests...");

	dMatrix testMatrix=GenerateRandomSquareMatrix(4);

	m_log->Info(testMatrix.toString("A"));

	::glLoadMatrixd(testMatrix.GetOGLMatrix());

	glPushMatrix();

	dMatrix copy;

	GLdouble modelMatrix[16]={0};

	glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);

	copy.Copy(modelMatrix);

	m_log->Info(copy.toString("B"));

	glPopMatrix();

	sseErrorHandler::_ThrowIfUnitTestFail(!(testMatrix==copy), "Matrix Copy and Equality Check");

	copy[0][0]=8;

	sseErrorHandler::_ThrowIfUnitTestFail((testMatrix==copy), "Inequality Check");
}

void sseUnitTests::RunDeterminantTests()
{
	m_log->Info("Running Determinant Test...");

	dMatrix testMatrix(4,4);

	testMatrix[0][0]=1;
	testMatrix[0][1]=4;
	testMatrix[0][2]=0;
	testMatrix[0][3]=3;

	testMatrix[1][0]=-1;
	testMatrix[1][1]=2;
	testMatrix[1][2]=0;
	testMatrix[1][3]=1;

	testMatrix[2][0]=0;
	testMatrix[2][1]=5;
	testMatrix[2][2]=4;
	testMatrix[2][3]=2;

	testMatrix[3][0]=1;
	testMatrix[3][1]=0;
	testMatrix[3][2]=0;
	testMatrix[3][3]=-2;

	m_log->Info(testMatrix.toString("Determinant Test"));

	m_log->Info("Determinant=%0.7f", testMatrix.Determinant());

	sseErrorHandler::_ThrowIfUnitTestFail(!(testMatrix.Determinant()==-56), "Determinant Check");
}

void sseUnitTests::RunTransposeTests()
{
	m_log->Info("Running Transpose, Inverse, Determinant Tests...");

	for (int matrixSize=2; matrixSize<=8; matrixSize++) {
		m_log->Info("Using matrix size=%i.", matrixSize);

		double *arrayMatrix=new double[matrixSize*matrixSize];
		dMatrix testMatrix=GenerateRandomSquareMatrix(matrixSize);

		int c=0;
		for (int i=0; i<matrixSize; i++)
		{
			for (int j=0; j<matrixSize; j++)
			{
				arrayMatrix[c]=testMatrix[i][j];
				c++;
			}
		}

		m_log->Info(testMatrix.toString("Original"));
		m_log->Info(testMatrix.Transpose().toString("Transpose"));
		m_log->Info(testMatrix.Transpose().Transpose().toString("Transpose Twice"));

		dMatrix copy(matrixSize,matrixSize);

		copy.Copy(matrixSize, arrayMatrix);

		m_log->Info(copy.toString("Copy of Original"));

		//(A^T)^T=A
		sseErrorHandler::_ThrowIfUnitTestFail(!(testMatrix.Transpose().Transpose()==testMatrix), "Transpose Check");

		m_log->Info("Transpose Determinant=%0.7f", testMatrix.Transpose().Determinant());
		m_log->Info("Determinant=%0.7f", testMatrix.Determinant());

		//det(A^T)=det(A)
		sseErrorHandler::_ThrowIfUnitTestFail(!(testMatrix.Transpose().Determinant()==testMatrix.Determinant()), "Determinant Check");

		//(A^T)^-1=(A^-1)^T
		if (matrixSize>2) {
			m_log->Info(testMatrix.Adjoint().toString("Adjoint"));
			m_log->Info(testMatrix.Inverse().toString("Inverse"));
			m_log->Info(testMatrix.Transpose().Inverse().toString("Transpose Inverse"));
			m_log->Info(testMatrix.Inverse().Transpose().toString("Inverse Transpose"));
			sseErrorHandler::_ThrowIfUnitTestFail(!(testMatrix.Transpose().Inverse()==testMatrix.Inverse().Transpose()), "Inverse Check");
		}

		delete [] arrayMatrix;
	}
}

void sseUnitTests::RunMultiplicationRegresssion()
{
	dMatrix testMatrixA(4,4);

	testMatrixA[0][0]=0.999684;
	testMatrixA[0][1]=-0.0177723;
	testMatrixA[0][2]=-0.0177779;
	testMatrixA[0][3]=0;

	testMatrixA[1][0]=1.73472e-018;
	testMatrixA[1][1]=0.707219;
	testMatrixA[1][2]=-0.706995;
	testMatrixA[1][3]=0;

	testMatrixA[2][0]=0.0251378;
	testMatrixA[2][1]=0.706772;
	testMatrixA[2][2]=0.706995;
	testMatrixA[2][3]=0;

	testMatrixA[3][0]=-127.56;
	testMatrixA[3][1]=-8;
	testMatrixA[3][2]=-5;
	testMatrixA[3][3]=1;

	dMatrix testMatrixB(4,4);

	testMatrixB[0][0]=1;
	testMatrixB[0][1]=0;
	testMatrixB[0][2]=0;
	testMatrixB[0][3]=0;

	testMatrixB[1][0]=0;
	testMatrixB[1][1]=1;
	testMatrixB[1][2]=0;
	testMatrixB[1][3]=0;

	testMatrixB[2][0]=0;
	testMatrixB[2][1]=0;
	testMatrixB[2][2]=1;
	testMatrixB[2][3]=0;

	testMatrixB[3][0]=149600;
	testMatrixB[3][1]=0;
	testMatrixB[3][2]=0;
	testMatrixB[3][3]=1;

	dMatrix testResult=testMatrixA;
	testResult*=testMatrixB;

	m_log->Info(testResult.toString("Multiplied"));

	dMatrix right(4,4);

	right[0][0]=0.999684;
	right[0][1]=-0.0177723;
	right[0][2]=-0.0177779;
	right[0][3]=0;

	right[1][0]=1.73472e-018;
	right[1][1]=0.707219;
	right[1][2]=-0.706995;
	right[1][3]=0;

	right[2][0]=0.0251378;
	right[2][1]=0.706772;
	right[2][2]=0.706995;
	right[2][3]=0;

	right[3][0]=149472.44000000000;
	right[3][1]=-8;
	right[3][2]=-5;
	right[3][3]=1;

	sseErrorHandler::_ThrowIfUnitTestFail(!(testResult==right), "Multiplication Check");
}