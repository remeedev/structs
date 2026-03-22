// This example uses no trash handling for memory, it is not recommended to do so

#include <stdio.h>
#include <stdlib.h>

#include "../imported/headers/typeless.h"
#include "../imported/headers/array.h"

int main(int argc, char *argv[]){
    obj str_obj = create_string_obj("Hello, world!");
    printf("Raw obj: %s\n", get_raw_obj(str_obj));
    printf("Plain obj: %s\n", get_plain_obj(str_obj));
    free((char *)str_obj - 1);

    obj int_obj = create_int_obj(19);
    printf("Raw obj: %s == Plain obj: %s\n", get_raw_obj(int_obj), get_plain_obj(int_obj));
    free((char *)int_obj - 1);

    obj float_obj = create_decimal_obj(-10.5);
    printf("Raw obj: %s == Plain obj: %s\n", get_raw_obj(float_obj), get_plain_obj(float_obj));
    free((char *)float_obj - 1);

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

    array arr1 = get_array_from_obj(array_obj);
    for (int i = 0; i < get_array_size(arr1); i++){
        if (arr1[i] == nested_array) {
            for (int j = 0; j < get_array_size(get_array_from_obj(nested_array)); j++){
                free(*(void **)get_array_from_obj(nested_array)[j]);
                free((char *)get_array_from_obj(nested_array)[j] - 1);
                get_array_from_obj(nested_array)[j] = NULL;
            }
        }
        free(*(void **)arr1[i]);
        free((char *)arr1[i] - 1);
        arr1[i] = NULL;
    }
    printf("Raw list: %s\n", get_raw_obj(array_obj));

    free_array(get_array_from_obj(array_obj));
    free_array(get_array_from_obj(nested_array));

    return 0;
}
