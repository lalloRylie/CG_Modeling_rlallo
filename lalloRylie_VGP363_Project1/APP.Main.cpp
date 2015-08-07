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
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(true);
	glClearDepthf(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	_Mesh = new Mesh();
	_Mesh->AllocateVertices(36);
	//_Mesh->SetVertex(0, MeshVertex(-0.75f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	//_Mesh->SetVertex(1, MeshVertex(0.75f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	//_Mesh->SetVertex(2, MeshVertex(0.0f, 0.75f, 0.0f, 0.0f, 0.0f, -1.0f, 0.5f, 1.0f));

	//face1:
	_Mesh->SetVertex(0,  MeshVertex(-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	_Mesh->SetVertex(1,  MeshVertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(2,  MeshVertex( 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
	_Mesh->SetVertex(3,  MeshVertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(4,  MeshVertex( 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	_Mesh->SetVertex(5,  MeshVertex( 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

	//face2:
	_Mesh->SetVertex(6,  MeshVertex( 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	_Mesh->SetVertex(7,  MeshVertex( 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(8,  MeshVertex( 0.5f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
	_Mesh->SetVertex(9,  MeshVertex( 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(10, MeshVertex( 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	_Mesh->SetVertex(11, MeshVertex( 0.5f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

	//face3
	_Mesh->SetVertex(12, MeshVertex( 0.5f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	_Mesh->SetVertex(13, MeshVertex( 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(14, MeshVertex(-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
	_Mesh->SetVertex(15, MeshVertex( 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(16, MeshVertex(-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	_Mesh->SetVertex(17, MeshVertex(-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

	//face4
	_Mesh->SetVertex(18, MeshVertex(-0.5f,  0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	_Mesh->SetVertex(19, MeshVertex(-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(20, MeshVertex(-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
	_Mesh->SetVertex(21, MeshVertex(-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(22, MeshVertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	_Mesh->SetVertex(23, MeshVertex(-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

	//face5
	_Mesh->SetVertex(24, MeshVertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	_Mesh->SetVertex(25, MeshVertex(-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(26, MeshVertex( 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
	_Mesh->SetVertex(27, MeshVertex(-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(28, MeshVertex( 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	_Mesh->SetVertex(29, MeshVertex( 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

	//face6
	_Mesh->SetVertex(30, MeshVertex(-0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
	_Mesh->SetVertex(31, MeshVertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(32, MeshVertex( 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
	_Mesh->SetVertex(33, MeshVertex(-0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
	_Mesh->SetVertex(34, MeshVertex( 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
	_Mesh->SetVertex(35, MeshVertex( 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));

	//face1:
	//-0.5f,  0.5f, 0.0f,; 
	//-0.5f, -0.5f, 0.0f,; 
	// 0.5f,  0.5f, 0.0f,;
	//-0.5f, -0.5f, 0.0f,;  
	// 0.5f, -0.5f, 0.0f,; 
	// 0.5f,  0.5f, 0.0f,;
	//
	//face2:
	// 0.5f,  0.5f, 0.0f,; 
	// 0.5f, -0.5f, 0.0f,; 
	// 0.5f,  0.5f, 1.0f,;
	// 0.5f, -0.5f, 0.0f,;
	//-0.5f,  0.5f, 1.0f,;
	// 0.5f,  0.5f, 1.0f,;
	//
	//face3:
	// 0.5f,  0.5f, 1.0f,; 
	//-0.5f,  0.5f, 1.0f,; 
	//-0.5f,  0.5f, 1.0f,;
	//-0.5f,  0.5f, 1.0f,; 
	//-0.5f, -0.5f, 1.0f,; 
	//-0.5f,  0.5f, 1.0f,;
	//
	//face4:
	//-0.5f,  0.5f, 1.0f,; 
	//-0.5f, -0.5f, 1.0f,; 
	//-0.5f,  0.5f, 0.0f,;
	//-0.5f, -0.5f, 1.0f,; 
	//-0.5f, -0.5f, 0.0f,; 
	//-0.5f,  0.5f, 0.0f,;
	//
	//face5:
	//-0.5f, -0.5f, 0.0f,;
	//-0.5f, -0.5f, 1.0f,;
	// 0.5f, -0.5f, 0.0f,;
	//-0.5f, -0.5f, 1.0f,;
	//-0.5f,  0.5f, 1.0f,;
	// 0.5f, -0.5f, 0.0f,;
	//
	//face6:
	//-0.5f, 0.5f, 1.0f,; 
	//-0.5f, 0.5f, 0.0f,; 
	// 0.5f, 0.5f, 1.0f,;
	//-0.5f, 0.5f, 0.0f,; 
	// 0.5f, 0.5f, 0.0f,; 
	// 0.5f, 0.5f, 1.0f,;
	//
	//vertex - x,y,z
	//
	//0 : -0.5,  0.5, 0.0;
	//1 : -0.5, -0.5, 0.0;
	//2 :  0.5, -0.5, 0.0;
	//3 :  0.5,  0.5, 0.0;
	//4 : -0.5,  0.5, 1.0;
	//5 : -0.5, -0.5, 1.0;
	//6 : -0.5,  0.5, 1.0;
	//7 :  0.5,  0.5, 1.0;


	_Mesh->material = GetDefaultMaterial();
	
	_Mesh->texture = CORE::Texture::LoadPNG("./Resources/REFERENCE_GRASS_PHOTO.png");

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