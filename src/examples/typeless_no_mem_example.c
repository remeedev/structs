// This example uses no trash handling for memory, it is not recommended to do so
// Nevertheless it is added for other travelers to consider the same as me,
// it is not worth it to not use the trash disposal
//
// Compared to trash disposal usage:
//
// typeless_no_mem ->51 allocs and frees, of course
// typeless ->870 allocs and frees, clearly one is memory friendly and the other one isn't

#include <stdio.h>
#include <stdlib.h>

#include "../imported/headers/hmem.h"
#include "../imported/headers/typeless.h"
#include "../imported/headers/array.h"

int main(int argc, char *argv[]){
    obj str_obj = create_string_obj("Hello, world!");
    char *raw_obj;
    char *plain_obj;
    printf("Raw obj: %s\n", raw_obj = get_raw_obj(str_obj));
    printf("Plain obj: %s\n", plain_obj = get_plain_obj(str_obj));
    hfree(*(char **)str_obj); // Weird free, first the item
    hfree((char *)str_obj - 1); // Then the obj itself
    hfree(raw_obj);
    hfree(plain_obj);

    obj int_obj = create_int_obj(19);
    printf("Raw obj: %s == Plain obj: %s\n", raw_obj = get_raw_obj(int_obj), plain_obj = get_plain_obj(int_obj));
    free(*(void **)int_obj);
    free((char *)int_obj - 1);
    hfree(raw_obj);
    hfree(plain_obj);

    obj float_obj = create_decimal_obj(-10.5);
    printf("Raw obj: %s == Plain obj: %s\n", raw_obj = get_raw_obj(float_obj), plain_obj = get_plain_obj(float_obj));
    free(*(void **)float_obj);
    free((char *)float_obj - 1);
    hfree(raw_obj);
    hfree(plain_obj);

    obj array_obj = create_empty_array_obj();
    array_append_pointer(get_array_addr(array_obj), create_int_obj(19));
    array_append_pointer(get_array_addr(array_obj), create_decimal_obj(-420.69));
    array_append_pointer(get_array_addr(array_obj), create_string_obj("Nigga, please"));

    obj nested_array = create_empty_array_obj();
    array_append_pointer(get_array_addr(nested_array), create_int_obj(420));
    array_append_pointer(get_array_addr(nested_array), create_string_obj("Testing, please"));

    array_append_pointer(get_array_addr(array_obj), nested_array);

    printf("Getting raw list...\n");
    raw_obj = get_raw_obj(array_obj);
    printf("Raw List: %s\n", raw_obj);
    free(raw_obj);

    array arr1 = get_array_from_obj(nested_array);
    for (int i = 0; i < get_array_size(arr1); i++){ // First removing the list that is nested
        hfree(*(void **)arr1[i]); // Free elem actually saved
        hfree((char *)arr1[i] - 1); // Free obj container
        arr1[i] = NULL;
    }
    free((char *)nested_array - 1); // Free the actual elem
    free_array(arr1); // Finally the elem
    arr1 = get_array_from_obj(array_obj);
    arr1[3] = NULL; // Set it to null, allows for free_array to be called
    for (int i = 0; i < get_array_size(arr1); i++){
        if ((void *)arr1[i] == NULL) continue;
        hfree(*(void **)arr1[i]); // Same shit
        hfree((char *)arr1[i] - 1);
        arr1[i] = NULL;
    }
    raw_obj = get_raw_obj(array_obj);
    printf("Raw list: %s\n", raw_obj); // Proves empty array set to -> []
    free(raw_obj);
    free((char *)array_obj - 1);
    free_array(arr1);

    return 0;
}
