#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura StringADT
typedef struct {
    char *data;
    size_t length;
} StringADT;

// Inicializa uma StringADT vazia
StringADT *string_create() {
    StringADT *str = (StringADT *)malloc(sizeof(StringADT));
    str->data = NULL;
    str->length = 0;
    return str;
}

// Cria uma StringADT a partir de uma string C
StringADT *string_from(const char *cstr) {
    StringADT *str = string_create();
    str->length = strlen(cstr);
    str->data = (char *)malloc(str->length + 1);
    strcpy(str->data, cstr);
    return str;
}

// Libera a memória alocada para uma StringADT
void string_free(StringADT *str) {
    if (str) {
        free(str->data);
        free(str);
    }
}

// Concatena duas StringADT e retorna uma nova
StringADT *string_concat(const StringADT *s1, const StringADT *s2) {
    StringADT *result = string_create();
    result->length = s1->length + s2->length;
    result->data = (char *)malloc(result->length + 1);
    strcpy(result->data, s1->data);
    strcat(result->data, s2->data);
    return result;
}

// Adiciona um caractere ao final da StringADT
void string_append_char(StringADT *str, char c) {
    str->data = (char *)realloc(str->data, str->length + 2);
    str->data[str->length] = c;
    str->data[str->length + 1] = '\0';
    str->length++;
}

// Adiciona uma string C ao final da StringADT
void string_append_string(StringADT *str, const char *suffix) {
    size_t suffix_len = strlen(suffix);
    str->data = (char *)realloc(str->data, str->length + suffix_len + 1);
    strcpy(str->data + str->length, suffix);
    str->length += suffix_len;
}

// Retorna o tamanho da string
size_t string_length(const StringADT *str) {
    return str->length;
}

// Compara duas StringADT
int string_compare(const StringADT *s1, const StringADT *s2) {
    return strcmp(s1->data, s2->data);
}

// Copia uma StringADT
StringADT *string_copy(const StringADT *str) {
    return string_from(str->data);
}

// Exibe a string
void string_print(const StringADT *str) {
    if (str && str->data) {
        printf("%s\n", str->data);
    }
}

// Testando a StringADT
int main() {
    StringADT *s1 = string_from("Hello");
    StringADT *s2 = string_from(" World!");
    StringADT *s3 = string_concat(s1, s2);

    printf("s1: "); string_print(s1);
    printf("s2: "); string_print(s2);
    printf("Concatenated: "); string_print(s3);
    printf("Length: %zu\n", string_length(s3));

    string_free(s1);
    string_free(s2);
    string_free(s3);

    return 0;
}
