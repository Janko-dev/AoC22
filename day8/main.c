#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUF_SIZE 0xffffff

char grid[BUF_SIZE] = {0};

size_t part1(size_t width, size_t height){

    size_t total = 2*(width-1) + 2*(height-2);
    for (size_t i = 0; i < width*height; i++){
        size_t x = i % width;
        size_t y = i / width;
        if (x == 0 || x >= width-2 || y == 0 || y == height-1) continue;

        char current = grid[x + y * width];
        int is_visible = 1;
        for (size_t j = 0; j < x; j++){
            if (grid[j + y * width] >= current){
                is_visible = 0;
                break;
            }
        }
        if (is_visible){
            total++;
            continue;
        }
        
        is_visible = 1;
        for (size_t j = x+1; j < width-1; j++){
            if (grid[j + y * width] >= current){
                is_visible = 0;
                break;
            }
        }
        if (is_visible){
            total++;
            continue;
        }

        is_visible = 1;
        for (size_t j = 0; j < y; j++){
            if (grid[x + j * width] >= current){
                is_visible = 0;
                break;
            }
        }
        if (is_visible){
            total++;
            continue;
        }

        is_visible = 1;
        for (size_t j = y+1; j < height; j++){
            if (grid[x + j * width] >= current){
                is_visible = 0;
                break;
            }
        }
        if (is_visible){
            total++;
            continue;
        }
    }
    return total;
}

size_t part2(size_t width, size_t height){    
    size_t best_viewing_score = 0;

    for (size_t i = 0; i < width*height; i++){
        size_t x = i % width;
        size_t y = i / width;
        if (x == 0 || x >= width-2 || y == 0 || y == height-1) continue;

        char current = grid[x + y * width];
        size_t left = 0;
        for (int j = x-1; j >= 0; j--){
            left++;
            if (grid[j + y * width] >= current) break;
        }
        size_t right = 0;
        for (int j = x+1; j < width-1; j++){
            right++;
            if (grid[j + y * width] >= current) break;
        }
        size_t up = 0;
        for (int j = y-1; j >= 0; j--){
            up++;
            if (grid[x + j * width] >= current) break;
        }
        size_t down = 0;
        for (int j = y+1; j < height; j++){
            down++;
            if (grid[x + j * width] >= current) break;
        }
        // printf("score %c: %d*%d*%d*%d = %d\n", current, left, right, up, down, left*right*up*down);
        if (up*down*left*right > best_viewing_score){
            best_viewing_score = up*down*left*right;
        }
    }
    return best_viewing_score;
}

int main(void){

    FILE* f = fopen("input.txt", "r");
    fseek(f, 0L, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0L, SEEK_SET);
    fread(grid, sizeof(char), size, f);

    char* first_occur = strchr(grid, '\n');
    size_t width = (size_t)(first_occur - grid) + 1;
    size_t height = size/width;

    // printf("Total part 1: %d", part1(width, height));
    printf("Total part 2: %d", part2(width, height));

    fclose(f);
    return 0;
}