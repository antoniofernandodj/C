Aqui está um conjunto de regras inspirado na filosofia do Rust e do seu borrow checker para tornar a programação em C mais segura. Essas regras visam minimizar os riscos de bugs, evitar vazamentos de memória e melhorar a robustez do código:

1. Use const sempre que possível
Declare variáveis como const a menos que sejam explicitamente mutáveis.
Utilize ponteiros const para indicar que a função não modifica os dados apontados.
Exemplo:


void print_array(const int *arr, size_t size);
2. Inicialize todas as variáveis antes de usá-las
Nunca deixe variáveis não inicializadas. Sempre atribua um valor inicial, mesmo que seja um valor "vazio" padrão.
Exemplo:

c```
int x = 0;
char buffer[128] = {0};
```

3. Sempre limpe a memória ao sair do escopo
Libere explicitamente qualquer recurso alocado dinamicamente.
Utilize macros ou funções para facilitar a limpeza.
Exemplo:

c```
#define CLEANUP(ptr) do { free(ptr); ptr = NULL; } while (0)

char *data = malloc(100);
// ... uso de data ...
CLEANUP(data);
```

4. Prefira funções que retornem erros em vez de manipular diretamente estados globais
Evite usar variáveis globais. Caso seja necessário, use acessores para encapsular o acesso.
Exemplo:

c```
int get_value_safe(const int *array, size_t index, int *out_value);
```

5. Use escopos limitados e evite variáveis de longa duração
Declare variáveis no menor escopo possível.
Reduza o número de variáveis no mesmo bloco.
Exemplo:

c```
for (int i = 0; i < n; i++) {
    int temp = process(data[i]);
    printf("%d\n", temp);
}
```

6. Valide argumentos de funções explicitamente
Sempre verifique os parâmetros de entrada antes de usá-los.
Exemplo:

c```
if (ptr == NULL || size == 0) {
    return ERROR_INVALID_ARGUMENT;
}
```

7. Use estruturas para encapsular dados e métodos
Crie abstrações para manipular recursos como memória ou arquivos.
Exemplo:

c```
typedef struct {
    FILE *file;
} SafeFile;

SafeFile *open_safe(const char *filename, const char *mode);
void close_safe(SafeFile *safe_file);
```

8. Evite casting de ponteiros sem necessidade
Use void * com cautela. Sempre converta explicitamente e evite operações perigosas.
Exemplo:

c```
void *ptr = malloc(sizeof(int));
int *int_ptr = (int *)ptr;
```

9. Prefira arrays de tamanho fixo e evite ponteiros arbitrários
Sempre que possível, use arrays de tamanho fixo ou encapsule o gerenciamento de buffers em funções seguras.
Exemplo:

c```
void safe_copy(char *dest, size_t dest_size, const char *src) {
    strncpy(dest, src, dest_size - 1);
    dest[dest_size - 1] = '\0';
}
```

10. Use verificações de limite para evitar buffer overflow
Valide o tamanho antes de acessar arrays ou copiar dados.
Exemplo:

c```
if (index >= 0 && index < array_size) {
    array[index] = value;
}
```

11. Prefira macros seguras ou inline para operações críticas
Use macros e funções inline para encapsular operações repetitivas e reduzir erros.
Exemplo:

c```
#define ARRAY_LEN(arr) (sizeof(arr) / sizeof((arr)[0]))

inline int max(int a, int b) {
    return (a > b) ? a : b;
}
```

12. Evite manipular strings manualmente, prefira funções seguras
Use funções seguras como snprintf ou strncat em vez de sprintf ou strcpy.

13. Sempre documente o gerenciamento de memória
Especifique claramente quem é responsável por alocar e liberar memória em funções e estruturas.
Exemplo:

c```
// O chamador deve liberar a memória retornada por esta função
char *generate_message(const char *input);
```

14. Use ferramentas de análise estática
Integre ferramentas como gcc -fsanitize=address, clang static analyzer, ou valgrind para detectar erros em tempo de execução ou compilação.
15. Desative warnings e trate todos como erros
Configure o compilador para tratar todos os warnings como erros usando -Wall -Wextra -Werror.
16. Prefira enum e typedef para substituir constantes mágicas
Evite números mágicos no código.
Exemplo:

c```
typedef enum {
    STATUS_OK,
    STATUS_ERROR,
    STATUS_PENDING
} Status;
```

17. Use locks para acessar recursos compartilhados
Para aplicações multithread, proteja recursos compartilhados com mutexes ou outro mecanismo de sincronização.
Essas regras, quando aplicadas rigorosamente, ajudam a aproximar a segurança do C àquela promovida por linguagens modernas como Rust. Isso exige disciplina, ferramentas auxiliares e práticas de código limpo.
