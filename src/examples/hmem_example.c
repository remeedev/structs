// To run this code run from ../../, so from main.
//      make test hmem 

#include <stdio.h>
#include "../imported/headers/hmem.h"

int main(int argc, char *argv[]){
    void *tmp = hmalloc(15); // technically don't need memory registering to malloc memory, requires manual free though
    hfree(tmp);

    start_memory_registering(); // Gotta turn on memory registering

    printf("Allocated: %p\n", hmalloc(15));
    printf("Allocated: %p\n", hmalloc(15));
    printf("Allocated: %p\n", hmalloc(15));

    char *aa = hmalloc(5); // Allocate idk 5 bytes for hello
                           // But hello is 6 so:
    aa = hrealloc(aa, 6);
    for (int i = 0; i < 6; i++){
        aa[i] = "hello"[i];
    }
    printf("%s\n", aa);
    hfree(aa);

    printf("Total mallocs: %d\n", get_currently_malloced_size());

    end_memory_registering();
}
