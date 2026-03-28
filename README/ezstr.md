# ezstr

Proy module: **ezstr**

Ezstr is basically a `char *` that doesn't need to call `strlen` every time you want to figure its length out.

## Usage

After importing the `ezstr.h` to create a string you must run the following function:

```c
string new_str = create_empty_string();
```

That will create a totally empty string, then you can add characters (`char`) or character sequences (`char *`).

To add characters the following two functions exist:

```c
concat_to_str(&str, "text"); // Adds "text" to the end of str
concat_char_to_str(&str, '!'); // Adds '!' to the end of str
```

This implementation of strings allow for

```c
get_string_size(string); // Returns size of string
```

to have a time complexity of O(1).

After you are done with a string you must run:

```c
free_string(string);
```

To free the string object that was created.

## Example files

- [ezstr_example.c](https://github.com/remeedev/structs/blob/main/src/examples/ezstr_example.c)
