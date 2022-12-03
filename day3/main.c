#include <stdio.h>
#include <string.h>

#define ITEM_SIZE ('z' - 'A' + 1)
#define AS_INDEX(c) ((int)((c) - 'A'))

int to_priority(char c){
    return c >= 'a' && c <= 'z' ? 
        (c - 'a') + 1 :
        (c - 'A') + 27;
}

// Part 1
int find_dup_prio(char* buf, size_t len){
    char items[ITEM_SIZE] = {0};
    // First compartment
    for (size_t i = 0; i < len/2; i++)
        items[AS_INDEX(buf[i])]++;

    // Second compartment
    for (size_t i = len/2; i < len; i++){
        if (items[AS_INDEX(buf[i])] > 0){
            printf("Dupe: %c, index: %d, priority: %d\n", buf[i], AS_INDEX(buf[i]), to_priority(buf[i]));
            return to_priority(buf[i]);
        }
    }
    return 0;
}

// Part 2
int find_group_prio(char* buf, size_t len, size_t i, char* group_items){
    
    char items[ITEM_SIZE] = {0};
    for (size_t j = 0; j < len; j++){
        if (items[AS_INDEX(buf[j])] == 0){
            items[AS_INDEX(buf[j])] = 1;
            group_items[AS_INDEX(buf[j])]++;
        }
    }

    if (i > 0 && i % 3 == 2){
        for (int j = 0; j < ITEM_SIZE; j++){
            if (group_items[j] == 3){
                memset(group_items, 0, ITEM_SIZE);
                return to_priority(j + 'A');
            }
        }
    }
    return 0;
}

int main(void){

    FILE* f = fopen("input.txt", "r");

    char buf[0xff];
    size_t sum_prios = 0;
    size_t sum_group_prios = 0;
    
    char group_items[ITEM_SIZE] = {0};
    
    for (size_t i = 0; fgets(buf, sizeof(buf), f) != NULL; i++){

        // calculate line length
        size_t len = 0;
        for (char* c = buf; *c != '\n' && *c != '\0'; c++, len++); 

        sum_prios       += find_dup_prio(buf, len);                   // part 1
        sum_group_prios += find_group_prio(buf, len, i, group_items); // part 2

    }
    printf("Part 1 sum duplicate priorities: %d\n", sum_prios);
    printf("Part 2 sum group priorities: %d\n", sum_group_prios);

    fclose(f);
    
    return 0;
}