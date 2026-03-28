// To run this code run from ../../, so from main.
//      make test files 

#include <stdio.h>

#include "../imported/headers/files.h"
#include "../imported/headers/bytes.h"

int main(int argc, char *argv[]){
    char *file_name = "./src/examples/files_example.c";
    string self_content = read_file(file_name);
    printf("Content:\n%s\nEOF\n", self_content);
    if (get_string_size(self_content)%2 == 0){
        concat_to_str(&self_content, "//  Hello!\n");
    }else{
        concat_to_str(&self_content, "//  Goodbye!\n");
    }
    write_to_file(file_name, self_content); // Writes to self, no change
    free_string(self_content);
    size_t size;
    unsigned char *self_compiled = read_file_bytes("./src/examples/files_example.c", &size);
    printf("Size of self : %lu bytes\n", size);
    free(self_compiled);
    return 0;
}

// Written by self:
