//CORE.Material.h
///////////////////////////////////////////////////////

#pragma once

#include "DataCore.h"

#ifndef _CORE_MATERIAL_H_
#define _CORE_MATERIAL_H_


#define SHADER_SOURCE(...) #__VA_ARGS__

typedef GLuint MATERIAL_ID;
#define INVALID_MATERIAL_VALUE (-1)

typedef GLint MATERIAL_ATTRIBUTE;
#define INVALID_MATERIAL_ATTRIBUTE_VALUE (-1)

typedef GLuint TEXTURE;
#define INVALID_TEXTURE_VALUE (-1)

namespace CORE {
	class Mesh;
	class Camera;

	MATERIAL_ID GL_CreateMaterial(const char* vs_src, const char* fs_src);
	GLuint GL_CreateVertexShader(const char* src);
	GLuint GL_CreateFragmentShader(const char* src);
	GLuint GL_CompileShader(GLuint shader);

	class Material{
	public:
		MATERIAL_ID shader;
		virtual void Build(Mesh* mesh) = 0;
		virtual void Unbuild(Mesh* mesh) = 0;
		virtual void Activate(Mesh* mesh) = 0;
		virtual void Render(Camera* camera, Mesh* mesh) = 0;
	};

	class DefaultMaterial : public Material {
	public:
		MATERIAL_ATTRIBUTE vertexPositionAttribute;
		MATERIAL_ATTRIBUTE vertexNormalAttribute;
		MATERIAL_ATTRIBUTE textureCoordAttribute;
		MATERIAL_ATTRIBUTE projectionMatrixUniform;
		MATERIAL_ATTRIBUTE modelMatrixUniform;
		MATERIAL_ATTRIBUTE viewMatrixUniform;
		MATERIAL_ATTRIBUTE normalMatrixUniform;
		MATERIAL_ATTRIBUTE samplerColorUniform;
		MATERIAL_ATTRIBUTE ambientColorUniform;
		MATERIAL_ATTRIBUTE lightingDirectionUniform;
		MATERIAL_ATTRIBUTE directionalColorUniform;
		MATERIAL_ATTRIBUTE alphaUniform;

		void Build(Mesh* mesh);
		void Unbuild(Mesh* mesh);
		void Activate(Mesh* mesh);
		void Render(Camera* camera, Mesh* mesh);
	};

	DefaultMaterial* GetDefaultMaterial();
	DefaultMaterial* CreateDefaultMaterial();
}

#endif