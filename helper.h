#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>

char *load_shader(const char *shader_path) {
    char *shader_code;

    FILE *shader_file = fopen(shader_path, "r");
    if (!shader_file) {
        fprintf(stderr, "ERROR:LOADING:SHADER:FAILED\n");
        return NULL;
    }

    // seek to end to determine file size
    fseek(shader_file, 0, SEEK_END);
    long file_size = ftell(shader_file);
    rewind(shader_file);

    // allocate buffer (+1 for null terminator)
    shader_code = (char *)malloc(file_size + 1);
    if (!shader_code) {
        fprintf(stderr, "ERROR:ALLOCATION:SHADER:BUFFER:FAILED\n");
        fclose(shader_file);
        return NULL;
    }

    // read file into buffer
    size_t read_size = fread(shader_code, 1, file_size, shader_file);
    shader_code[read_size] = '\0';

    fclose(shader_file);
    return shader_code;
}


#endif