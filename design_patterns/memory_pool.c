#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POOL_SIZE 1024

// Pool de Memória (Memory Pool)

typedef struct {
    char pool[POOL_SIZE];
    size_t offset;
} MemoryPool;

void* pool_alloc(MemoryPool* mp, size_t size) {
    if (mp->offset + size > POOL_SIZE) {
        return NULL;  // Sem memória
    }
    void* ptr = mp->pool + mp->offset;
    mp->offset += size;
    return ptr;
}

void pool_reset(MemoryPool* mp) {
    mp->offset = 0;
}

int main() {
    MemoryPool mp = { .offset = 0 };

    char* str = (char*)pool_alloc(&mp, 100);
    strcpy(str, "Usando um pool de memória!");
    printf("%s\n", str);

    pool_reset(&mp);  // Pool resetado
    return 0;
}
