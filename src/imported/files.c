#include "headers/ezstr.h"

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

void write_to_file(char *file_name, char *content){
    FILE *file = fopen(file_name, "w");
    if (file == NULL){
        print_file_not_found(file_name);
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);
}
