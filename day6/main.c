#include <stdio.h>

#define CHAR_SIZE 14

int is_uniq(char* buf, size_t size){
    for (size_t i = 0; i < size; i++){
        for (size_t j = i; j < size; j++){
            if (i == j) continue;
            // printf("buf[%d] = %c, buf[%d] = %c\n", i, buf[i], j, buf[j]);
            if(buf[i] == buf[j]) return 0;
        }
    }
    return 1;
}

int main(void){

    FILE* f = fopen("input.txt", "r");
    size_t count = 0;
    char buf[15] = {0};

    while(fgets(buf, sizeof(buf), f) != NULL){
        
        // printf("%s\n", buf);
        
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