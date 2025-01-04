#include <stdio.h>

typedef struct {
    void (*handle)(void);
} State;

void stateA() {
    printf("Estado A\n");
}

void stateB() {
    printf("Estado B\n");
}

typedef struct {
    State* current_state;
} Context;

void set_state(Context* context, State* state) {
    context->current_state = state;
}

void handle(Context* context) {
    context->current_state->handle();
}

int main() {
    State stateA_obj = { stateA };
    State stateB_obj = { stateB };
    Context context = { &stateA_obj };

    handle(&context);

    set_state(&context, &stateB_obj);
    handle(&context);

    return 0;
}
