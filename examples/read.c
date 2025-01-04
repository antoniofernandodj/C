#include <stdio.h>
#include <ctype.h>

#define is_whitespace(c) (c == ' ' || c == '\t' || c == '\n' || c == '\r')

// Função que conta as palavras da entrada
int count_words(FILE *input) {
    int word_count = 0;
    char c;
    int in_word = 0;

    while ((c = fgetc(input)) != EOF) {
        if (is_whitespace(c)) {
            if (in_word) {
                word_count++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }
    
    if (in_word) {
        word_count++;
    }

    return word_count;
}

int main() {
    int word_count = count_words(stdin);  // Lê da entrada padrão
    printf("Número de palavras: %d\n", word_count);
    return 0;
}


// #include <stdio.h>
// #include <ctype.h>
// #define read_stdin(c) while ((c = getchar()) != EOF)

// int main() {
//     char c;
//     int inWord = 0;
//     int wordCount = 0;

//     read_stdin(c) {
//         if (isalnum(c)) {
//             if (!inWord) {
//                 inWord = 1;
//                 wordCount++;
//             }
//         } else {
//             inWord = 0;
//         }
//     }

//     // Exibe o número de palavras encontradas
//     printf("Número de palavras: %d\n", wordCount);

//     return 0;
// }
