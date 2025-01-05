#include <stdio.h>
#include <stdlib.h>

#define BITMAP_SIZE 32  // Tamanho do bitmap (em bits)

typedef struct {
    unsigned int bits[1];  // Um array para armazenar os bits (usando 32 bits)
} Bitmap;

// Função para inicializar o bitmap
void bitmap_init(Bitmap *bmp) {
    bmp->bits[0] = 0;  // Inicializa todos os bits como 0
}

// Função para definir um bit (colocando-o em 1)
void bitmap_set(Bitmap *bmp, int index) {
    if (index >= 0 && index < BITMAP_SIZE) {
        bmp->bits[0] |= (1 << index);  // Usando operador OR para definir o bit
    }
}

// Função para limpar um bit (colocando-o em 0)
void bitmap_clear(Bitmap *bmp, int index) {
    if (index >= 0 && index < BITMAP_SIZE) {
        bmp->bits[0] &= ~(1 << index);  // Usando operador AND para limpar o bit
    }
}

// Função para verificar se um bit é 1
int bitmap_check(Bitmap *bmp, int index) {
    if (index >= 0 && index < BITMAP_SIZE) {
        return (bmp->bits[0] & (1 << index)) != 0;  // Verifica se o bit está em 1
    }
    return 0;  // Se o índice for inválido, retorna 0
}

// Função para alternar o valor de um bit
void bitmap_toggle(Bitmap *bmp, int index) {
    if (index >= 0 && index < BITMAP_SIZE) {
        bmp->bits[0] ^= (1 << index);  // Usando operador XOR para alternar o bit
    }
}

// Função para imprimir o bitmap (exibindo os bits)
void bitmap_print(Bitmap *bmp) {
    for (int i = BITMAP_SIZE - 1; i >= 0; i--) {
        printf("%d", bitmap_check(bmp, i));
        if (i % 8 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    Bitmap bmp;
    bitmap_init(&bmp);

    printf("Bitmap inicial: ");
    bitmap_print(&bmp);

    bitmap_set(&bmp, 0);  // Definir o bit 0
    bitmap_set(&bmp, 3);  // Definir o bit 3
    bitmap_set(&bmp, 5);  // Definir o bit 5

    printf("Bitmap após definições: ");
    bitmap_print(&bmp);

    bitmap_clear(&bmp, 3);  // Limpar o bit 3
    printf("Bitmap após limpar o bit 3: ");
    bitmap_print(&bmp);

    printf("Verificando o bit 5: %d\n", bitmap_check(&bmp, 5));
    printf("Verificando o bit 3: %d\n", bitmap_check(&bmp, 3));

    bitmap_toggle(&bmp, 5);  // Alternar o bit 5
    printf("Bitmap após alternar o bit 5: ");
    bitmap_print(&bmp);

    return 0;
}

