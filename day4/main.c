#include <stdio.h>

int main(void){

    FILE* f = fopen("input.txt", "r");
    char buf[0xf];

    size_t total_part1 = 0;
    size_t total_part2 = 0;
    
    while (fgets(buf, sizeof(buf), f) != NULL){

        int p1_low, p1_high, p2_low, p2_high;
        sscanf(buf, "%d-%d,%d-%d", 
            &p1_low, &p1_high,
            &p2_low, &p2_high);

        total_part1 += (p1_low >= p2_low && p1_high <= p2_high) || 
                       (p2_low >= p1_low && p2_high <= p1_high);
        
        // total_part2 += ((p1_low >= p2_low  && p1_low <= p2_high)   ||
        //                 (p1_high >= p2_low && p1_high <= p2_high)) ||
        //                ((p2_low >= p1_low  && p2_low <= p1_high)   ||
        //                 (p2_high >= p1_low && p2_high <= p1_high));
        
        total_part2 += (p1_low <= p2_low && p1_high >= p2_low) || 
                       (!(p1_low <= p2_low)  && p2_high >= p1_low);
    }
    fclose(f);
    
    printf("total part 1: %d\n", total_part1);
    printf("total part 2: %d\n", total_part2);

    return 0;
}