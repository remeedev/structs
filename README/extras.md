# Extras

Contains all other modules created that were not mentioned in any of the files.

## Messages

Proy module: **messages**

As defined in `messages.h`

```c
void mem_alloc_error(int, char *);
void value_should_be(int value, char *arg_name, char* should_be);
void print_error(char *error_text);
```

clearly just quick prints.

## Handled mem

Proy module: **handled-mem**

As defined in `handled_mem.h`:

```c
void *int_to_ptr(int a);
void *float_to_ptr(float a);
void *double_to_ptr(double a);
```

Does quick allocation for variables that wouldn't require an alloc by default, allows for structures to *always* be able to free **all** elements.

## Bytes

Proy module: **bytes**

As defined in `bytes.h`:

```c
unsigned char *int2bytes(int);
unsigned char *float2bytes(int);
void print_bytes(char *byte_name, void *byte_addr, size_t size);
```

Converts objects to bytes, and has a function to print bytes given an address and a size, `byte_name` can be `NULL` as it is just a printed name and has no impact on the regular functioning of bytes.c

## Strs

Proy module: **strs**

As defined in `strs.h`:

```c
int str_len(char *str);
int str_equal(char *a, char *b);
int str2int(char *str);
char *int2str(int num);
float str2float(char *str);
char *float2str(float num);
int is_int(char *);
int is_float(char *);
char *dupstr(char *);
```

Some duplicated functions from `<strings.h>`, generally useful functions for manipulation of strings.

**Be careful!** `str_len(char *)` returns the calculated length of a string, if the object happens to be of type `string` from `ezstr` then you can just do `get_string_size` which consists of one read, complexity of O(1).
