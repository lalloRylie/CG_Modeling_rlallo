//CORE.Texture.cpp
/////////////////////////////////////////////////////////////////

#include "main.h"

namespace CORE {
	Texture::Texture() {
		this->image    = NULL;
		this->fileName = "";
		this->id       = -1;
		this->width    = NULL;
		this->height   = NULL;
		this->format   = NULL;
		this->data     = NULL;
		this->built    = false;
	}

	CORE::Texture* Texture::LoadPNG(char* fileName) {
		CORE::File::Data* fileData = File::LoadAsset(fileName);
		if(fileData == NULL) {
			return 0;
		}

		CORE::Image* imgData = CORE::IMAGE::PNG::Load(fileData);
		if(imgData == NULL) {
			return 0;
		}

		CORE::Texture* texture = new Texture();
		texture->fileName = fileName;
		texture->image = imgData;
		texture->data = imgData->data;
		texture->width = imgData->width;
		texture->height = imgData->height;
		texture->format = imgData->format;

		File::UnloadAsset(fileData);

		return texture;
	}

	void UnloadPNG(CORE::Texture* texture) {
		if(texture == NULL) return;

		CORE::IMAGE::PNG::Unload(&texture->image);

		delete texture;
	}
}