//CORE.Texture.h
/////////////////////////////////////////////////////////////////

#pragma once

#include "CORE.Material.h"
#include "System.File.h"
#include "System.Data.h"
#include "System.Image.h"

namespace CORE {
	class Texture {
	public:
		CORE::Image* image;
		char* fileName;
		int id, width, height, format;
		void* data;
		bool built;

		Texture();
		static CORE::Texture* LoadPNG(char* fileName);
		static void UnloadPNG(CORE::Texture* texture);
	};
}