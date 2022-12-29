#include <stdio.h>

#define CHAR_SIZE 14

int is_uniq(char* buf, size_t size){
    for (size_t i = 0; i < size; i++){
        for (size_t j = i; j < size; j++){
            if (i == j) continue;
            if(buf[i] == buf[j]) return 0;
        }
    }
    return 1;
}

int main(void){

    FILE* f = fopen("input.txt", "r");
    size_t count = 0;
    char buf[CHAR_SIZE+1] = {0};

    while(fgets(buf, sizeof(buf), f) != NULL){
        
        if (is_uniq(buf, CHAR_SIZE)){
            break;
        }
        count++;
        fseek(f, count, SEEK_SET);
    }
    printf("%d\n", count+CHAR_SIZE);

    fclose(f);
    return 0;
}