//CORE.Matrix.h
///////////////////////////////////////////////////////

#pragma once

#ifndef _CORE_MATRIX_H_
#define _CORE_MATRIX_H_

namespace CORE {
	extern float _ModelMatrix[16];
	extern float _ViewMatrix[16];
	extern float _ProjectionMatrix[16];
	extern float _NormalMatrix[9];

	class Matrix {
	public:
		float m[16];
		Matrix();
		Matrix(
			float r0c0, float r0c1, float r0c2, float r0c3,
			float r1c0, float r1c1, float r1c2, float r1c3,
			float r2c0, float r2c1, float r2c2, float r2c3,
			float r3c0, float r3c1, float r3c2, float r3c3);
		static Matrix Identity();
		static Matrix Rotation(float g, float b, float a);
	};

	void GL_SetModelMatrix(const Matrix& matrix);
	void GL_SetViewMatrix(const Matrix& matrix);
	void GL_SetProjectionMatrix(const Matrix& matrix);
	void GL_SetNormalMatrix(const Matrix& matrix);
}

#endif