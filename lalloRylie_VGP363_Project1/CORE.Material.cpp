//CORE.Material.cpp
///////////////////////////////////////////////////////

#include "main.h"

#define MAX_TEXTURE_CHANNELS 10

namespace CORE {
	CORE::Texture* _textureChannel[MAX_TEXTURE_CHANNELS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	void GL_EnableTexture(int channel, CORE::Texture* texture, int options) {
		if(channel < 0) {
			channel = 0;
		}
		if(channel > (MAX_TEXTURE_CHANNELS - 1)) {
			channel = MAX_TEXTURE_CHANNELS - 1;
		}

		if(texture == 0) {
			return;
		}

		_textureChannel[channel] = texture;

		if(!texture->built){
			glGenTextures(1, (GLuint*) &texture->id);
			glBindTexture(GL_TEXTURE_2D, texture->id);
			glTexImage2D(GL_TEXTURE_2D, 0, texture->format, texture->width, texture->height, 0, texture->format, GL_UNSIGNED_BYTE, texture->data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glGenerateMipmap(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, 0);

			texture->built = true;
		}
	}

}

namespace CORE {
	const char* FRAGMENT_SHADER_DEFAULT = SHADER_SOURCE
	(
		precision mediump float;

		varying vec2 vTextureCoord;
		varying vec3 vLightWeighting;

		uniform sampler2D uSamplerColor;
		uniform float uAlpha;

		void main(void) {
			vec4 textureColor = texture2D(uSamplerColor, vec2(vTextureCoord.x, vTextureCoord.y));
			gl_FragColor = vec4(textureColor.rgb, textureColor.a);
		}
	);

	const char* VERTEX_SHADER_DEFAULT = SHADER_SOURCE
	(
		attribute vec3 aVertexPosition;
		attribute vec3 aVertexNormal;
		attribute vec2 aTextureCoord;

		uniform mat4 uModelMatrix;
		uniform mat4 uViewMatrix;
		uniform mat4 uProjectionMatrix;
		uniform mat3 uNormalMatrix;

		uniform vec3 uAmbientColor;

		uniform vec3 uLightingDirection;
		uniform vec3 uDirectionalColor;

		varying vec2 vTextureCoord;
		varying vec3 vLightWeighting;

		void main(void) {
			vec4 worldPos = uModelMatrix * vec4(aVertexPosition, 1.0);
			vec4 cameraPos = uViewMatrix * worldPos;
			vec4 screenPos = uProjectionMatrix * cameraPos;
			vTextureCoord = aTextureCoord;
			gl_Position = screenPos;

			vec3 transformedNormal = mat3(uViewMatrix * uModelMatrix) * aVertexNormal;
			float directionalLightWeighting = max(dot(transformedNormal, uLightingDirection), 0.0);
			vLightWeighting = uAmbientColor + uDirectionalColor * directionalLightWeighting;
		}
	);

	// GL_CreateMaterial : Creates a material given the vertex and fragment shader sources.
	MATERIAL_ID GL_CreateMaterial(const char* vs_src, const char* fs_src) {
		GLuint fragmentShader = GL_CreateFragmentShader(fs_src);
		GLuint vertexShader = GL_CreateVertexShader(vs_src);

		GLuint material = glCreateProgram();
		glAttachShader(material, vertexShader);
		glAttachShader(material, fragmentShader);
		glLinkProgram(material);

		GLint result;
		glGetProgramiv(material, GL_LINK_STATUS, &result);
		if (result == 0) {
			//Debug::Log("ERROR: Material creation failed.\n");
			return -1;
		}

			return material;
	}

	// GL_CreateVertexShader : Builds a vertex shader given the source and returns it.
	GLuint GL_CreateVertexShader(const char* src) {
		GLuint shader = glCreateShader(GL_VERTEX_SHADER);
		int length = strlen(src);
		const GLchar* item = (const GLchar*)src;
		glShaderSource(shader, 1, &item, &length);
		return GL_CompileShader(shader);
	}

	// GL_CreateVertexShader : Builds a fragment shader given the source and returns it.
	GLuint GL_CreateFragmentShader(const char* src) {
	GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
	int length = strlen(src);
	const GLchar* item = (const GLchar*)src;
	glShaderSource(shader, 1, &item, &length);
	return GL_CompileShader(shader);
	}

	// GL_CompileShader : Internal function used to compile vertex and fragment shaders.
	GLuint GL_CompileShader(GLuint shader) {
		glCompileShader(shader);

		GLint result;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (result == 0) {
			char infoLog[255];
			int length = 0;
			glGetShaderInfoLog(shader, 255, &length, infoLog);
			//Debug::Log("ERROR: Failed to compile shader:\n");
			//Debug::Log(infoLog);
			//Debug::Log("\n");
			return -1;
		}
		return shader;
	}

	void DefaultMaterial::Build(Mesh* mesh){
		if(mesh->built) return;
		mesh->built = true;

		if(mesh->vertexBuffer.data.floats != 0){
			glGenBuffers(1, &mesh->vertexBuffer.id);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer.id);
			glBufferData(GL_ARRAY_BUFFER, mesh->vertexBuffer.numItems * mesh->vertexBuffer.itemSize * sizeof(float), mesh->vertexBuffer.data.floats, GL_STATIC_DRAW);
		}

		if(mesh->normalBuffer.data.floats != 0){
			glGenBuffers(1, &mesh->normalBuffer.id);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->normalBuffer.id);
			glBufferData(GL_ARRAY_BUFFER, mesh->normalBuffer.numItems * mesh->normalBuffer.itemSize * sizeof(float), mesh->normalBuffer.data.floats, GL_STATIC_DRAW);
		}

		if(mesh->textureCoordBuffer.data.floats != 0){
			glGenBuffers(1, &mesh->textureCoordBuffer.id);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->textureCoordBuffer.id);
			glBufferData(GL_ARRAY_BUFFER, mesh->textureCoordBuffer.numItems * mesh->textureCoordBuffer.itemSize * sizeof(float), mesh->textureCoordBuffer.data.floats, GL_STATIC_DRAW);
		}

		if(mesh->indexBuffer.data.ushorts != 0){
			glGenBuffers(1, &mesh->indexBuffer.id);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->indexBuffer.id);
			glBufferData(GL_ARRAY_BUFFER, mesh->indexBuffer.numItems * mesh->indexBuffer.itemSize * sizeof(short), mesh->indexBuffer.data.ushorts, GL_STATIC_DRAW);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void DefaultMaterial::Unbuild(Mesh* mesh){
		if(mesh->vertexBuffer.data.floats != 0) delete mesh->vertexBuffer.data.floats;
		if(mesh->normalBuffer.data.floats != 0) delete mesh->normalBuffer.data.floats;
		if(mesh->textureCoordBuffer.data.floats != 0) delete mesh->textureCoordBuffer.data.floats;
		if(mesh->indexBuffer.data.ushorts != 0) delete mesh->indexBuffer.data.ushorts;
		
		if(mesh->vertexBuffer.id != 0) glDeleteBuffers(1, &mesh->vertexBuffer.id);
		if(mesh->normalBuffer.id != 0) glDeleteBuffers(1, &mesh->normalBuffer.id);
		if(mesh->textureCoordBuffer.id != 0) glDeleteBuffers(1, &mesh->textureCoordBuffer.id);
		if(mesh->indexBuffer.id != 0) glDeleteBuffers(1, &mesh->indexBuffer.id);

		mesh->built = false;
	}

	void DefaultMaterial::Activate(Mesh* mesh){
		glUseProgram(this->shader);

		vertexPositionAttribute  = glGetAttribLocation(this->shader, "aVertexPosition");
		vertexNormalAttribute    = glGetAttribLocation(this->shader, "aVertexNormal");
		textureCoordAttribute    = glGetAttribLocation(this->shader, "aTextureCoord");
		  
		projectionMatrixUniform  = glGetUniformLocation(this->shader, "uProjectionMatrix");
		modelMatrixUniform       = glGetUniformLocation(this->shader, "uModelMatrix");
		viewMatrixUniform        = glGetUniformLocation(this->shader, "uViewMatrix");
		normalMatrixUniform      = glGetUniformLocation(this->shader, "uNormalMatrix");
		alphaUniform             = glGetUniformLocation(this->shader, "uAlpha");
		samplerColorUniform      = glGetUniformLocation(this->shader, "uSamplerColor");
		lightingDirectionUniform = glGetUniformLocation(this->shader, "uLightingDirection");
		directionalColorUniform  = glGetUniformLocation(this->shader, "uDirectionalColor");

		glEnableVertexAttribArray(this->vertexPositionAttribute);
		glEnableVertexAttribArray(this->vertexNormalAttribute);
		glEnableVertexAttribArray(this->textureCoordAttribute);
	}

	void DefaultMaterial::Render(Camera* camera, Mesh* mesh){
		this->Activate(mesh);

		if(mesh != 0) {
			GL_EnableTexture(0, mesh->texture, 0);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->texture->id);
			glUniform1i(this->samplerColorUniform, 0);

		}

		glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer.id);
		glVertexAttribPointer(this->vertexPositionAttribute, mesh->vertexBuffer.itemSize, GL_FLOAT, false, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, mesh->normalBuffer.id);
		glVertexAttribPointer(this->vertexNormalAttribute, mesh->normalBuffer.itemSize, GL_FLOAT, false, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, mesh->textureCoordBuffer.id);
		glVertexAttribPointer(this->textureCoordAttribute, mesh->textureCoordBuffer.itemSize, GL_FLOAT, false, 0, 0);

		glUniform3f(ambientColorUniform, 0.15f, 0.15f, 0.15f);
		glUniform3f(lightingDirectionUniform, 0.0f, 0.0f, 1.0f);
		glUniform3f(directionalColorUniform, 0.88f, 0.88f, 0.88f);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer.id);

		glUniformMatrix4fv(projectionMatrixUniform, 1, false, _ProjectionMatrix);
		glUniformMatrix4fv(modelMatrixUniform, 1, false, _ModelMatrix);
		glUniformMatrix4fv(viewMatrixUniform, 1, false, _ViewMatrix);

		glDrawElements(GL_TRIANGLES, mesh->indexBuffer.numItems, GL_UNSIGNED_SHORT, 0);
	}

	DefaultMaterial* _defaultMaterial = 0;

	DefaultMaterial* GetDefaultMaterial(){
		if(_defaultMaterial == 0){
			_defaultMaterial = CreateDefaultMaterial();
		}

		return _defaultMaterial;
	}

	DefaultMaterial* CreateDefaultMaterial(){
		DefaultMaterial* defaultMaterial = new DefaultMaterial();
		defaultMaterial->shader = GL_CreateMaterial(VERTEX_SHADER_DEFAULT, FRAGMENT_SHADER_DEFAULT);

		return defaultMaterial;
	}

	void DeleteMaterial(Material* material){
	
	}
}