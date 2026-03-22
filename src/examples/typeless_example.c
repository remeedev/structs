#include <stdio.h>
#include <stdlib.h>

#include "../imported/headers/typeless.h"
#include "../imported/headers/hmem.h"
#include "../imported/headers/array.h"

int main(int argc, char *argv[]){
    start_memory_registering(); // Therefore shows no frees for simple objs
    // All variables created are objects

    obj str_obj = create_string_obj("Hello, world!");
    printf("Raw obj: %s\n", get_raw_obj(str_obj));
    printf("Plain obj: %s\n", get_plain_obj(str_obj));

    obj int_obj = create_int_obj(19);
    printf("Raw obj: %s == Plain obj: %s\n", get_raw_obj(int_obj), get_plain_obj(int_obj));

    obj float_obj = create_decimal_obj(-10.5);
    printf("Raw obj: %s == Plain obj: %s\n", get_raw_obj(float_obj), get_plain_obj(float_obj));

    obj array_obj = create_empty_array_obj();
    array_append_pointer(get_array_addr(array_obj), create_int_obj(19));
    array_append_pointer(get_array_addr(array_obj), create_decimal_obj(-420.69));
    array_append_pointer(get_array_addr(array_obj), create_string_obj("Nigga, please"));

    obj nested_array = create_empty_array_obj();
    array_append_pointer(get_array_addr(nested_array), create_int_obj(420));
    array_append_pointer(get_array_addr(nested_array), create_string_obj("Testing, please"));

    array_append_pointer(get_array_addr(array_obj), nested_array);

    printf("Getting raw list...\n");
    printf("Raw List: %s\n", get_raw_obj(array_obj));

    free((int *)get_array_from_obj(array_obj) - 1); // Complex objects require free
    free((int *)get_array_from_obj(nested_array) - 1); // free_array tries to free all elements, must use basic free

    end_memory_registering();

    return 0;
}
