#include "../imported/headers/typeless.h"
#include "../imported/headers/hmem.h"

#include <stdio.h>

int main(int argc, char *argv[]){
    obj test = read_to_obj("{\"test\": true, \"extra\":15, \"true\":false}");
    char *raw_written = get_raw_obj(test);
    printf("%s\n", raw_written);
    hfree(raw_written);
    free_obj(test);
    return 0;
}
