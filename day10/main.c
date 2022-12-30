#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 0xff
#define CRT_SIZE 40

char CRT[CRT_SIZE] = {0};
char sprite_pos[CRT_SIZE] = {0};

void part1_cycle(int* sum, int cycles, int reg){
    if (cycles % 40 == 20){
        *sum += cycles*reg;
    }
}

void part2_cycle(int cycles){
    int index = (cycles%CRT_SIZE) - 1; 
    CRT[index] = sprite_pos[index+1] == '#' ? '#' : '.';
    if (cycles % CRT_SIZE == 0) {
        printf("current CRT row: [%.*s] %d\n", CRT_SIZE, CRT, cycles);
        memset(CRT, ' ', CRT_SIZE);
    }
}

int main(void){

    FILE* f = fopen("test.txt", "r");
    char buf[BUF_SIZE] = {0};
    int reg = 1;
    int cycles = 0; 
    int sum = 0;

    memset(CRT, ' ', CRT_SIZE);
    
    memset(sprite_pos, '.', CRT_SIZE);
    memset(sprite_pos, '#', 3);
    
    while(fgets(buf, sizeof(buf), f) != NULL){
        if (*buf == 'a'){
            int operand = strtol(buf+4, NULL, 10);

            cycles++;
            part1_cycle(&sum, cycles, reg);
            part2_cycle(cycles);

            cycles++;
            part1_cycle(&sum, cycles, reg);
            part2_cycle(cycles);

            reg += operand;
            memset(sprite_pos, '.', CRT_SIZE);
            memset(sprite_pos+reg, '#', 3);
        } else if (*buf == 'n'){
            cycles++;
            part1_cycle(&sum, cycles, reg);
            part2_cycle(cycles);
        }
    }
    printf("sum = %d\n", sum);

    fclose(f);
    return 0;
}