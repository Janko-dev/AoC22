#include <stdio.h>

int ABC_to_index(char c){
    return c - 'A';
}

int XYZ_to_index(char c){
    return c - 'X';
}

int points_matrix_p1[3][3] = {
  // X  Y  Z
  // R  P  S => player
    {3, 6, 0}, // R (A) 
    {0, 3, 6}, // P (B) => opponent
    {6, 0, 3}, // S (C)
};

int points_matrix_p2[3][3] = {
  // X  Y  Z => player
    {3, 1, 2}, // R (A)  
    {1, 2, 3}, // P (B) => opponent
    {2, 3, 1}, // S (C)
};

int round_points[3] = {0, 3, 6};

int main(void){

    FILE* f = fopen("input.txt", "r");

    char buf[10];
    size_t total_score_part1 = 0;
    size_t total_score_part2 = 0;
    while (fgets(buf, sizeof(buf), f) != NULL){
        int opponent_index = ABC_to_index(buf[0]);
        int player_index = XYZ_to_index(buf[2]);
        total_score_part1 += points_matrix_p1[opponent_index][player_index] + (player_index+1);
        total_score_part2 += points_matrix_p2[opponent_index][player_index] + round_points[player_index];
    }
    printf("total score part 1: %d\n", total_score_part1);
    printf("total score part 2: %d\n", total_score_part2);
    fclose(f);
    
    return 0;
}