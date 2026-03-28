# Dict

Proy module: **dict**

A dictionary is a useful tool whose element indices are determined by a string key.

## Usage

After importing `hash-table.h` into your code you can create a new dictionary running the following:

```c
dict dict_name = create_dict(int);
```

to add elements to the dictionary there are 4 possible functions inside the `hash-table.h` file:

```c
void dict_add_pointer(dict *d, char *key, void *ptr);
void dict_add_float(dict *d, char *key, float value);
void dict_add_double(dict *d, char *key, double value);
void dict_add_int(dict *d, char *key, int value);
```

All of them, except for dict_add_pointer, malloc a space of memory for the pointer that stores the value, there is also `dict_put_pointer_no_free(dict *, char *, void *)` which will, as its name indicates, put a pointer in a position and, even if that element had a previous value, it will not free the value, this allows for freeing certain elements before calling `free_dict(dict)`

To get an element inside of the dict one must do the following:

`dict_get(dict, char *)` passing the dictionary and key searched, that will return a `void *` that must be cast to the correct type for operations of that type to become valid.

`dict_get_addr(dict, char *)` return the address where the element is stored, this allows for certain manipulation of elements.

After working with the dictionary one must free it using the
`free_dict(dict)` function, passing in the originally generated dictionary.

## Example files

- [dict_example.c](https://github.com/remeedev/structs/blob/main/src/examples/dict_example.c)
