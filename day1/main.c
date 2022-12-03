#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    size_t cap;
    size_t index;
    size_t* elements;
} List;

void push_element(List* lst, size_t value){
    if (lst->index == lst->cap){
        lst->cap = lst->cap == 0 ? 8 : lst->cap * 2;
        lst->elements = realloc(lst->elements, lst->cap * sizeof(size_t));
        if (lst->elements == NULL){
            fprintf(stderr, "An error occurred during allocation: %s", strerror(errno));
        }
    }
    lst->elements[lst->index++] = value;
}

int is_bigger(const void* a, const void* b){
    return *(int*)b - *(int*)a;
}

int main(void){

    FILE* f = fopen("input.txt", "r");
    List calories = {0};

    char buf[10];
    size_t sum = 0;
    while (fgets(buf, sizeof(buf), f) != NULL){
        if (*buf == '\n') {
            push_element(&calories, sum);
            sum = 0;
        }
        sum += strtol(buf, NULL, 10);
    }
    qsort(calories.elements, calories.index, sizeof(size_t), is_bigger);

    printf("1. %ld\n", calories.elements[0]);
    printf("2. %ld\n", calories.elements[1]);
    printf("3. %ld\n", calories.elements[2]);

    printf("Total. %ld\n", 
        calories.elements[0] +
        calories.elements[1] +
        calories.elements[2]);
    
    free(calories.elements);
    return 0;
}