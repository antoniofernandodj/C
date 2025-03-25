#include <stdio.h>


int main(int argc, char** argv) {

    int arr[10] = {0};
    for (int i = 0; i < 10; i++) {
        arr[i] = i * 2;
    }


    for (int i = 0; i < 10; i++) {
        printf("arr[i] = %d\n", *(arr + i));
    }
    
    return 0;
}
