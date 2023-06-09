#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
    void (*print)(struct Point*);
    struct Point* (*add)(struct Point*, struct Point*);
} Point;

void print(struct Point* p) {
    printf("P:(%d, %d)\n", p->x, p->y);
}

struct Point* add(struct Point* p1, struct Point* p2) {
    struct Point* result = (struct Point*)malloc(sizeof(struct Point));
    result->x = p1->x + p2->x;
    result->y = p1->y + p2->y;
    result->print = &print;
    result->add = &add;
    return result;
}

Point* newPoint(int x, int y) {
    Point* p = (Point*)malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    p->print = &print;
    p->add = &add;
    return p;
}

int main() {
    Point* p1 = newPoint(2, 3);
    Point* p2 = newPoint(5, 7);

    Point* p3 = p1->add(p1, p2);
    p3->print(p3);

    free(p1);
    free(p2);
    free(p3);

    return 0;
}
