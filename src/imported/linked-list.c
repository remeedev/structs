#include <stdint.h>
#include <stdlib.h>
#include "headers/messages.h"
#include "headers/handled_mem.h"

#define node void **
#define list void *

list create_list(){
    void *out = (void *)malloc(sizeof(int) + 2*sizeof(node *));
    if (out == NULL){
        mem_alloc_error(sizeof(int) + 2*sizeof(node *), "linked list");
        return NULL;
    }
    *((int *) out) = 0;
    *(node *)((int *) out + 1) = NULL;
    *((node *)((int *) out + 1) + 1) = NULL;
    return (list)((int *)out + 1);
}

node get_first_node(list l){
    return *((node *)l);
}

node get_last_node(list l){
    return *((node *)l + 1);
}

int get_list_size(list l){
    return *((int *)l - 1);
}

node create_node(void *next, void *prev, void *content){
    node out = malloc(2*sizeof(void *));
    if (out == NULL){
        mem_alloc_error(2*sizeof(void *), "linked list node");
        return NULL;
    }
    out[0] = (void *)((uintptr_t)next ^ (uintptr_t)prev);
    out[1] = content;
    return out;
}

void *get_node_content(node n){
    return n[1];
}

void *node_xor(node n, void *ptr){
    if (n == NULL) return NULL;
    return (void *)((uintptr_t)n[0] ^ (uintptr_t)ptr);
}

void list_append_pointer(list l, void *content){
    node new_node = create_node(NULL, get_last_node(l), content);
    if (get_first_node(l) == NULL) *(node *)l = new_node;
    node last_node = get_last_node(l);
    if (last_node) last_node[0] = (void *)((uintptr_t)last_node[0] ^ (uintptr_t)new_node);
    *((node *)l + 1) = new_node;
    *((int *)l - 1) = get_list_size(l) + 1;
}

void list_append_int(list l, int num){
    list_append_pointer(l, int_to_ptr(num));
}

void list_append_float(list l, float num){
    list_append_pointer(l, float_to_ptr(num));
}

void list_append_double(list l, double num){
    list_append_pointer(l, double_to_ptr(num));
}

void free_node(node n){
    free(n[1]);
    free(n);
}

void free_list(list l){
    if (get_list_size(l) > 0){
        node first_node = get_first_node(l);
        void *prev = NULL;
        while (first_node != NULL){
            node tmp = first_node;

            first_node = node_xor(first_node, prev);
            prev = tmp;
            free_node(tmp);
        }
    }
    free((int *)l - 1);
}

node get_node_at(list l, int pos){
    if (pos < 0) pos = get_list_size(l) + pos;
    if (pos > get_list_size(l)){
        print_error("Index out of range! Must be bigger than 0 and less than list size!");
        return NULL;
    }
    node closest_entry = pos > (get_list_size(l)>>1) ? get_last_node(l) : get_first_node(l);
    void *prev = NULL;
    int curr_pos = closest_entry == get_first_node(l) ? 0 : get_list_size(l) - 1;
    while (curr_pos != pos){
        void *tmp = closest_entry;
        closest_entry = node_xor(closest_entry, prev);
        prev = tmp;
        if (curr_pos < pos){
            curr_pos++;
        }else{
            curr_pos--;
        }
    }
    return closest_entry;
}

void list_pop(list l, int pos){
    if (pos < 0) pos = get_list_size(l) + pos;
    if (pos > get_list_size(l)){
        print_error("Index out of range! Must be bigger than 0 and less than list size!");
        return;
    }
    node closest_entry = pos > (get_list_size(l)>>1) ? get_last_node(l) : get_first_node(l);
    int is_prev_saved = closest_entry == get_first_node(l);
    void *prev = NULL;
    int curr_pos = closest_entry == get_first_node(l) ? 0 : get_list_size(l) - 1;
    while (curr_pos != pos){
        void *tmp = closest_entry;
        closest_entry = node_xor(closest_entry, prev);
        prev = tmp;
        if (curr_pos < pos){
            curr_pos++;
        }else{
            curr_pos--;
        }
    }
    void *next = node_xor(closest_entry, prev);
    if (prev) ((node)prev)[0] = (void *)((uintptr_t)((node)prev)[0] ^ (uintptr_t) closest_entry);
    if (prev) ((node)prev)[0] = (void *)((uintptr_t)((node)prev)[0] ^ (uintptr_t) next);
    if (next) ((node)next)[0] = (void *)((uintptr_t)((node)next)[0] ^ (uintptr_t) closest_entry);
    if (next) ((node)next)[0] = (void *)((uintptr_t)((node)next)[0] ^ (uintptr_t) prev);
    *((int *)l - 1) = get_list_size(l) - 1;
    if (get_first_node(l) == closest_entry){
        *(node *)l = next;
    }
    if (get_last_node(l) == closest_entry){
        *((node *)l + 1) = next;
    }
    free_node(closest_entry);
}
