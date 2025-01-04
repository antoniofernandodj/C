#include <stdio.h>

// Adapter

// Interface antiga
typedef struct {
    void (*old_function)(void);
} LegacySystem;

void legacy_function() {
    printf("Função antiga chamada\n");
}

// Interface nova
typedef struct {
    void (*new_function)(void);
} ModernSystem;

void adapter_function() {
    printf("Adaptando a interface...\n");
    legacy_function();
}

int main() {
    LegacySystem legacy = { legacy_function };
    ModernSystem modern = { adapter_function };

    modern.new_function();

    return 0;
}
