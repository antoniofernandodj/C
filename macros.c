#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <setjmp.h>

jmp_buf env;

#define to_string(x) #x
#define try if (setjmp(env) == 0)
#define catch else
#define throw longjmp(env, 1)

#define to_upper_char(c) ((c) >= 'a' && (c) <= 'z' ? (c) - 'a' + 'A' : (c))
#define to_upper(str) \
    for (int i = 0; (str)[i] != '\0'; i++) { \
        (str)[i] = to_upper_char((str)[i]); \
    }



#define guard(condition) if (!(condition)) break
#define defer(func) __attribute__((cleanup(func)))
#define println(fmt, ...) printf(fmt "\n", __VA_ARGS__)
#define len(arr) (sizeof(arr) / sizeof((arr)[0]))
#define loop while(1)
#define for_each(item, array)                                  \
	for (                                                      \
	    int _i = 0;                                            \
	    _i < len(array) && ((item = array[_i]), 1);            \
	    ++_i                                                   \
	)

#define debug(fmt, ...) fprintf(stderr, "DEBUG (%s:%d): " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define range(i, n) for (int i = 0; i < (n); ++i)
#define is_null(ptr) ((ptr) == NULL)
#define map(arr, size, func) do { \
    for (int i = 0; i < size; ++i) { \
        func(arr[i]); \
    } \
} while (0)

#define alloc(type, count) ((type*)malloc(sizeof(type) * (count)))
#define cls() system("clear")

#define with_file(filename, mode, file_ptr) \
    for (FILE *file_ptr = fopen(filename, mode); file_ptr != NULL; fclose(file_ptr), file_ptr = NULL)

#define benchmark(code_block)                         \
    do {                                              \
        clock_t start = clock();                      \
        code_block;                                   \
        clock_t end = clock();                        \
        double time_spent = (double)(end - start) / CLOCKS_PER_SEC; \
        println("Execution time: %.6f seconds", time_spent); \
    } while (0)

#define print_array_int(arr)                                \
    do {                                                    \
        printf("[ ");                                       \
        for (size_t i = 0; i < len(arr); i++) {             \
            printf("%d", arr[i]);                           \
            if (i != len(arr) - 1) {                        \
                printf(", ");                               \
            } else {                                        \
                printf(" ");                                \
            }                                               \
        }                                                   \
        printf("]\n");                                      \
    } while (0)

void print_double(int x) {
    printf("%d ", x * 2);
}

void close_file(FILE **file) {
    if (*file) fclose(*file);
}

int main() {

    try {
        printf("Trying...\n");
        throw;
        printf("This won't be executed\n");
    } catch {
        printf("An error occurred!\n");
    }

    println("Value: %s\n", to_string(42));  // Saída: Value: 42

    int x = 1;
    do {
        guard(x > 0);
        printf("x is positive\n");
    } while (0);

    with_file("example.txt", "w", file) {
        if (is_null(file)) {
            perror("Failed to open file");
            return 1;
        }
        fprintf(file, "Hello, world!\n");
    }

    FILE *file defer(close_file) = fopen("example.txt", "w");
    if (!file) {
        perror("Failed to open file");
        return 1;
    }
    fprintf(file, "Hello, world!\n");

    int age = 32;
    println("My age: %d", age);

    range(i, 5) {
        println("Iteration %d", i);
    }

    benchmark({
        int j = 1;
        range(i, 1000000) {
            j = j + i;
        }
    });

    int numbers[] = {1, 2, 3, 4, 5};
    println("Array size: %lu", len(numbers));

    int value = 42;
    debug("Value is: %d", value);

    int numbers2[] = {10, 20, 30, 40};
    int num;

    for_each(num, numbers2) {
        println("Number: %d", num);
    }

    int k = 0;
    loop {
        k++;
        println("k = %d", k);
        if (k > 30) {
            break;
        }
    }

    int arr1[] = {1, 2, 3, 4, 5};
    print_array_int(arr1);


    int* arr2 = alloc(int, 10);
    free(arr2);

    int arr3[] = {1, 2, 3, 4};

    map(arr3, 4, print_double);
    puts("");

    char str[] = "Hello, world!";
    to_upper(str);
    printf("Uppercase string: %s\n", str);

    // cls();

    return 0;
}

