#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

void print(Point* p) {
    printf("P:(%d, %d)\n", p->x, p->y);
}

typedef void (*PrintFunction)(Point*);

Point* newPoint(int x, int y) {
    Point* p = (Point*)malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    return p;
}

int main() {
    Point* p1 = newPoint(2, 3);
    Point* p2 = newPoint(5, 7);

    PrintFunction printFunc = &print;

    printFunc(p1);
    printFunc(p2);

    free(p1);
    free(p2);

    return 0;
}
