#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUF_SIZE 0xff

typedef enum {
    AOC_DIR,
    AOC_FILE,
} FileType;

typedef struct AoC_Dir AoC_Dir;
typedef struct AoC_File AoC_File;

struct AoC_File{
    FileType type;
    size_t file_size;
    char* name;
    AoC_File* parent;
    AoC_Dir* dir;
};

struct AoC_Dir {
    size_t len;
    AoC_File files[BUF_SIZE];
};

void append_to_dir(AoC_File* f, FileType type, char* name, size_t size){
    f->dir->files[f->dir->len] = (AoC_File){
        .type=type,
        .dir=NULL,
        .file_size=size,
        .name=name,
        .parent=f,
    };
    f->dir->len++;
    f->file_size += size;
    // propagate size to all parents
    AoC_File* temp = f;
    while (temp->parent != NULL){
        temp->parent->file_size += size;
        temp = temp->parent;
    }
}

void print_file(AoC_File* f, int indent){
    for (int i = 0; i < indent; i++) printf(" ");
    if (f->type == AOC_FILE){
        printf("file: %d, %s", f->file_size, f->name);
    } else {
        if (f->dir == NULL) return;
        printf("dir: %d, %s", f->file_size, f->name);
        for (size_t i = 0; i < f->dir->len; i++){
            print_file(f->dir->files + i, indent + 4);
        }
    }
}

void print_part1(AoC_File* f, size_t* sum){
    if (f->type == AOC_DIR){
        if (f->file_size <= 100000) {
            printf("dir: %d, %s", f->file_size, f->name);
            *sum += f->file_size;
        }
        for (size_t i = 0; i < f->dir->len; i++){
            print_part1(f->dir->files + i, sum);
        }
    }
}

void find_smallest_with_size(size_t size, AoC_File* f, AoC_File* smallest){
    if (f->type == AOC_DIR){
        if (f->file_size >= size && f->file_size < smallest->file_size) {
            *smallest = *f;
        }
        for (size_t i = 0; i < f->dir->len; i++){
            find_smallest_with_size(size, f->dir->files + i, smallest);
        }
    }
}

void free_file(AoC_File* f){
    if (f->type == AOC_FILE){
        free(f->name);
        free(f);
    } else if (f->dir != NULL){
        for (size_t i = 0; i < f->dir->len; i++){
            free_file(f->dir->files + i);
        }
        free(f->name);
        free(f->dir);
        free(f);
    }
}

int main(void){

    FILE* f = fopen("input.txt", "r");
    AoC_File root = (AoC_File){
        .type=AOC_DIR,
        .name="/\n",
        .file_size=0, 
        .dir=NULL,
        .parent=NULL
    };

    AoC_File* current_dir = &root;

    char buf[BUF_SIZE] = {0};

    while(fgets(buf, sizeof(buf), f) != NULL){
        if (buf[0] == '$') {
            // command
            if (memcmp(buf+2, "cd", 2) == 0) {
                char* target = buf+5;
                if (target[0] == '.' && target[1] == '.') {
                    if (current_dir->parent != NULL) current_dir = current_dir->parent;
                } else if (target[0] == '/') {
                    current_dir = &root;
                } else {
                    for (size_t i = 0; i < current_dir->dir->len; i++){
                        if (strcmp(current_dir->dir->files[i].name, target) == 0){
                            current_dir = &current_dir->dir->files[i];
                            break;
                        } 
                    }
                }
            } else if (memcmp(buf+2, "ls", 2) == 0) {
                if (current_dir->dir == NULL){
                    current_dir->dir = (AoC_Dir*)calloc(1, sizeof(AoC_Dir));
                }
            }
        } else {
            // file
            if (*buf >= '0' && *buf <= '9') {
                char* name;
                size_t size = strtol(buf, &name, 10);
                char* copy_name = malloc(strlen(name+1)+1);
                strcpy(copy_name, name+1);
                append_to_dir(current_dir, AOC_FILE, copy_name, size);
            } else {
                // dir
                char* copy_name = malloc(strlen(buf+4)+1);
                strcpy(copy_name, buf+4);
                append_to_dir(current_dir, AOC_DIR, copy_name, 0);
            }
        }
    }
    // size_t sum = 0;
    // print_part1(&root, &sum);
    // printf("Total sum at most 100 000: %d\n", sum);
    
    size_t disk_space = 30000000 - (70000000 - root.file_size);
    printf("%d\n", disk_space);
    AoC_File* smallest = &root;
    find_smallest_with_size(disk_space, &root, smallest);
    print_file(smallest, 0);

    free_file(&root);
    fclose(f);
    return 0;
}