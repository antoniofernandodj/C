#include <stdio.h>
#include <stdlib.h>

// Tabela de Descritores (Descriptor Table)

typedef struct {
    int id;
    const char* description;
} Descriptor;

#define MAX_DESCRIPTORS 10
Descriptor descriptors[MAX_DESCRIPTORS];
int descriptor_count = 0;

int create_descriptor(const char* description) {
    if (descriptor_count >= MAX_DESCRIPTORS) return -1;

    descriptors[descriptor_count].id = descriptor_count;
    descriptors[descriptor_count].description = description;
    return descriptor_count++;
}

const char* get_descriptor(int id) {
    for (int i = 0; i < descriptor_count; ++i) {
        if (descriptors[i].id == id) {
            return descriptors[i].description;
        }
    }
    return NULL;
}

int main() {
    int d1 = create_descriptor("Arquivo 1");
    int d2 = create_descriptor("Arquivo 2");

    printf("Descritor %d: %s\n", d1, get_descriptor(d1));
    printf("Descritor %d: %s\n", d2, get_descriptor(d2));

    return 0;
}
