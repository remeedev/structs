#include "ezstr.h"
#include <stdlib.h>

#ifndef files
#define files

string read_file(char *file_name);
unsigned char *read_file_bytes(char *file_name, size_t *size);
void write_to_file(char *file_name, char *content);
void write_bytes_to_file(char *file_name, unsigned char *bytes, size_t size);

int is_file_bytes(char *file_name);

#endif
