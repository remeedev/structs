#include <stdio.h>

#include "../imported/headers/bytes.h"
#include "../imported/headers/hmem.h"
#include "../imported/headers/typeless.h"
#include "../imported/headers/hash-table.h"
#include "../imported/headers/array.h"

void side_by_side(unsigned char *bytes, obj object){
    printf("\n");
    obj to_compare = read_bytes_to_obj(bytes, NULL);
    printf("Compared side by side:\n");
    char *obj_a = get_raw_obj(object);
    char *obj_b = get_raw_obj(to_compare);
    printf("Obj A: %s & Obj B: %s\n", obj_a, obj_b);
    hfree(obj_a);
    hfree(obj_b);
    free_obj(to_compare);
    printf("\n");
}

int main(int argc, char *argv[]){
    size_t jic;
    obj str_obj = create_string_obj("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    unsigned char *byte_str = get_byte_obj(str_obj, &jic);
    print_bytes("string object", byte_str, jic);
    side_by_side(byte_str, str_obj);
    hfree(byte_str);
    free_obj(str_obj);

    obj int_obj = create_int_obj(42069);
    unsigned char *byte_int = get_byte_obj(int_obj, &jic);
    print_bytes("int object", byte_int, jic);
    side_by_side(byte_int, int_obj);
    hfree(byte_int);
    free_obj(int_obj);

    obj float_obj = create_decimal_obj(15.69); // Technically double
    unsigned char *byte_dec = get_byte_obj(float_obj, &jic);
    print_bytes("decimal object", byte_dec, jic);
    side_by_side(byte_dec, float_obj);
    hfree(byte_dec);
    free_obj(float_obj);

    obj array_obj = create_empty_array_obj();
    array *arr_addr = obj_get_array_addr(array_obj);
    array_append_pointer(arr_addr, create_int_obj(42069));
    array_append_pointer(arr_addr, create_decimal_obj(15.69));
    unsigned char *bytes_arr = get_byte_obj(array_obj, &jic);
    print_bytes("array object", bytes_arr, jic);
    side_by_side(bytes_arr, array_obj);
    hfree(bytes_arr);
    free_obj(array_obj);

    obj dict_obj = create_empty_dict_obj();
    dict *dict_addr = obj_get_dict_addr(dict_obj);
    dict d = *dict_addr;
    dict_add_pointer(dict_addr, "abc", create_int_obj(42069));
    dict_add_pointer(dict_addr, "def", create_decimal_obj(15.69));
    dict_add_pointer(dict_addr, "ghi", create_string_obj("OKCOMPUTER"));
    unsigned char *bytes_dict = get_byte_obj(dict_obj, &jic);
    print_bytes("dict object", bytes_dict, jic);
    side_by_side(bytes_dict, dict_obj);
    hfree(bytes_dict);
    free_obj(dict_obj);

    return 0;
}
