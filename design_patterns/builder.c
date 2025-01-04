#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* name;
    int age;
} Person;

typedef struct {
    char* name;
    int age;
} PersonBuilder;

PersonBuilder* create_person_builder() {
    PersonBuilder* builder = malloc(sizeof(PersonBuilder));
    builder->name = NULL;
    builder->age = 0;
    return builder;
}

void set_name(PersonBuilder* builder, const char* name) {
    builder->name = strdup(name);
}

void set_age(PersonBuilder* builder, int age) {
    builder->age = age;
}

Person* build_person(PersonBuilder* builder) {
    Person* person = malloc(sizeof(Person));
    person->name = builder->name;
    person->age = builder->age;
    free(builder);
    return person;
}

int main() {
    PersonBuilder* builder = create_person_builder();
    set_name(builder, "John");
    set_age(builder, 30);

    Person* person = build_person(builder);
    printf("Nome: %s, Idade: %d\n", person->name, person->age);

    free(person->name);
    free(person);
    return 0;
}
