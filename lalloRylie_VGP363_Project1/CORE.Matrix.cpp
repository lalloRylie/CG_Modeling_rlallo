//CORE.Matrix.cpp
///////////////////////////////////////////////////////

#include "main.h"

namespace CORE {
	Matrix::Matrix(){
		memset(this->m, 0, sizeof(float)*16);
	}
	
	Matrix::Matrix(
			float r0c0, float r0c1, float r0c2, float r0c3,
			float r1c0, float r1c1, float r1c2, float r1c3,
			float r2c0, float r2c1, float r2c2, float r2c3,
			float r3c0, float r3c1, float r3c2, float r3c3)
	{
		this->m[0]  = r0c0;
		this->m[1]  = r0c1;
		this->m[2]  = r0c2;
		this->m[3]  = r0c3;
		this->m[4]  = r1c0;
		this->m[5]  = r1c1;
		this->m[6]  = r1c2;
		this->m[7]  = r1c3;
		this->m[8]  = r2c0;
		this->m[9]  = r2c1;
		this->m[10] = r2c2;
		this->m[11] = r2c3;
		this->m[12] = r3c0;
		this->m[13] = r3c1;
		this->m[14] = r3c2;
		this->m[15] = r3c3;
	}

	Matrix Matrix::Identity(){
		return Matrix(1, 0, 0, 0, 
					  0, 1, 0, 0, 
					  0, 0, 1, 0, 
					  0, 0, 0, 1);
	}

	void GL_SetModelMatrix(const Matrix& matrix){
		memcpy(_ModelMatrix, matrix.m, sizeof(float)*16);
	}

	void GL_SetViewMatrix(const Matrix& matrix){
		memcpy(_ViewMatrix, matrix.m, sizeof(float)*16);
	}

	void GL_SetProjectionMatrix(const Matrix& matrix){
		memcpy(_ProjectionMatrix, matrix.m, sizeof(float)*16);
	}

	void GL_SetNormalMatrix(const Matrix& matrix){
		memcpy(_NormalMatrix, matrix.m, sizeof(float)*9);
	}

	float _ModelMatrix[]      = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	float _ViewMatrix[]       = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	float _ProjectionMatrix[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	float _NormalMatrix[]     = {1, 0, 0, 0, 1, 0, 0, 0, 1};
}