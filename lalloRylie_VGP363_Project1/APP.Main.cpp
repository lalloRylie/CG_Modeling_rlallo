//APP.Main.cpp
///////////////////////////////////////////////////////////

#include "APP.Main.h"

using namespace CORE;

Mesh* _Mesh = NULL;
float RotX = 0.0f;
float RotY = 0.0f;
float RotZ = 0.0f;

void OnInitialize(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(true);
	glClearDepthf(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_Mesh = new Mesh();
	_Mesh->AllocateVertices(3);
	_Mesh->SetVertex(0, MeshVertex(-0.75f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(1, MeshVertex(0.75f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	_Mesh->SetVertex(2, MeshVertex(0.0f, 0.75f, 0.0f, 0.0f, 0.0f, -1.0f, 0.5f, 1.0f));
	_Mesh->material = GetDefaultMaterial();
	_Mesh->Build();

	GL_SetModelMatrix(Matrix::Identity());
	GL_SetViewMatrix(Matrix::Identity());
	GL_SetProjectionMatrix(Matrix::Identity());
	GL_SetNormalMatrix(Matrix::Identity());

	glViewport(0, 0, 800, 600);
}

void OnFrame(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RotX += 0.1f * Time::DeltaTime;
	RotY += 0.2f * Time::DeltaTime;
	RotZ += 0.3f * Time::DeltaTime;

	GL_SetModelMatrix(Matrix::Rotation(RotX, RotY, RotZ));

	_Mesh->Render(NULL);

	Time::Update();
}