#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../src/stb_image.h"

unsigned int make_texture(const std::string texture_path, 
		const std::string directory);

#endif
