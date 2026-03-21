#include <stdlib.h>

#ifndef memory_memory
#define memory_memory

void start_memory_registering();
void set_memory_functions(void *(*m)(size_t), void *(*r)(void *, size_t), void (*f)(void *));
void *hmalloc(size_t size);
void *hrealloc(void *ptr, size_t size);
void hfree(void *ptr);
void free_all_tracked();
void end_memory_registering();
int get_currently_malloced_size();

#endif
