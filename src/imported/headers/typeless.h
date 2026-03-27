#include <stdlib.h>

#ifndef typeless
#define typeless

#define obj void *

char *get_raw_obj(obj object);
char *get_plain_obj(obj object);
unsigned char *get_byte_obj(obj object, size_t* size);

void set_object_content(obj, void *);

obj create_string_obj(char *content);
obj create_int_obj(int content);
obj create_decimal_obj(double content);
obj create_empty_array_obj();
obj create_empty_dict_obj();

void * get_dict_from_obj(obj);
void *obj_get_dict_addr(obj);

void **get_array_from_obj(obj array_obj);
void *obj_get_array_addr(obj array_obj);

void free_contained_array(obj array_obj);

void free_obj(obj object);
void free_simple_obj(obj object);
void free_array_obj(obj array_obj);
void free_dict_obj(obj dict_obj);

obj read_bytes_to_obj(unsigned char *bytes, int *pos);
obj read_to_obj(char *str);
obj read_from_file(char *file_name);

#endif
