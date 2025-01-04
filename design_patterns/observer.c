#include <stdio.h>
#include <stdlib.h>

typedef struct Observer {
    void (*update)(int);
} Observer;

typedef struct {
    Observer** observers;
    int count;
} Subject;

void attach(Subject* subject, Observer* observer) {
    subject->observers = (Observer**)realloc(subject->observers, sizeof(Observer*) * (subject->count + 1));
    subject->observers[subject->count++] = observer;
}

void notify(Subject* subject, int state) {
    for (int i = 0; i < subject->count; ++i) {
        subject->observers[i]->update(state);
    }
}

void observer_update(int state) {
    printf("Observer notificado: estado = %d\n", state);
}

int main() {
    Subject subject = { NULL, 0 };

    Observer observer1 = { observer_update };
    attach(&subject, &observer1);

    Observer observer2 = { observer_update };
    attach(&subject, &observer2);

    notify(&subject, 10);

    free(subject.observers);
    return 0;
}
