#include <stdlib.h>

#ifndef byte_converters
#define byte_converters

typedef unsigned char * byte_seq;

int byte_seq_size(byte_seq *seq);
byte_seq *create_empty_byte_sequence();
void free_byte_seq(byte_seq* seq);
void concat_to_byte_seq(byte_seq *seq, unsigned char * bytes, int byte_len);
void concat_char_to_byte_seq(byte_seq *seq, unsigned char a);

unsigned char *int2bytes(int);
unsigned char *float2bytes(int);
void print_bytes(char *byte_name, void *byte_addr, size_t size);
void print_byte_seq(char *byte_name, byte_seq* seq);

int is_bytes(unsigned char *bytes, size_t byte_size);

#endif
