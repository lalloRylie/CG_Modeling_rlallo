//CORE.Matrix.h
///////////////////////////////////////////////////////

#pragma once

#ifndef _CORE_MATRIX_H_
#define _CORE_MATRIX_H_

#include "DataCore.h"

namespace CORE {
	extern float _ModelMatrix[16];
	extern float _ViewMatrix[16];
	extern float _ProjectionMatrix[16];
	extern float _NormalMatrix[9];

	struct vector{
		float x, y, z, w;
	};

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
		static Matrix Translate(float x, float y, float z);
		static Matrix InverseTranslate(float x, float y, float z);
		static Matrix Rotation(float g, float b, float a);
		static Matrix InverseRotation(float g, float b, float a);
		static Matrix SpaceRotation(const vector& xaxis, const vector& yaxis, const vector& zaxis);
		static Matrix InverseSpaceRotation(const vector& xaxis, const vector& yaxis, const vector& zaxis);
		static Matrix RotationAroundVector(float theta, float Vx, float Vy, float Vz);
		static Matrix InverseRotationAroundVector(float theta, float Vx, float Vy, float Vz);
		static Matrix Perspective(float fov, float w, float h, float _near, float _far);
		static Matrix InversePerspective(float fov, float w, float h, float _near, float _far);
		static Matrix Orthographic(float l, float r, float b, float t, float n, float f);
		static Matrix InverseOrthographic(float l, float r, float b, float t, float n, float f);
		static Matrix Matrix::Multiply(const Matrix& m, const Matrix& n);
		static DATACORE::Vector Matrix::ExtractZ(const Matrix& m);
	};

	void GL_SetModelMatrix(const Matrix& matrix);
	void GL_SetViewMatrix(const Matrix& matrix);
	void GL_SetProjectionMatrix(const Matrix& matrix);
	void GL_SetNormalMatrix(const Matrix& matrix);
}

#endif