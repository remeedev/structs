#ifndef lists
#define lists

#define list void *
#define node void **

list create_list();
int get_list_size(list l);
void free_list(list l);

void list_append_int(list l, int num);
void list_append_float(list l, float num);
void list_append_double(list l, double num);
void list_append_pointer(list l, void *content);

node get_first_node(list l);
node get_last_node(list l);

node get_node_at(list l, int pos);
void list_pop(list l, int pos);

void *get_node_content(node n);

void *node_xor(node n, void *ptr);

#endif
