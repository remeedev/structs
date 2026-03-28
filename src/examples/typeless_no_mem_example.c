// To run this code run from ../../, so from main.
//      make test typeless_no_mem

// This example uses no trash handling for memory, it is not recommended to do so
// Nevertheless it is added for other travelers to consider the same as me,
// it is not worth it to not use the trash disposal
//
// Compared to trash disposal usage:
//
// typeless_no_mem ->104 allocs and frees (2,423 Bytes total), of course
// typeless ->2,275 allocs and frees (292,898 Bytes total), clearly one is memory friendly and the other one isn't

#include <stdio.h>
#include <stdlib.h>

#include "../imported/headers/hmem.h"
#include "../imported/headers/typeless.h"
#include "../imported/headers/array.h"
#include "../imported/headers/hash-table.h" //dict

int main(int argc, char *argv[]){
    obj str_obj = create_string_obj("Hello, world!");
    char *raw_obj;
    char *plain_obj;
    printf("Raw obj: %s\n", raw_obj = get_raw_obj(str_obj));
    printf("Plain obj: %s\n", plain_obj = get_plain_obj(str_obj));
    free_obj(str_obj);
    hfree(raw_obj);
    hfree(plain_obj);

    obj int_obj = create_int_obj(19);
    printf("Raw obj: %s == Plain obj: %s\n", raw_obj = get_raw_obj(int_obj), plain_obj = get_plain_obj(int_obj));
    free_obj(int_obj);
    hfree(raw_obj);
    hfree(plain_obj);

    obj float_obj = create_decimal_obj(-10.5);
    printf("Raw obj: %s == Plain obj: %s\n", raw_obj = get_raw_obj(float_obj), plain_obj = get_plain_obj(float_obj));
    free_obj(float_obj);
    hfree(raw_obj);
    hfree(plain_obj);

    obj array_obj = create_empty_array_obj();
    array_append_pointer(obj_get_array_addr(array_obj), create_int_obj(19));
    array_append_pointer(obj_get_array_addr(array_obj), create_decimal_obj(-420.69));
    array_append_pointer(obj_get_array_addr(array_obj), create_string_obj("--, please"));

    obj nested_array = create_empty_array_obj();
    array_append_pointer(obj_get_array_addr(nested_array), create_int_obj(420));
    array_append_pointer(obj_get_array_addr(nested_array), create_string_obj("Testing, please"));

    array_append_pointer(obj_get_array_addr(array_obj), nested_array);

    printf("Getting raw list...\n");
    raw_obj = get_raw_obj(array_obj);
    printf("Raw List: %s\n", raw_obj);
    free(raw_obj);

    free_obj(array_obj);

    obj dict_obj = create_empty_dict_obj();
    dict* d_addr = obj_get_dict_addr(dict_obj);
    dict d = *d_addr;

    dict_add_pointer(d_addr, "test", create_int_obj(15));
    dict_add_pointer(d_addr, "weird", create_string_obj("dumb"));
    dict_add_pointer(d_addr, "list", create_empty_array_obj());

    obj dict_arr_obj = dict_get(d, "list");
    array *d_arr_addr = obj_get_dict_addr(dict_arr_obj);
    array d_arr = *d_arr_addr;
    array_append_pointer(d_arr_addr, create_string_obj("random string, literally"));
    array_append_pointer(d_arr_addr, create_int_obj(69));

    raw_obj = get_raw_obj(dict_obj);
    printf("Raw dict: %s\n", raw_obj);
    hfree(raw_obj);

    free_obj(d_addr);

    return 0;
}
