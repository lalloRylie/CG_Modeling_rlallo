//APP.Main.cpp
///////////////////////////////////////////////////////////

#include "APP.Main.h"

using namespace CORE;

Mesh* _Mesh = NULL;
float RotX = 0.0f;
float RotY = 0.0f;
float RotZ = 0.0f;

float _CameraPitchX = 0.0f, _CameraYawY = 0.0f, _CameraRollZ = 0.0f;
float _CameraPositionX = 0.0f, _CameraPositionY = 0.0f, _CameraPositionZ = 0.0f;

void OnInitialize(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(true);
	glClearDepthf(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//_Mesh = Mesh::CreateCube(0.25f);

	_Mesh = new Mesh();

	_Mesh->AllocateVertices(3);
	_Mesh->SetVertex(0, CORE::MeshVertex(-100.75f, -10.0f, -100.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(1, CORE::MeshVertex(0.0f, 0.75f, 100.0f, 0.0f, 0.0f, -1.0f, 0.5f, 1.0f));
	_Mesh->SetVertex(2, CORE::MeshVertex(100.75f, -10.0f, -100.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));

	_Mesh->material = GetDefaultMaterial();	
	_Mesh->texture = CORE::Texture::LoadPNG("./Resources/REFERENCE_GRASS_PHOTO.png");
	_Mesh->Build();

	GL_SetModelMatrix(Matrix::Identity());
	GL_SetViewMatrix(Matrix::Identity());
	GL_SetProjectionMatrix(Matrix::Perspective(60.0f, DATACORE::wndWidth, DATACORE::wndHeight, 0.1f, 1000.0f));
	GL_SetNormalMatrix(Matrix::Identity());
	

	glViewport(0, 0, DATACORE::wndWidth, DATACORE::wndHeight);
}

void OnFrame(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*RotX += 0.1f * Time::DeltaTime;
	RotY += 0.2f * Time::DeltaTime;
	RotZ += 0.3f * Time::DeltaTime;

	GL_SetModelMatrix(Matrix::Rotation(RotX, RotY, RotZ));*/

	CORE::Matrix cameraTranslate = CORE::Matrix::Translate(_CameraPositionX, _CameraPositionY, _CameraPositionZ);
	CORE::Matrix cameraRotate = CORE::Matrix::Rotation(_CameraPitchX, _CameraYawY, _CameraRollZ);
	CORE::Matrix view = CORE::Matrix::Multiply(cameraTranslate, cameraRotate);
	GL_SetViewMatrix(view);

	if(DATACORE::_KEYBOARD_LEFT) {
		_CameraYawY += 0.01;
	}
	if(DATACORE::_KEYBOARD_RIGHT) {
		_CameraYawY -= 0.01;
	}
	if(DATACORE::_KEYBOARD_UP) {
		DATACORE::Vector forward = Matrix::ExtractZ(view);
		_CameraPositionX += 0.1*forward.x;
		_CameraPositionY += 0.1*forward.y;
		_CameraPositionZ += 0.1*forward.z;
	}

	_Mesh->Render(NULL);

	Time::Update();
}