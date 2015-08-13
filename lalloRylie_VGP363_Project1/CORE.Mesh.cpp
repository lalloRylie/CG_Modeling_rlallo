//CORE.Mesh.cpp
///////////////////////////////////////////////////////

#include "main.h"

namespace CORE {

	Mesh* _cube = NULL;

	Mesh::Mesh(){
		memset(this, 0, sizeof(Mesh));
		this->alpha = 1.0f;
	}

	void Mesh::AllocateVertices(int count){
		this->vertexBuffer.itemSize = 3;
		this->vertexBuffer.numItems = count;
		this->vertexBuffer.data.floats = new float[count * this->vertexBuffer.itemSize];

		this->normalBuffer.itemSize = 3;
		this->normalBuffer.numItems = count;
		this->normalBuffer.data.floats = new float[count * this->normalBuffer.itemSize];
		
		this->textureCoordBuffer.itemSize = 2;
		this->textureCoordBuffer.numItems = count;
		this->textureCoordBuffer.data.floats = new float[count * this->textureCoordBuffer.itemSize];

		this->indexBuffer.itemSize = 1;
		this->indexBuffer.numItems = count;
		this->indexBuffer.data.ushorts = new unsigned short[count];

		for(int n = 0; n < count; n++){
			this->indexBuffer.data.ushorts[n] = n;
		}

	}

	void Mesh::SetVertex(int index, const MeshVertex& vertex){
		this->vertexBuffer.data.floats[index * 3 + 0] = vertex.x;
		this->vertexBuffer.data.floats[index * 3 + 1] = vertex.y;
		this->vertexBuffer.data.floats[index * 3 + 2] = vertex.z;

		this->normalBuffer.data.floats[index * 3 + 0] = vertex.nx;
		this->normalBuffer.data.floats[index * 3 + 1] = vertex.ny;
		this->normalBuffer.data.floats[index * 3 + 2] = vertex.nz;

		this->textureCoordBuffer.data.floats[index * 2 + 0] = vertex.tu;
		this->textureCoordBuffer.data.floats[index * 2 + 1] = vertex.tv;
	}

	void Mesh::Build(){
		if(this->material != 0){
			this->material->Build(this);
		} else {
			DebugLog("Mesh cannot be built until its material is assigned. \n");
		}
	}

	void Mesh::Render(Camera* camera){
		if(this->material != 0){
			this->material->Render(camera, this);
		}
	}

	Mesh* Mesh::CreateCube(float scale) {
		Mesh* Cube = new Mesh();
		Cube->AllocateVertices(36);
		//face1:
		Cube->SetVertex(0,  MeshVertex(-1.0f * scale,  1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
		Cube->SetVertex(1,  MeshVertex(-1.0f * scale, -1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
		Cube->SetVertex(2,  MeshVertex( 1.0f * scale,  1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
		Cube->SetVertex(3,  MeshVertex(-1.0f * scale, -1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
		Cube->SetVertex(4,  MeshVertex( 1.0f * scale, -1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
		Cube->SetVertex(5,  MeshVertex( 1.0f * scale,  1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));									  
		//face2:						  											
		Cube->SetVertex(6,  MeshVertex( 1.0f * scale,  1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
		Cube->SetVertex(7,  MeshVertex( 1.0f * scale, -1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
		Cube->SetVertex(8,  MeshVertex( 1.0f * scale,  1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
		Cube->SetVertex(9,  MeshVertex( 1.0f * scale, -1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
		Cube->SetVertex(10, MeshVertex( 1.0f * scale, -1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
		Cube->SetVertex(11, MeshVertex( 1.0f * scale,  1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));									  
		//face3							  											
		Cube->SetVertex(12, MeshVertex( 1.0f * scale,  1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
		Cube->SetVertex(13, MeshVertex( 1.0f * scale, -1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
		Cube->SetVertex(14, MeshVertex(-1.0f * scale,  1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
		Cube->SetVertex(15, MeshVertex( 1.0f * scale, -1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
		Cube->SetVertex(16, MeshVertex(-1.0f * scale, -1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
		Cube->SetVertex(17, MeshVertex(-1.0f * scale,  1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));								 
		//face4							 											 
		Cube->SetVertex(18, MeshVertex(-1.0f * scale,  1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
		Cube->SetVertex(19, MeshVertex(-1.0f * scale, -1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
		Cube->SetVertex(20, MeshVertex(-1.0f * scale,  1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
		Cube->SetVertex(21, MeshVertex(-1.0f * scale, -1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
		Cube->SetVertex(22, MeshVertex(-1.0f * scale, -1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
		Cube->SetVertex(23, MeshVertex(-1.0f * scale,  1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));							  
		//face5							  											
		Cube->SetVertex(24, MeshVertex(-1.0f * scale, -1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
		Cube->SetVertex(25, MeshVertex(-1.0f * scale, -1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
		Cube->SetVertex(26, MeshVertex( 1.0f * scale, -1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
		Cube->SetVertex(27, MeshVertex(-1.0f * scale, -1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
		Cube->SetVertex(28, MeshVertex( 1.0f * scale, -1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
		Cube->SetVertex(29, MeshVertex( 1.0f * scale, -1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));										  								
		//face6							  											 
		Cube->SetVertex(30, MeshVertex(-1.0f * scale,  1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
		Cube->SetVertex(31, MeshVertex(-1.0f * scale,  1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
		Cube->SetVertex(32, MeshVertex( 1.0f * scale,  1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
		Cube->SetVertex(33, MeshVertex(-1.0f * scale,  1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
		Cube->SetVertex(34, MeshVertex( 1.0f * scale,  1.0f * scale, 0.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
		Cube->SetVertex(35, MeshVertex( 1.0f * scale,  1.0f * scale, 1.0f * (scale * 2.0), 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
		
		_cube = Cube;
		return _cube;
	}

	MeshVertex::MeshVertex(float x, float y, float z, float nx, float ny, float nz, float tu, float tv){
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = 1.0f;
			this->nx = nx;
			this->ny = ny;
			this->nz = nz;
			this->nw = 0.0f;
			this->tu = tu;
			this->tv = tv;
			this->gu = 0.0f;
			this->gv = 0.0f;
		}
}