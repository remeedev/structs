#include <stdlib.h>
#include "headers/array.h"
#include "headers/handled_mem.h"
#include "headers/messages.h"

#define pq void **

pq create_pq(int max_heap){
    pq out = (pq)malloc(sizeof(int) + sizeof(array *));
    if (out == NULL){
        mem_alloc_error(sizeof(int) + sizeof(array *), "priority queue");
        return NULL;
    }
    *(int *)out = max_heap;
    array heap = create_array();
    *(array *)((int *)out + 1) = heap;
    return (pq)((int *)out + 1);
}

int get_pq_size(pq a){
    return get_array_size(*(array *)a);
}

int is_max_heap(pq a){
    return *((int *)a - 1);
}

void **new_elem(int priority, void *content){
    void **out = (void **)malloc(sizeof(int) + sizeof(void *));
    if (out == NULL){
        mem_alloc_error(sizeof(int) + sizeof(void *), "priority queue element");
        return NULL;
    }
    *(int *)out = priority;
    *(void **)((int *)out + 1) = content;
    return out;
}

int get_elem_priority(void **elem){
    return *(int *)elem;
}

void *get_elem_content(void **elem){
    return *(void **)((int *)elem + 1);
}

void swim(pq a, int pos){
    if (pos == 0) return;
    int max_heap = is_max_heap(a);
    array ll = *(array *)a;
    int parent_pos = (pos - 1)>>1;
    while (pos > 0 && \
            ((max_heap && get_elem_priority(ll[pos]) > get_elem_priority(ll[parent_pos])) || \
             (!max_heap && get_elem_priority(ll[pos]) < get_elem_priority(ll[parent_pos])))){
        void *tmp = ll[parent_pos];
        ll[parent_pos] = ll[pos];
        ll[pos] = tmp;
        pos = parent_pos;
        parent_pos = (pos - 1)>>1;
    }
}

void sink(pq a, int pos){
    if (pos == get_array_size(*(array *)a) - 1) return;
    int max_heap = is_max_heap(a);
    array ll = *(array *)a;
    int left_child = (pos<<1) + 1;
    int right_child = (pos<<1) + 2;
    int size = get_array_size(*(array *)a);
    int best_index = pos;
    if (left_child < size && \
            ((max_heap && get_elem_priority(ll[best_index]) < get_elem_priority(ll[left_child])) || \
             (!max_heap && get_elem_priority(ll[best_index]) > get_elem_priority(ll[left_child])))){
        best_index = left_child;
    }
    if (right_child < size && \
            ((max_heap && get_elem_priority(ll[best_index]) < get_elem_priority(ll[right_child])) || \
             (!max_heap && get_elem_priority(ll[best_index]) > get_elem_priority(ll[right_child])))){
        best_index = right_child;
    }
    if (pos != best_index){
        void *tmp = ll[best_index];
        ll[best_index] = ll[pos];
        ll[pos] = tmp;
        sink(a, best_index);
    }
}

void pq_push(pq a, int priority, void *content){
    void **elem = new_elem(priority, content);
    array_append_pointer((array *)a, elem);
    swim(a, get_array_size(*(array *)a) - 1);
}

void pq_push_int(pq a, int priority, int content){
    pq_push(a, priority, int_to_ptr(content));
}

void pq_push_float(pq a, int priority, float content){
    pq_push(a, priority, float_to_ptr(content));
}

void pq_push_double(pq a, int priority, double content){
    pq_push(a, priority, double_to_ptr(content));
}

void* pq_pop(pq a){
    void *content = get_elem_content((*(array *)a)[0]);
    array_pop((array *)a, 0);
    sink(a, 0);
    return content;
}

void free_pq(pq a){
    array arr = *(array *)a;
    for (int i = 0; i < get_array_size(*(array *)a); i++){
        if (get_elem_content(arr[i]))free(get_elem_content(arr[i]));
        if (arr[i])free(arr[i]);
        arr[i] = NULL;
    }
    free_array(arr);
    free((void *)((int *)a-1));
}
