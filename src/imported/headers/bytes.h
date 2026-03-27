#include <stdlib.h>

#ifndef byte_converters
#define byte_converters

unsigned char *int2bytes(int);
unsigned char *float2bytes(int);
void print_bytes(char *byte_name, void *byte_addr, size_t size);

#endif
