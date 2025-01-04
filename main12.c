#include <stdio.h>
#include <stdlib.h>

// RAII (Resource Acquisition Is Initialization)

typedef struct {
    FILE* file;
} ManagedFile;

ManagedFile open_file(const char* filename, const char* mode) {
    ManagedFile mf;
    mf.file = fopen(filename, mode);
    if (mf.file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }
    return mf;
}

void close_file(ManagedFile* mf) {
    if (mf->file) {
        fclose(mf->file);
        mf->file = NULL;
    }
}

int main() {
    ManagedFile mf = open_file("exemplo.txt", "w");
    fprintf(mf.file, "Hello, RAII!\n");
    close_file(&mf);
    return 0;
}
