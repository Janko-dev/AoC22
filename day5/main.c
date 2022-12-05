#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_STACKS 9
#define STACK_SIZE 0xff

typedef struct {
    char stacks[NUM_STACKS][0xff];
    int sptr[NUM_STACKS];
} Stacks;

void push(Stacks* part, char c, int index){
    part->stacks[index][part->sptr[index]++] = c;
}

char pop(Stacks* part, int index){
    return part->stacks[index][--part->sptr[index]];
}

int main(void){

    FILE* f = fopen("input.txt", "r");
    char buf[STACK_SIZE];

    Stacks part1 = {0};
    Stacks part2 = {0};

    while (fgets(buf, sizeof(buf), f) != NULL){
        size_t len = strlen(buf);
        if (*buf == 'm') {
            // move crane part 1
            int num, from, to;
            sscanf(buf, "move %d from %d to %d", &num, &from, &to);
            for (int i = 0; i < num; i++){
                char c = pop(&part1, from-1);
                push(&part1, c, to-1);
            }

            // move crane part 2
            part2.sptr[from-1] -= num;

            memmove(part2.stacks[to-1] + part2.sptr[to-1], 
                    part2.stacks[from-1] + part2.sptr[from-1], 
                    num);
            
            part2.sptr[to-1] += num;
            
            memset(part2.stacks[from-1] + part2.sptr[from-1], 0, num);
            
        } else if (isdigit(buf[1])) {
            // memmove stack to front
            for (int i = 0; i <  NUM_STACKS; i++){
                memmove(part1.stacks[i], 
                        part1.stacks[i] + STACK_SIZE - part1.sptr[i], 
                        part1.sptr[i]);
                        
                memset(part1.stacks[i] + STACK_SIZE - part1.sptr[i], 
                        0, 
                        part1.sptr[i]);
            }
            // copy part1 stacks to part2 stacks
            memcpy(&part2, &part1, sizeof(part1));
            
        } else {
            //  Create stack
            for (size_t i = 0; i < len; i++){
                if (isalpha(buf[i])){
                    int index = i/4;
                    part1.stacks[index][STACK_SIZE - 1 - part1.sptr[index]] = buf[i];
                    part1.sptr[index]++;
                }
            }
        }
    }
    fclose(f);

    printf("result part 1: ");
    for (int i = 0; i < NUM_STACKS; i++){
        printf("%c", part1.stacks[i][part1.sptr[i]-1]);
    }
    printf("\n");

    printf("result part 2: ");
    for (int i = 0; i < NUM_STACKS; i++){
        printf("%c", part2.stacks[i][part2.sptr[i]-1]);
    }
    printf("\n");

    return 0;
}