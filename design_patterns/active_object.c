#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Active Object

typedef struct {
    int data[10];
    int head;
    int tail;
} Queue;

Queue queue = { .head = 0, .tail = 0 };
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* worker(void* arg) {
    while (1) {
        pthread_mutex_lock(&lock);

        while (queue.head == queue.tail) {
            pthread_cond_wait(&cond, &lock);
        }

        int task = queue.data[queue.head++];
        queue.head %= 10;

        pthread_mutex_unlock(&lock);

        printf("Processando tarefa: %d\n", task);
        sleep(1);
    }
}

void enqueue_task(int task) {
    pthread_mutex_lock(&lock);

    queue.data[queue.tail++] = task;
    queue.tail %= 10;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
}

int main() {
    pthread_t thread;
    pthread_create(&thread, NULL, worker, NULL);

    for (int i = 0; i < 5; ++i) {
        enqueue_task(i);
        sleep(1);
    }

    pthread_join(thread, NULL);
    return 0;
}