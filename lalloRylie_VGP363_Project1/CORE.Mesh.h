//CORE.Mesh.h
///////////////////////////////////////////////////////

#pragma once

#include "main.h"

#ifndef _CORE_MESH_H_
#define _CORE_MESH_H_

namespace CORE {
	class Camera;
	class Material;

	typedef union DATA_BUFFER{
		float* floats;
		unsigned short* ushorts;
		int* ints;
	};

	typedef struct GLBuffferObject{
		GLBuffferObject();
		GLuint id;
		int itemSize;
		int numItems;
		DATA_BUFFER data;
	
	};

	class MeshVertex{
	public:
		MeshVertex(float x, float y, float z, float nx, float ny, float nz, float tu, float tv);
		float x, y, z, w;
		float nx, ny, nz, nw;
		float tu, tv, gu, gv;
	};

	class Mesh{
	public:
		Mesh();

		Material* material;
		float alpha;
		bool built;

		GLBuffferObject vertexBuffer;
		GLBuffferObject normalBuffer;
		GLBuffferObject textureCoordBuffer;
		GLBuffferObject indexBuffer;

		void AllocateVertices(int count);
		void SetVertex(int index, const MeshVertex& vertex);
		void Build();
		void Render(Camera* camera);
	};

}

#endif