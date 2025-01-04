#include <stdio.h>
#include <stdlib.h>

typedef struct {
    void (*execute)(void);
} Command;

void turn_on() {
    printf("Ligando o dispositivo\n");
}

void turn_off() {
    printf("Desligando o dispositivo\n");
}

int main() {
    Command onCommand = { turn_on };
    Command offCommand = { turn_off };

    onCommand.execute();
    offCommand.execute();

    return 0;
}
