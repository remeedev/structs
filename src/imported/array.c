#include "headers/messages.h"
#include "headers/handled_mem.h"
#include <stdlib.h>
#include <stdio.h>

#define array void **

array create_array(){
    int size = 0;
    int alloc_size = sizeof(int) + sizeof(void *) * size;
    void *out = malloc(alloc_size);
    if (out == NULL){
        mem_alloc_error(alloc_size, "array");
        return NULL;
    }
    *(int *)out = size;
    array tmp_array = (array)((int *)out + 1);
    for (int i = 0; i < size; i++) tmp_array[i] = NULL;

    return (array)((int *)out + 1);
}

int get_array_size(array arr){
    if (arr == NULL) return 0;
    return *((int *)arr - 1);
}

void array_append_pointer(array *arr, void *pointer);

void array_set_size(array *arr, int new_size){
    int prev_size = get_array_size(*arr);
    if (new_size == prev_size) return;
    if (new_size < prev_size){
        array out_arr = create_array();
        for (int i = new_size; i < prev_size; i++) free((*arr)[i]);
        for (int i = 0; i < new_size; i++) array_append_pointer(&out_arr, (*arr)[i]);
        free((void *)((int *)(*arr) - 1));
        *arr = out_arr;
        return;   
    }
    int bytes_size = sizeof(int) + sizeof(void *) * new_size;
    void *og_array_blob = (void *)((int *)(*arr) - 1);
    void *out = realloc(og_array_blob, bytes_size);
    if (out == NULL){
        mem_alloc_error(bytes_size, "realloced array");
        return;
    }
    array out_arr = (array)((int *)out + 1);
    for (int i = prev_size; i < new_size; i++) out_arr[i] = NULL;
    *arr =out_arr;
    *((int *)(*arr) - 1) = new_size;
}

int real_index(array arr, int index){
    int arr_size = get_array_size(arr);
    if (abs(index) > arr_size){
        printf("Index %d out of bounds, list size = %d\n", index, arr_size);
        return -1;
    }

    int out = 0;
    if (index < 0){
        return arr_size + index;
    } else if (index > 0){
        return index%arr_size;
    }
    return index%arr_size;
}

void swap_above(array *arr, int index){
    void *tmp = (*arr)[index];
    (*arr)[index] = (*arr)[index + 1];
    (*arr)[index + 1] = tmp;
}

void array_pop(array *arr, int index){
    int i;
    int array_size = get_array_size(*arr);
    if (( i = real_index(*arr, index) ) == -1) return;
    if (i != array_size - 1) while ( i < array_size - 1 ) swap_above(arr, i++);
    array_set_size(arr, array_size - 1);
}

void array_append_pointer(array *arr, void *pointer){
    int out_pos = get_array_size(*arr);
    array_set_size(arr, out_pos + 1);
    (*arr)[out_pos] = pointer;
}

void array_append_int(array *arr, int num){
    array_append_pointer(arr, int_to_ptr(num));
}

void array_append_float(array *arr, float num){
   array_append_pointer(arr, float_to_ptr(num));
}

void array_append_double(array* arr, double num){
    array_append_pointer(arr, double_to_ptr(num));
}

void free_array(array arr){
    int arr_size = get_array_size(arr);
    for (int i = 0; i < arr_size; i++) if(arr[i]) free(arr[i]);
    free((void *)((int *)arr - 1));
}

int array_contains(array arr, void *elem){
    int arr_size = get_array_size(arr);
    for (int i = 0; i < arr_size; i++) if (arr[i] == elem) return 1;
    return 0;
}
