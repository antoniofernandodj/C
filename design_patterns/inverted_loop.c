#include <stdio.h>

// Loop Inverso (Inverted Loop)

void process_items(int* items, size_t count) {
    for (size_t i = count; i > 0; --i) {
        printf("Processando item: %d\n", items[i - 1]);
    }
}

int main() {
    int items[] = {1, 2, 3, 4, 5};
    process_items(items, 5);
    return 0;
}
