// To run this code run from ../../, so from main.
//      make test list 

// Example for a linked list

#include <stdio.h>
#include <stdlib.h>

#include "../imported/headers/list.h"

int main(int argc, char *argv[]){
    list new_list = create_list();
    for (int i = 0; i < 10; i++){
        list_append_int(new_list, i);
    }
    node first_elem = get_first_node(new_list);
    void *prev = NULL;
    while (first_elem != NULL){
        printf("%d\n", *(int *)get_node_content(first_elem));
        void *tmp = first_elem;
        first_elem = node_xor(first_elem, prev);
        prev = tmp;
    }
    // Manual free is possible, would require maintaining list consistency.
    // Solution:
    list_pop(new_list, 5);
    free_list(new_list);
    return 0;
}
