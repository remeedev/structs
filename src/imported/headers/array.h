#ifndef arrays
#define arrays

#define array void **

array create_array();

void array_append_pointer(array *arr, void *pointer);
void array_append_int(array*, int);
void array_append_float(array*, float);
void array_append_double(array*, double);
void array_pop(array *, int);

int array_contains(array arr, void *elem);

int get_array_size(array);
void array_set_size(array *arr, int new_size);
void free_array(array);

#endif
