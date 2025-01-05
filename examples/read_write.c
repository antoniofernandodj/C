#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

int main() {
    // Array de structs
    Point points[] = {
        { 1, 2 },
        { 3, 4 },
        { 5, 6 }
    };

    // Abertura do arquivo em modo de escrita binária
    FILE* f = fopen("example_array.bin", "wb");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Escrevendo o array de structs no arquivo
    size_t num_points = sizeof(points) / sizeof(points[0]);
    fwrite(points, sizeof(Point), num_points, f);

    // Fechando o arquivo
    fclose(f);

    // Abertura do arquivo em modo leitura binária
    f = fopen("example_array.bin", "rb");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Lendo o array de structs do arquivo
    Point read_points[3];  // Precisamos garantir que o array tenha o mesmo tamanho
    fread(read_points, sizeof(Point), num_points, f);

    // Fechando o arquivo
    fclose(f);

    // Exibindo os dados lidos
    for (size_t i = 0; i < num_points; i++) {
        printf("Point %zu: x = %d, y = %d\n", i, read_points[i].x, read_points[i].y);
    }

    return 0;
}

