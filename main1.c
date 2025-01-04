#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
} Singleton;

Singleton* get_instance() {
    static Singleton* instance = NULL;
    if (instance == NULL) {
        instance = (Singleton*)malloc(sizeof(Singleton));
        instance->value = 0;  // Valor inicial
    }
    return instance;
}

int main(int argc, char *argv[]) {
    Singleton* s1 = get_instance();
    Singleton* s2 = get_instance();
    s1->value = 42;

    printf("s1->value: %d\n", s1->value);
    printf("s2->value: %d\n", s2->value);  // Deve ser 42
    return 0;
}