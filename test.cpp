#include <cstdlib>
#include <cstring>
#include <iostream>

char* getRealPath(const char* path) {
    char resolvedPath[5000];
    if (realpath(path, resolvedPath) == NULL) {
        // Handle error, such as invalid path
        return NULL;
    }
    return strdup(resolvedPath); // Remember to free this memory after use
}

int main() {
    const char* path = "/www/myProject/../myProject/../";
    char* realPath = getRealPath(path);
    if (realPath != NULL) {
        std::cout << "Real path: " << realPath << std::endl;
        free(realPath); // Free the memory allocated by strdup
    } else {
        std::cerr << "Failed to get the real path." << std::endl;
    }
    return 0;
}

