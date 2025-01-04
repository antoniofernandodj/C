#include <stdio.h>

typedef struct {
    int (*request)(void);
} Service;

int real_service() {
    printf("Real Service: executando solicitação\n");
    return 42;
}

int proxy_service() {
    printf("Proxy: verificando acesso...\n");
    printf("Proxy: encaminhando para o serviço real\n");
    return real_service();
}

int main() {
    Service proxy = { proxy_service };

    int result = proxy.request();
    printf("Resultado: %d\n", result);

    return 0;
}
