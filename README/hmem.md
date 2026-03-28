# Hmem

Proy module: **hmem**

Hmem is like memory management, except it does a lot of work for you, so you don't do as much work.

## Usage

After `#include`ing the `hmem.h` file there are several ways to start.

You can:

1. Set memory functions to be used, that way every call to the other functions get redirected to a memory function. This can be done by writing the following code.

```c
set_memory_functions(&malloc, &realloc, &free);
```

As this is a minimal example this line of code would do nothing, if the memory functions were different then it would override regular protocol.

2. Start memory registering, which will reduce the need of `free`s everywhere, nevertheless, the use of memory registering is memory exhaustive and it will display way higher memory usage than it wold regularly. To start memory registering just run the following function:

```c
start_memory_registering();
```

Using memory registering, even though reduces the needs of `free`s still needs a free for itself, to free all allocated and registered memory blocks just run:

```c
end_memory_registering();
```

3. You can just start using memory as you would using `malloc`, `realloc` and `free` except with `hmalloc`, `hrealloc` and `hfree` respectively, if memory registering is off functions will still work it just won't bother keeping track.

***

There is also an aditional function called:

```c
get_currently_malloced_size();
```

It requires memory registering to be turned on and it returns the total size of memory that has been allocated.

## Example files

- [hmem_example.c](https://github.com/remeedev/structs/blob/main/src/examples/hmem_example.c)
