#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 1024

typedef struct {
    int x;
    int y;
} Pos;

void print_visited(int grid[SIZE][SIZE]){
    for (int y = 0; y < SIZE; y++){
        for (int x = 0; x < SIZE; x++){
            printf(grid[y][x] ? "#" : ".");
        }
        printf("\n");
    }
}

void print_grid(char grid[SIZE][SIZE]){
    for (int y = 0; y < SIZE; y++){
        for (int x = 0; x < SIZE; x++){
            printf("%c", grid[y][x]);
        }
        printf("\n");
    }
}

char grid[SIZE][SIZE] = {0};
int visited[SIZE][SIZE] = {0};

int main(void){

    memset(grid, '.', SIZE*SIZE);
    grid[SIZE-1][0] = 'H';

    Pos ropes[10];
    for (int i = 0; i < 10; i++){
        ropes[i] = (Pos){SIZE/2, SIZE/2};
    }

    FILE* f = fopen("input.txt", "r");

    char buf[0xf] = {0};
    while(fgets(buf, sizeof(buf), f) != NULL){
        size_t num = strtol(buf+2, NULL, 10);
        memset(grid, '.', SIZE*SIZE);
        Pos dir = {0, 0};
        switch (*buf){
            case 'R': dir.x = 1; break;
            case 'L': dir.x = -1; break;
            case 'U': dir.y = -1; break;
            case 'D': dir.y = 1; break;
            default: break;
        }

        for (size_t i = 0; i < num; i++){
            ropes[0].x += dir.x;
            ropes[0].y += dir.y;
            
            for (size_t k = 0; k < 9; k++){
                Pos* head = &ropes[k];
                Pos* tail = &ropes[k+1];
                
                if (head->x - tail->x > 1){
                    if (head->y > tail->y) tail->y++;
                    else if (head->y < tail->y) tail->y--;
                    tail->x++;
                } else if (tail->x - head->x > 1){
                    if (head->y > tail->y) tail->y++;
                    else if (head->y < tail->y) tail->y--;
                    tail->x--;
                } else if (tail->y - head->y > 1){
                    if (head->x > tail->x) tail->x++;
                    else if (head->x < tail->x) tail->x--;
                    tail->y--;
                } else if (head->y - tail->y> 1){
                    if (head->x > tail->x) tail->x++;
                    else if (head->x < tail->x) tail->x--;
                    tail->y++;
                }
            }
            visited[ropes[9].y][ropes[9].x] = 1;
        }
        
        // grid[ropes[9].y][ropes[9].x] = 'T';
        // for (int i = 8; i >= 1; i--){
        //     grid[ropes[i].y][ropes[i].x] = '0' + i;
        // }
        // grid[ropes[0].y][ropes[0].x] = 'H';
        // printf("-----------------\n%s", buf);
        // print_grid(grid);
    }

    // print_visited(visited);
    int total = 0;
    for (int y = 0; y < SIZE; y++){
        for (int x = 0; x < SIZE; x++){
            total += visited[y][x];
        }
    }
    printf("%d\n", total);

    fclose(f);
    return 0;
}