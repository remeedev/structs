// To run this code run from ../../, so from main.
//      make test dict 


// Example for hash_table or dict, whatever u wanna call it
#include <stdio.h>
#include <stdlib.h>
#include "../imported/headers/hash-table.h"

int main(int argc, char *argv[]){
    dict new_dict = create_dict(11); // Receives capacity as argument
    dict_add_int(&new_dict, "value", 1);
    dict_add_int(&new_dict, "other_value", 25);
    printf("Value: %d\n", *(int *)dict_get(new_dict, "value")); // For universal typing must cast
    printf("Other value: %d\n", *(int *)dict_get(new_dict, "other_value"));
    // Example of manual free;
    free(dict_get(new_dict, "value"));
    dict_put_pointer_no_free(&new_dict, "value", NULL); // Will only put on existent values
    free_dict(new_dict);
    return 0;
}
