#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int x;
    int y;
} Point;

int main() {
    // Abertura do arquivo em modo leitura binária
    FILE* f = fopen("example_array.bin", "rb");
    if (f == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Determinando o tamanho do arquivo
    fseek(f, 0, SEEK_END);  // Vai até o final do arquivo
    long file_size = ftell(f);  // Pega a posição do ponteiro (tamanho do arquivo)
    fseek(f, 0, SEEK_SET);  // Volta para o começo do arquivo

    // Calculando o número de structs no arquivo
    size_t num_points = file_size / sizeof(Point);

    // Lendo o array de structs do arquivo
    Point* read_points;
    read_points = (Point*) malloc(file_size);  // Alocando memória dinamicamente

    fread(read_points, sizeof(Point), num_points, f);
    
    // Fechando o arquivo
    fclose(f);

    // Exibindo os dados lidos
    for (size_t i = 0; i < num_points; i++) {
        printf("Point %zu: x = %d, y = %d\n", i, read_points[i].x, read_points[i].y);
    }

    free(read_points);  // Liberando a memória alocada

    return 0;
}

