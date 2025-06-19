#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const int PNG_TEX = 1;
const int JPG_TEX = 2;

void make_texture(const char *texture_path, const int image_type) {
    int texWidth, texHeight, texChannels;
    stbi_set_flip_vertically_on_load(GL_TRUE);
    unsigned char *pixels = stbi_load(texture_path, &texWidth, &texHeight, &texChannels, 0);

    if (pixels) {
        if (image_type == PNG_TEX)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        else if (image_type == JPG_TEX)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
        else {
            fprintf(stderr, "Failed to create texture: Wrong texture type\n");
            stbi_image_free(pixels);
            return;
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        fprintf(stderr, "Failed to load texture %s\n", texture_path);
    }

    stbi_image_free(pixels);
}

#endif