#include <stdint.h>
#include <stdio.h> 
#include "my_lib.h"
#include "config.h"

int main() {
    printf("Projeto %s, versão %d.%d.%d\n",
        PROJECT_NAME,
        PROJECT_VERSION_MAJOR, 
        PROJECT_VERSION_MINOR, 
        PROJECT_VERSION_PATCH);

    say_hello();

    return 0;
}
