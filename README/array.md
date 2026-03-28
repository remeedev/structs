# Array

Proy module: **array**

The array is a non linked list whose element addresses are one after the other.

e.g. arr[0] is the first element, the second is arr[1].

## Usage

To create an array first include the `array.h` file, then:

```c
array new_array = create_array();
```

There you have a blank array, appending to an array is possible, inside `array.h` there are 4 types of appends.

```c
void array_append_pointer(array *arr, void *pointer);
void array_append_int(array*, int);
void array_append_float(array*, float);
void array_append_double(array*, double);
```

Running all functions, except `array_append_pointer` will create a brand new pointer to be freed when `free_array` is called.

To get array size:

```c
get_array_size(new_array);
```

Array also contains a function called:

`array_contains(array, void *)`

That function will determine if a specific pointer is stored inside of the array.

To get the value of an element stored in the array just do:

`array[i]` being `array` the array that you created and `i` being the position accessed, take into account that for any i the type of array[i] is `void *`, therefore it must be cast to another type before being operated on.

When an array is done being used you must call:

`free_array(new_array)`, replacing `new_array` with the name of the array you created initially!

## Example files

- [array_example.c](https://github.com/remeedev/structs/blob/main/src/examples/array_example.c)
