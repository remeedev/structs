/*
 * OPENING COMMENTS FOR CODE:
 * This program uses trash disposal also known as
 * hmem.h, this was a program created by me (remeedev),
 * when tested it will show a LOT of memory allocated,
 * even though it is the simplest path to take when
 * dealing with mallocs, if you feel capable of handling
 * ALL of the frees then you can check out typeless_no_mem_example.c, 
 * it demonstrates same function as here but it doesn't use trash
 * disposal, but it does use some quirks to free every element,
 * UPSIDE:
 *  Not using trash disposal uses WAY LESS memory.
 * DOWNSIDE:
 *  Not using trash disposal uses _quirks_
 * Check typeless_no_mem to see memory comparison between both files,
 * a bit shocking but then again, yeah makes sense.
 * 
 *
 * Be careful with you memory
 * - Remee
 */

#include <stdio.h>
#include <stdlib.h>

#include "../imported/headers/typeless.h"
#include "../imported/headers/hmem.h"
#include "../imported/headers/array.h"
#include "../imported/headers/hash-table.h"
#include "../imported/headers/strs.h"

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
    array_append_pointer(obj_get_array_addr(array_obj), create_int_obj(19));
    array_append_pointer(obj_get_array_addr(array_obj), create_decimal_obj(-420.69));
    array_append_pointer(obj_get_array_addr(array_obj), create_string_obj("--, please"));

    obj nested_array = create_empty_array_obj();
    array_append_pointer(obj_get_array_addr(nested_array), create_int_obj(420));
    array_append_pointer(obj_get_array_addr(nested_array), create_string_obj("Testing, please"));

    array_append_pointer(obj_get_array_addr(array_obj), nested_array);

    printf("Getting raw list...\n");
    printf("Raw List: %s\n", get_raw_obj(array_obj));
    /*
     * typeless_no_mem handles memory directly,
     * has example of a list that is created and
     * then cleared, shows empty in list, the following
     * is an example, with trash disposal of emptied list
    */

    for (int i = 0; i < get_array_size(get_array_from_obj(array_obj)); i++){
        get_array_from_obj(array_obj)[i] = NULL; // emptying every elem
    }

    printf("Raw List: %s\n", get_raw_obj(array_obj));

    free_contained_array(array_obj); // Array objects require free
    free_contained_array(nested_array); // free_array tries to free all elements, must use basic free

    obj dict_obj = create_empty_dict_obj();
    dict_add_pointer(obj_get_dict_addr(dict_obj), "test", create_int_obj(15));
    dict_add_pointer(obj_get_dict_addr(dict_obj), "weird", create_string_obj("dumb"));
    dict_add_pointer(obj_get_dict_addr(dict_obj), "list", create_empty_array_obj());

    obj dict_arr_obj = dict_get(get_dict_from_obj(dict_obj), "list");
    array_append_pointer(obj_get_array_addr(dict_arr_obj), create_string_obj("random string, literally"));
    array_append_pointer(obj_get_array_addr(dict_arr_obj), create_int_obj(69));

    printf("Raw dict: %s\n", get_raw_obj(dict_obj));

    // Remember to free ALL arrays
    free(get_array_mallocd_ptr(get_dict_array(get_dict_from_obj(dict_obj)))); // Frees the array
    free_contained_array(dict_arr_obj);

    end_memory_registering();

    return 0;
}
