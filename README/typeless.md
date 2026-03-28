# Typeless

I should've made another repo for this, but I didn't

## What is it ?

It is one of the few files which don't contain actual structures, but this one is a bit greater because it allows for elements (of any type) to be stored in one unified type. Clearly this implementation takes more space (`sizeof(int) < sizeof(obj_which_contains_int)`) than regular objects would, it allows for obj dumping (whether it be into bytes or into characters) and for memory writing.

Tl;dr

If you wanna store structures of multiple types and save them to files, this is the module for you.

## Usage

After importing `typeless.h` into your program there are a couple of functions at our disposal.

### Creation of objects

To create an object there are the following functions, defined in `typeless.h`:

```c
obj create_string_obj(char *content);
obj create_int_obj(int content);
obj create_decimal_obj(double content);
obj create_empty_array_obj();
obj create_empty_dict_obj();
```

The functions that contain `empty` inside them by default are already filled and are already operable, the other two will appear, as their name indicates, empty.

To start working on an array object `array.h` must be included into the file as the regular array and an array stored in an `obj` type are the same. The following is an example of working with an array, taken from `typeless_no_mem_example.c` in the `examples` folder.

```c
obj array_obj = create_empty_array_obj();
array_append_pointer(obj_get_array_addr(array_obj), create_int_obj(19));
array_append_pointer(obj_get_array_addr(array_obj), create_decimal_obj(-420.69));
array_append_pointer(obj_get_array_addr(array_obj), create_string_obj("--, please"));
```

To start working on a dict object `hash-table.h` must be included into the file as the regular dict is the same dict stored in an `obj` type. The following is an example of working with a dict, taken from `typeless_no_mem_example.c` in the `examples` folder.

```c
obj dict_obj = create_empty_dict_obj();
dict_add_pointer(obj_get_dict_addr(dict_obj), "test", create_int_obj(15));
dict_add_pointer(obj_get_dict_addr(dict_obj), "weird", create_string_obj("dumb"));
```

If you would like further knowledge on nesting arrays/dicts into each other you can check out the example inside `typeless_no_mem_example.c`.

### Printing objects

To convert an object to a printable string (`char *`) you must run the following function:

```c
char *out = get_raw_obj(obj); // replace obj for your object name, in out the printable string will be stored.
```

To convert an object to a byte sequence (`unsigned char *`) you must run the following function:

```c
size_t size;
unsigned char *out = get_byte_obj(obj, &size); // Writes byte sequence size to the variable pointed to by `&size`
```

### Writing to a file

In case you don't really want the hassle of handling the memory of the object as a sequence, whether it be of `char`s or `unsigned char`s, you can write your object to a file using the following function:

```c
write_obj_to_file(0, obj, file_name); // Setting the 0 to 1 will store the obj as bytes.
```

That function will store into `file_name` the content of `obj` as bytes/plaintext depending on what the first integer values is.

### Reading from a file

To read an object from a file there are two functions, depending on the file type:

```c
read_from_plain_file(char *file_name); // Reads from a plaintext file
read_from_bytes_file(char *file_name); // Reads from a byte file
```

There are also functions which read the sequences without having to open a file:

```c
read_bytes_to_obj(unsigned char* bytes, int *pos); // Reads bytes from pos, returns an obj read from the bytes.
read_to_obj(char *str); // Reads str, returns the object read from the string.
```

For simpler living conditions the following function was created:

```c
read_from_file(char *file_name);
```

`read_from_file` automatically determines file type and reads file accoringly.

### Freeing an object

`typeless.h` contains various free functions, for this readme I will only show one:

```c
free_obj(obj); // Will free any obj
```

That is because this function is the universal for every other function.
