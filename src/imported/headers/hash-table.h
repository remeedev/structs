#ifndef hash_table
#define hash_table

#define dict void *
#define hash_elem void *

dict create_dict(int capacity);
void free_dict(dict d);

void dict_remove(dict d, char *key);

int get_dict_size(dict d);
void *dict_get(dict d, char *key);
void **dict_get_addr(dict d, char *key);

void dict_put_pointer_no_free(dict *d, char *key, void *ptr);

void dict_add_pointer(dict *d, char *key, void *ptr);
void dict_add_float(dict *d, char *key, float value);
void dict_add_double(dict *d, char *key, double value);
void dict_add_int(dict *d, char *key, int value);
 
#endif
