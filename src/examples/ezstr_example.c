// To run this code run from ../../, so from main.
//      make test ezstr 

#include <stdio.h>

#include "../imported/headers/ezstr.h"

int main(int argc, char *argv[]){
    string new_str = create_empty_string();
    concat_to_str(&new_str, "Hello, ");
    concat_to_str(&new_str, "world");
    concat_char_to_str(&new_str, '!');
    printf("%s\n", new_str);
    free_string(new_str);
    // yeah, that's it
    return 0;
}
