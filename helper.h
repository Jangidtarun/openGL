#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>

char *load_shader(const char *shader_path) {
    char *shader_code;

    FILE *shader_file = fopen(shader_path, "r");
    if (!shader_file) {
        fprintf(stderr, "ERROR:LOADING:SHADER:FAILED\n");
        return NULL;
    }

    // read shader_file's content into shader_code

    fclose(shader_file);
    return shader_code;
}


#endif