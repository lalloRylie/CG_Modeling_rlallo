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

	_Mesh->AllocateVertices(6);
	_Mesh->SetVertex(0, CORE::MeshVertex(-100.0f, -10.0f, -100.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(1, CORE::MeshVertex(-100.0f, -10.0f, 100.0f, 0.0f, 0.0f, -1.0f, 3.0f, 0.0f));
	_Mesh->SetVertex(2, CORE::MeshVertex(100.0f, -10.0f, 100.0f, 0.0f, 0.0f, -1.0f, 3.0f, 3.0f));

	_Mesh->SetVertex(3, CORE::MeshVertex(100.0f, -10.0f, 100.0f, 0.0f, 0.0f, -1.0f, 3.0f, 3.0f));
	_Mesh->SetVertex(4, CORE::MeshVertex(100.0f, -10.0f, -100.0f, 0.0f, 0.0f, -1.0f, 3.0f, 0.0f));
	_Mesh->SetVertex(5, CORE::MeshVertex(-100.0f, -10.0f, -100.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));

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

	if(DATACORE::_KEYBOARD_A) {
		_CameraYawY += DATACORE::player_lookSpeed * Time::DeltaTime;
	}
	if(DATACORE::_KEYBOARD_D) {
		_CameraYawY -= DATACORE::player_lookSpeed * Time::DeltaTime;
	}
	if(DATACORE::_KEYBOARD_W) {
		DATACORE::Vector forward = Matrix::ExtractZ(view);
		_CameraPositionX += DATACORE::player_runSpeed * forward.x * Time::DeltaTime;
		_CameraPositionY += DATACORE::player_runSpeed * forward.y * Time::DeltaTime;
		_CameraPositionZ += DATACORE::player_runSpeed * forward.z * Time::DeltaTime;
	}
	if(DATACORE::_KEYBOARD_W && DATACORE::_KEYBOARD_SHIFT) {
		//Sprint
		DATACORE::Vector forward = Matrix::ExtractZ(view);
		_CameraPositionX += DATACORE::player_runSpeed * 2.5f * forward.x * Time::DeltaTime;
		_CameraPositionY += DATACORE::player_runSpeed * 2.5f * forward.y * Time::DeltaTime;
		_CameraPositionZ += DATACORE::player_runSpeed * 2.5f * forward.z * Time::DeltaTime;
	}
	if(DATACORE::_KEYBOARD_S) {
		DATACORE::Vector forward = Matrix::ExtractZ(view);
		_CameraPositionX -= DATACORE::player_runSpeed * forward.x * Time::DeltaTime;
		_CameraPositionY -= DATACORE::player_runSpeed * forward.y * Time::DeltaTime;
		_CameraPositionZ -= DATACORE::player_runSpeed * forward.z * Time::DeltaTime;
	}
	if(DATACORE::_KEYBOARD_SPACE) {
		DATACORE::player_STATE = 1;
	}
	
 	if(DATACORE::player_STATE == 1) {
		//Jump
		DATACORE::player_jumpVelocity -= DATACORE::player_gravity * Time::DeltaTime;
		if(DATACORE::player_jumpVelocity < 0) {
			if(DATACORE::player_jumpVelocity < -20.0f) 
				DATACORE::player_jumpVelocity = -20.0f;
			if(_CameraPositionY > 0.0f) {
				_CameraPositionY = 0.0f;
				DATACORE::player_STATE = 0; 
				DATACORE::player_jumpVelocity = 16.0f;
			}
		}
		_CameraPositionY -= DATACORE::player_jumpVelocity * Time::DeltaTime;	
	}

	_Mesh->Render(NULL);

	Time::Update();
}