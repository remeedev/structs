#include <stdlib.h>
#include "headers/array.h"
#include "headers/messages.h"

typedef struct alloced_mem{
    void *ptr;
    size_t size;
    struct alloced_mem* next;
}alloced_mem;

void *(*malloc_func)(size_t) = malloc;
void *(*realloc_func)(void *, size_t) = realloc;
void (*free_func)(void *) = free;

array alloced = NULL;

void start_memory_registering(){
    alloced = create_array();
}

void set_memory_functions(void *(*m)(size_t), void *(*r)(void *, size_t), void (*f)(void *)){
    malloc_func = m;
    realloc_func = r;
    free_func = f;
}

void *hmalloc(size_t size){
    void *new_alloc_ptr = malloc_func(size);
    if (new_alloc_ptr == NULL) return NULL;
    if (!alloced) return new_alloc_ptr;
    alloced_mem *mem_reg = malloc_func(sizeof(alloced_mem));
    if (mem_reg == NULL){
        mem_alloc_error(sizeof(alloced_mem), "allocated memory registry");
        free_func(new_alloc_ptr);
        return NULL;
    }
    mem_reg->ptr = new_alloc_ptr;
    mem_reg->size = size;
    mem_reg->next = NULL;
    array_append_pointer(&alloced, mem_reg);
    return new_alloc_ptr;
}

alloced_mem *get_mem_at(int index){
    if (alloced == NULL || index < 0 || index >= get_array_size(alloced)) return NULL;
    alloced_mem *out = alloced[index];
    return out;
}

alloced_mem *search_mem(void *ptr){
    for (int i = 0; i < get_array_size(alloced); i++){
        if (ptr == get_mem_at(i)->ptr) return get_mem_at(i);
    }
    return NULL;
}

void *hrealloc(void *ptr, size_t size){
    alloced_mem* tmp = search_mem(ptr);
    void *to_realloc = ptr;
    if (tmp == NULL && alloced != NULL){
        print_error("Tried to reallocate non allocated memory!\n");
        return NULL;
    }else if (tmp != NULL && tmp->size > size){
        print_error("Tried downsizing pointer!\n");
        return NULL;
    }
    void *tmp_mem = realloc_func(ptr, size);
    if (tmp_mem == NULL){
        mem_alloc_error(size, "reallocated object");
        return NULL;
    }
    if (tmp){
        tmp->ptr = tmp_mem;
        tmp->size = size;
    }
    return tmp_mem;
}

void hfree(void *ptr){
    alloced_mem *tmp = search_mem(ptr);
    void *to_free = ptr;
    if (tmp == NULL && alloced != NULL){
        print_error("Tried to free memory which was never allocated!\n");
        return;
    }
    free_func(to_free);
    if (alloced && tmp){
        int pos = 0;
        while (get_mem_at(pos)->ptr != ptr) pos++;
        array_pop(&alloced, pos);
    }
}

void free_all_tracked(){
    int prev_size = get_array_size(alloced);
    for (int i = 0; i < prev_size; i++){
        free_func(get_mem_at(0)->ptr);
        array_pop(&alloced, 0);
    }
}

int get_currently_malloced_size(){
    int out = 0;
    int prev_size = get_array_size(alloced);
    for (int i = 0; i < prev_size; i++){
        out += get_mem_at(i)->size;
    }
    return out;
}

void end_memory_registering(){
    if (!alloced) return;
    free_all_tracked();
    free_array(alloced);
}
