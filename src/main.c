#include "imported/headers/typeless.h"
#include "imported/headers/hash-table.h"
#include "imported/headers/hmem.h"

#include <stdio.h>

int main(int argc, char *argv[]){
    printf("Hello, world!\n");
    obj test = create_empty_dict_obj();
    dict *d_addr = obj_get_dict_addr(test);
    dict_add_pointer(d_addr, "test", create_bool_obj(1));
    char *raw_written = get_raw_obj(test);
    printf("%s\n", raw_written);
    hfree(raw_written);
    free_obj(test);
    return 0;
}
