#include <stdio.h>

typedef struct {
    void (*execute)(void);
} Component;

void base_function() {
    printf("Função base\n");
}

void decorator_function() {
    printf("Função decorada: antes\n");
    base_function();
    printf("Função decorada: depois\n");
}

int main() {
    Component base = { base_function };
    Component decorated = { decorator_function };

    base.execute();
    decorated.execute();

    return 0;
}
