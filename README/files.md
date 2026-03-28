# Files

Proy module: **files**

Its a file that contains utilities on files.

## Usage

The following are the functions defined on `files.h`:

```c
string read_file(char *file_name);
unsigned char *read_file_bytes(char *file_name, size_t *size);
void write_to_file(char *file_name, char *content);
void write_bytes_to_file(char *file_name, unsigned char *bytes, size_t size);

int is_file_bytes(char *file_name);
```

`read_file` and `read_file_bytes` both read a file, only thing that changes is the type of content to be received, `char *` and `unsigned char *` respectively, `read_file_bytes` takes in an extra argument that is a pointer to a size variable, this allows the function to also return the size of the bytes that were read.

`write_to_file` and `write_bytes_to_file` both take in a file name and content and just write the content to the file in `file_name`, `write_bytes_to_file` has an extra argument to know the size of bytes being written.

Finally: `is_file_bytes` returns whether a file has any byte elements (non-printable characters) or if it is purely plaintext. When true the file indicated by `file_name` is considered to be a byte file.

## Example files

- [files_example.c](https://github.com/remeedev/structs/blob/main/src/examples/files_example.c)
