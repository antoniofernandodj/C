#include <stdio.h>
#include <stdlib.h>

typedef struct Component {
    void (*operation)(void);
    struct Component** children;
    int child_count;
} Component;

void leaf_operation() {
    printf("Operação em um Leaf\n");
}

void composite_operation() {
    printf("Operação em um Composite\n");
}

void add_child(Component* parent, Component* child) {
    parent->children = realloc(parent->children, sizeof(Component*) * (parent->child_count + 1));
    parent->children[parent->child_count++] = child;
}

void execute(Component* component) {
    component->operation();
    for (int i = 0; i < component->child_count; ++i) {
        execute(component->children[i]);
    }
}

int main() {
    Component leaf1 = { leaf_operation, NULL, 0 };
    Component leaf2 = { leaf_operation, NULL, 0 };
    Component composite = { composite_operation, NULL, 0 };

    add_child(&composite, &leaf1);
    add_child(&composite, &leaf2);

    execute(&composite);

    free(composite.children);
    return 0;
}
