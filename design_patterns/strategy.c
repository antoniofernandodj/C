#include <stdio.h>

typedef void (*StrategyFunc)(void);

void strategyA() {
    printf("Executando estratégia A\n");
}

void strategyB() {
    printf("Executando estratégia B\n");
}

typedef struct {
    StrategyFunc execute;
} Context;

int main() {
    Context context;

    context.execute = strategyA;
    context.execute();

    context.execute = strategyB;
    context.execute();

    return 0;
}
