#include "texture.h"


unsigned int make_texture(const std::string texture_path, 
		const std::string directory) {
	std::string filename = directory + '/' + texture_path;

	unsigned int texture_id;
	glGenTextures(1, &texture_id);

	stbi_set_flip_vertically_on_load(true);

    int texture_width, texture_height, texture_channels;
    unsigned char *pixels = stbi_load(filename.c_str(), &texture_width, 
			&texture_height, &texture_channels, 0);

    if (pixels) {
		GLenum format;
		if (texture_channels == 1) {
			format = GL_RED;
		} else if (texture_channels == 3) {
			format = GL_RGB;
		} else if (texture_channels == 4) {
			format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, format, texture_width, texture_height, 0, 
				format, GL_UNSIGNED_BYTE, pixels);
        glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
				GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    } else {
		std::cout << "ERROR:FAILED:LOADING: " << filename << std::endl;
    }

    stbi_image_free(pixels);

	return texture_id;
}
