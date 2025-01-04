#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type;
} Product;

Product* create_product(int type) {
    Product* product = (Product*)malloc(sizeof(Product));
    product->type = type;
    return product;
}

int main() {
    Product* p1 = create_product(1);
    Product* p2 = create_product(2);

    printf("p1->type: %d\n", p1->type);
    printf("p2->type: %d\n", p2->type);

    free(p1);
    free(p2);
    return 0;
}