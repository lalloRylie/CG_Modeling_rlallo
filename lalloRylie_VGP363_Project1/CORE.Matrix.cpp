//CORE.Matrix.cpp
///////////////////////////////////////////////////////

#include "main.h"
#include <math.h>

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

	Matrix Matrix::Translation(float x, float y, float z){
		return Matrix(1, 0, 0, x, 
					  0, 1, 0, y, 
					  0, 0, 1, z, 
					  0, 0, 0, 1);
	}

	Matrix Matrix::InverseTranslation(float x, float y, float z){
		return Matrix(1, 0, 0, -x, 
					  0, 1, 0, -y, 
					  0, 0, 1, -z, 
					  0, 0, 0, 1);
	}

	Matrix Matrix::Rotation(float x, float y, float z){
		return Matrix(cos(z)*cos(y), cos(z)*sin(y)*sin(x)-sin(z)*cos(x), cos(z)*sin(y)*cos(x)+sin(z)*sin(x), 0,
					  sin(z)*cos(y), sin(z)*sin(y)*sin(x)+cos(z)*cos(x), sin(z)*sin(y)*cos(x)-cos(z)*sin(x), 0,
					  -sin(y)      , cos(y)*sin(x)                     , cos(y)*cos(x)                     , 0,
					              0,                                  0,                                  0, 1);
	}	

	Matrix Matrix::InverseRotation(float x, float y, float z){
		return Matrix(cos(z)*cos(y)                     , sin(z)*cos(y)                     , -sin(y)      , 0,
					  cos(z)*sin(y)*sin(x)-sin(z)*cos(x), sin(z)*sin(y)*sin(x)+cos(z)*cos(x), cos(y)*sin(x), 0,
					  cos(z)*sin(y)*cos(x)+sin(z)*sin(x), sin(z)*sin(y)*cos(x)-cos(z)*sin(x), cos(y)*cos(x), 0,
					                                   0,                                  0,             0, 1);
	}

	Matrix Matrix::SpaceRotation(const vector& xaxis, const vector& yaxis, const vector& zaxis){
		return Matrix(xaxis.x, xaxis.y, xaxis.z, 0,
					  yaxis.x, yaxis.y, yaxis.z, 0,
					  zaxis.x, zaxis.y, zaxis.z, 0,
					        0,       0,       0, 1);
	}

	Matrix Matrix::InverseSpaceRotation(const vector& xaxis, const vector& yaxis, const vector& zaxis){
		return Matrix(xaxis.x, yaxis.x, zaxis.x, 0,
					  xaxis.y, yaxis.y, zaxis.y, 0,
					  xaxis.z, yaxis.z, zaxis.z, 0,
					        0,       0,       0, 1);
	}

	Matrix Matrix::RotationAroundVector(float theta, float Vx, float Vy, float Vz){
		return Matrix(cos(theta)+Vx*Vx*(1-cos(theta))    , -Vz*sin(theta)+Vx*Vy*(1-cos(theta)), Vy*sin(theta)+Vx*Vz*(1-cos(theta)) , 0,
				      Vz*sin(theta)+Vy*Vx*(1-cos(theta)) , cos(theta)+Vy*Vy*(1-cos(theta))    , -Vx*sin(theta)+Vy*Vz*(1-cos(theta)), 0,
				      -Vy*sin(theta)+Vz*Vx*(1-cos(theta)), Vx*sin(theta)+Vz*Vy*(1-cos(theta)) , cos(theta)+Vz*Vz*(1-cos(theta))    , 0,
				                                        0,                                   0,                                   0, 1);
	}

	Matrix Matrix::InverseRotationAroundVector(float theta, float Vx, float Vy, float Vz){
		return Matrix(cos(-theta)+Vx*Vx*(1-cos(-theta))    , -Vz*sin(-theta)+Vx*Vy*(1-cos(-theta)), Vy*sin(-theta)+Vx*Vz*(1-cos(-theta)) , 0,
				      Vz*sin(-theta)+Vy*Vx*(1-cos(-theta)) , cos(-theta)+Vy*Vy*(1-cos(-theta))    , -Vx*sin(-theta)+Vy*Vz*(1-cos(-theta)), 0,
				      -Vy*sin(-theta)+Vz*Vx*(1-cos(-theta)), Vx*sin(-theta)+Vz*Vy*(1-cos(-theta)) , cos(-theta)+Vz*Vz*(1-cos(-theta))    , 0,
				                                          0,                                     0,                                     0, 1);
	}

	Matrix Matrix::Perspective(float fov, float w, float h, float _near, float _far){
		return Matrix((1/tan((fov/(w/h))/2))/(w/h),                    0,                         0,                           0,
					                             0, 1/tan((fov/(w/h))/2),                         0,                           0,
					                             0,                    0, (_far+_near)/(_near-_far), (2*_far*_near)/(_near-_far),
					                             0,                    0,                        -1,                           0);
	}

	Matrix Matrix::InversePerspective(float fov, float w, float h, float _near, float _far){
		return Matrix((w/h)/(1/tan((fov/(w/h))/2)),                  0,                           0,                            0,
					                             0, tan((fov/(w/h))/2),                           0,                            0,
					                             0,                  0,                           0,                           -1,
					                             0,                  0, (_near-_far)/(2*_far*_near), (_far+_near)/(2*_far*_near));
	}

	Matrix Matrix::Orthographic(float L, float r, float b, float t, float n, float f){
		return Matrix(2/(r-L),       0,        0, (r+L)/(r-L),
					  	    0, 2/(t-b),        0, (t+b)/(t-b),
					  	    0,       0, -2/(f-n), (f+n)/(f-n),
					  	    0,       0,        0,          1);
	}

	Matrix Matrix::InverseOrthographic(float L, float r, float b, float t, float n, float f){
		return Matrix((r-L)/2.0,         0,          0, (r+L)/2.0,
					          0, (t-b)/2.0,          0, (t+b)/2.0,
					          0,         0, (f-n)/-2.0, (f+n)/2.0,
					          0,         0,          0,        1);
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