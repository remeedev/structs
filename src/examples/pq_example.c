// To run this code run from ../../, so from main.
//      make test pq

// Example for a priority queue

#include <stdlib.h>
#include <stdio.h>

#include "../imported/headers/priority_queue.h"

int main(int argc, char *argv[]){
    pq new_pq = create_pq(0); // Pass 1 or 0 for Max heap or Min heap
    pq_push_int(new_pq, 5, 5);
    pq_push_int(new_pq, 1, 1);
    pq_push_int(new_pq, 14, 14);
    pq_push_int(new_pq, 12, 12);
    pq_push_int(new_pq, 6, 6);
    pq_push_int(new_pq, 15, 15);
    pq_push_int(new_pq, 0, 0);
    pq_push_int(new_pq, 1, 1);
    for (int i = 0; i < 4; i++){
        // Partial read
        int *num = pq_pop(new_pq);

        printf("%d\n", *num);

        // Must free content
        free(num);
    }
    free_pq(new_pq);
    return 0;
}
