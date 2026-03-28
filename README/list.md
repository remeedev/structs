# List

Proy module: **list**

Like an array, except it doesn't look at all like an array.

It's just a linked list.

## Usage

After importing `list.h` into your code you can:

To create a brand new list you must run the following function:

```c
list new_list = create_list();
```

To append to a new list you can run one of the following functions, defined in `list.h`:

```c
void list_append_int(list l, int num);
void list_append_float(list l, float num);
void list_append_double(list l, double num);
void list_append_pointer(list l, void *content);
```

All, except `list_append_pointer` will `malloc` a new space in memory for each element that is created.


All elements inside of a list are nodes, and to traverse these nodes you can either go from the back:

```c
node last_node = get_last_node(list);
```

Or the front:

```c
node first_node = get_first_node(list);
```

Either way you must keep a pointer to the previous address as nodes don't keep previous and next pointers, instead they keep them combined by an XOR operation (^). The following is an example for iterating a linked list called `breeze`.

```c
node first_node = get_first_node(breeze);
void *prev = NULL;
while (first_node != NULL){
    // Do something with first_node...

    // Go to next node:
    void *tmp = first_node;
    first_node = node_xor(first_node, prev);
    prev = tmp;
}
```

To get the content of a node you must call `get_node_content(node)`

which will return a `void *`, which then must be cast to the proper type for it to have the proper treatment.

Additionally, lists have a list size, to get it run the following function:

```c
int list_size = get_list_size(list_name);
```

Finally a list must be freed calling the function:

```c
free_list(list_name);
```
