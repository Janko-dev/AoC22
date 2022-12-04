#include <stdio.h>
#include <stdlib.h>

int main(void){

    FILE* f = fopen("input.txt", "r");
    char buf[0xf];

    size_t total_part1 = 0;
    size_t total_part2 = 0;
    
    while (fgets(buf, sizeof(buf), f) != NULL){

        char* ptr = buf;

        int p1_low = strtol(ptr, &ptr, 10);     // number
        ptr++;                                  // -
        int p1_high = strtol(ptr, &ptr, 10);    // number
        ptr++;                                  // ,
        int p2_low = strtol(ptr, &ptr, 10);     // number
        ptr++;                                  // -
        int p2_high = strtol(ptr, &ptr, 10);    // number

        
        if (p1_low >= p2_low && p1_high <= p2_high) {
            total_part1++;
        } else if (p2_low >= p1_low && p2_high <= p1_high){
            total_part1++;
        }

        if ((p1_low >= p2_low  && p1_low <= p2_high) ||
            (p1_high >= p2_low && p1_high <= p2_high)) {
            total_part2++;
        } else 
        if ((p2_low >= p1_low  && p2_low <= p1_high) ||
            (p2_high >= p1_low && p2_high <= p1_high)){
            total_part2++;
        }
    }
    fclose(f);
    
    printf("total part 1: %d\n", total_part1);
    printf("total part 2: %d\n", total_part2);

    return 0;
}