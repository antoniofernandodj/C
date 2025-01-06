#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r;
    int g;
    int b;
} Pixel;

// Função para inicializar a imagem
void initialize_image(Pixel **image, size_t width, size_t height) {
    for (size_t x = 0; x < width; x++) {
        for (size_t y = 0; y < height; y++) {
            image[x][y] = (Pixel){ .r = (int)x % 256, .g = (int)y % 256, .b = 100 };
        }
    }
}

// Função para liberar a memória alocada dinamicamente
void free_image(Pixel **image, size_t width) {
    for (size_t x = 0; x < width; x++) {
        free(image[x]);
    }
    free(image);
}

// Função para salvar a imagem em um arquivo PPM
void save_image_to_ppm(const char *filename, Pixel **image, size_t width, size_t height) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Erro ao abrir o arquivo para escrita: %s\n", filename);
        return;
    }

    // Escrever o cabeçalho do arquivo PPM
    fprintf(file, "P3\n%zu %zu\n255\n", width, height);

    // Escrever os pixels
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            Pixel pixel = image[x][y];
            fprintf(file, "%d %d %d ", pixel.r, pixel.g, pixel.b);
        }
        fprintf(file, "\n"); // Nova linha após cada linha de pixels
    }

    fclose(file);
    printf("Imagem salva no arquivo: %s\n", filename);
}

int main() {
    const size_t WIDTH = 800;
    const size_t HEIGHT = 600;

    // Alocar memória para a matriz de pixels
    Pixel **image = malloc(WIDTH * sizeof(Pixel *));
    if (image == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a imagem.\n");
        return 1;
    }

    for (size_t x = 0; x < WIDTH; x++) {
        image[x] = malloc(HEIGHT * sizeof(Pixel));
        if (image[x] == NULL) {
            fprintf(stderr, "Erro ao alocar memória para a linha %zu.\n", x);
            free_image(image, x); // Liberar as linhas alocadas até agora
            return 1;
        }
    }

    // Inicializar a imagem
    initialize_image(image, WIDTH, HEIGHT);

    // Salvar a imagem no arquivo
    save_image_to_ppm("imagem.ppm", image, WIDTH, HEIGHT);

    // Liberar a memória alocada
    free_image(image, WIDTH);

    return 0;
}

