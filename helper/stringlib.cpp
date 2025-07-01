#include "stringlib.h"
#include <iostream>

char *stradd(const char *s1, const char *s2) {
    char *s = (char *)malloc(sizeof(char) * (sizeof(s1) + sizeof(s2)));
    if (!s) {
        std::cout << "Failed to allocate new memory\n";
        return nullptr;
    }

    strcpy(s, s1);
    strcat(s, s2);

    return s;
}