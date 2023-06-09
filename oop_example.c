#include <stdio.h>
#include <stdlib.h>

// Definição da estrutura da classe
typedef struct {
    int x;
    int y;
    void (*print)(void*);
} Point;

// Métodos da classe
void print(void* object) {
    Point* p = (Point*)object;
    printf("P:(%d, %d)\n", p->x, p->y);
}

// Função para criar um novo objeto Ponto
Point* newPoint(int x, int y) {
    Point* p = (Point*)malloc(sizeof(Point));
    p->x = x;
    p->y = y;
    p->print = &print;
    return p;
}

// Função principal
int main() {
    // Criação de objetos Ponto
    Point* p1 = newPoint(2, 3);
    Point* p2 = newPoint(5, 7);

    // Chamada do método imprimir para cada objeto
    p1->print(p1);
    p2->print(p2);

    // Liberação da memória alocada
    free(p1);
    free(p2);

    return 0;
}
