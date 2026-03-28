// To run this code run from ../../, so from main.
//      make test array
// Example code for array

#include <stdio.h>
#include <stdlib.h>
#include "../imported/headers/array.h"

int main(int argc, char *argv[]){
    array new_array = create_array();
    for (int i = 0; i < 10; i++){
        array_append_int(&new_array, i); // General struct for append command: array_append_<type>
        printf("%d\n", *((int **)new_array)[i]); // indexing works like with a regular array, for type support
                                      // it uses (void *), must cast for correct type usage.
                                      //
                                      // e.g. *((int **)new_array)[i] or *(int *)(new_array[i]);
    }
    printf("Array size: %d == 10\n", get_array_size(new_array));
    // Example of manual freeing
    free(new_array[0]);
    new_array[0] = NULL;
    free_array(new_array); // Regular free func, will free all elements added
                           // For manual freeing must set value at array[i] = NULL;
                           // being i the element freed.
    return 0;
}
