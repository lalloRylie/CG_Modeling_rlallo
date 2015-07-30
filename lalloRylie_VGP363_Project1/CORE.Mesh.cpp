//CORE.Mesh.cpp
///////////////////////////////////////////////////////

#include "main.h"

namespace CORE {
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