#include "headers/ezstr.h"
#include "headers/messages.h"
#include "headers/hmem.h"

#include <stdio.h>

void print_file_not_found(char *file_name){
    printf("There has been an error opening the file '%s'\n", file_name);
}

string read_file(char *file_name){
    FILE* file = fopen(file_name, "r");
    if (file == NULL){
        print_file_not_found(file_name);
        return NULL;
    }

    string out = create_empty_string();
    char a;
    while ((a = fgetc(file)) != EOF){
        concat_char_to_str(&out, a);
    }

    fclose(file);
    return out;
}

unsigned char *read_file_bytes(char *file_name, size_t *size){
    FILE *file = fopen(file_name, "rb");
    if (file == NULL){
        print_file_not_found(file_name);
        *size = -1;
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    *size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    unsigned char *out = hmalloc(*size);
    if (out == NULL){
        mem_alloc_error(*size, "file bytes");
        *size = -1;
        return NULL;
    }
    for (int i = 0; i < *size; i++) out[i] = 0;
    fread(out, *size, 1, file);
    fclose(file);
    return out;
}

void write_to_file(char *file_name, char *content){
    FILE *file = fopen(file_name, "w");
    if (file == NULL){
        print_file_not_found(file_name);
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);
}

void write_bytes_to_file(char *file_name, unsigned char *bytes, size_t size){
    FILE *file = fopen(file_name, "wb");
    if (file == NULL){
        print_file_not_found(file_name);
        return;
    }
    fwrite(bytes, size, 1, file);
    fclose(file);
}

int is_file_bytes(char *file_name){
    size_t size;
    unsigned char *file_content = read_file_bytes(file_name, &size);
    for (int i = 0; i < size; i++){
        if ((file_content[i] < 32 || file_content[i] > 127) && file_content[i] != '\n'){
            hfree(file_content);
            return 1;
        }
    }
    hfree(file_content);
    return 0;
}
