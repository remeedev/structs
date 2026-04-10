#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "headers/strs.h"
#include "headers/array.h"
#include "headers/handled_mem.h"
#include "headers/hmem.h"

#define PRIME 333667
#define A 0.55

#define dict void *
#define hash_elem void *

dict create_dict(int capacity){
    void *out = (void *)hmalloc(2*sizeof(int) + sizeof(array *));
    *(int *)out = capacity;
    *((int *)out + 1) = 0;
    array empty_array = create_array();
    array_set_size(&empty_array, capacity);
    *(array *)((int *)out + 2) = empty_array;
    return out;
}

hash_elem generate_hash_elem(char *key, void *value){
    hash_elem out = (hash_elem)hmalloc(2*sizeof(void *));
    *(char **)out = key;
    *((void **)out + 1) = value;
    return out;
}

char *get_key(hash_elem a){
    return *(char **)a;
}

void *get_value(hash_elem a){
    return *((void **)a + 1);
}

array get_dict_array(dict d){
    array out = *(array *)((int *)d + 2);
    return out;
}

void free_hash_elem_content(hash_elem a){
    if (get_key(a)) free(get_key(a));
    if (get_value(a)) free(get_value(a));
    *(char **)a = NULL;
    *((void **)a + 1) = NULL;
}

int get_dict_capacity(dict d){
    return *(int *)d;
}

int get_dict_size(dict d){
    return *((int *)d + 1);
}

int hash_value(dict d, char *key){
    int aa = 0;
    for (int i = 0; key[i] != '\0'; i++){
        aa+=key[i]*(i + 1);
    }
    return ((int)floor(PRIME * fmod(aa*A, 1)))%get_dict_capacity(d);
}

array get_key_values(dict d){
    array out = create_array();
    array d_arr = get_dict_array(d);
    for (int i = 0; i < get_array_size(d_arr); i++){
        if (d_arr[i] == NULL || get_key(d_arr[i]) == NULL) continue;
        array_append_pointer(&out, d_arr[i]);
    }
    return out;
}

void free_after_expand(dict d){
    array kv_pairs = get_key_values(d);
    for (int i = 0; i < get_array_size(kv_pairs); i++){
        hfree(get_key(kv_pairs[i]));
        hfree(kv_pairs[i]);
        kv_pairs[i] = NULL;
    }
    free_array(kv_pairs);
    for (int i = 0; i < get_array_size(get_dict_array(d)); i++) get_dict_array(d)[i] = NULL;
    free_array(get_dict_array(d));
    hfree(d);
}

// Puts pointer in existing key, doesnt free previous value
void dict_put_pointer_no_free(dict *d, char *key, void *ptr){
    int pos = hash_value(*d, key);
    array hash_ar = get_dict_array(*d);
    while (hash_ar[pos] != NULL && !str_equal(get_key(hash_ar[pos]), key)) {
        pos++;
        if (pos >= get_dict_capacity(*d)) pos = 0;
    }
    if (hash_ar[pos] != NULL && str_equal(get_key(hash_ar[pos]), key)){
        *((void **)hash_ar[pos] + 1) = ptr;
    }
}

void dict_add_pointer(dict *d, char *key, void *ptr){
    int pos = hash_value(*d, key);
    array hash_ar = get_dict_array(*d);
    while (hash_ar[pos] != NULL && !str_equal(get_key(hash_ar[pos]), key)) {
        pos++;
        if (pos >= get_dict_capacity(*d)) pos = 0;
    }
    if (hash_ar[pos] != NULL && str_equal(get_key(hash_ar[pos]), key)){
        hfree(*((void **)hash_ar[pos] + 1));
        *((void **)hash_ar[pos] + 1) = ptr;
        goto capacity_check;
    }else if(hash_ar[pos] != NULL && get_key(hash_ar[pos]) == NULL) {
        *((void **)hash_ar[pos] + 1) = ptr;
        *((char **)hash_ar[pos]) = dupstr(key);
        *((int *)(*d) + 1) += 1;
        goto capacity_check;
    }
    hash_elem to_add = generate_hash_elem(dupstr(key), ptr);
    hash_ar[pos] = to_add;
    *((int *)(*d) + 1) += 1;
capacity_check:
    if (get_dict_size(*d) > get_dict_capacity(*d)>>1){
        dict tmp_dict = create_dict(get_dict_capacity(*d)<<1);
        array kv_pairs = get_key_values(*d);
        for (int i = 0; i < get_array_size(kv_pairs); i++){
            dict_add_pointer(&tmp_dict, get_key(kv_pairs[i]), get_value(kv_pairs[i]));
            kv_pairs[i] = NULL;
        }
        free_array(kv_pairs);
        free_after_expand(*d);
        *d = tmp_dict;
    }
}

void dict_add_int(dict *d, char *key, int value){
    dict_add_pointer(d, key, int_to_ptr(value));
}

void dict_add_float(dict *d, char *key, float value){
    dict_add_pointer(d, key, float_to_ptr(value));
}

void dict_add_double(dict *d, char *key, double value){
    dict_add_pointer(d, key, double_to_ptr(value));
}

void free_dict(dict d){
    array kv_pairs = get_key_values(d);
    for (int i = 0; i < get_array_size(kv_pairs); i++) {
        free_hash_elem_content(kv_pairs[i]);
    }
    array tmp_arr = get_dict_array(d);
    // all values have must be cleared to prevent double free
    for (int i = 0; i < get_array_size(tmp_arr); i++){
        if (array_contains(kv_pairs, tmp_arr[i])) tmp_arr[i] = NULL;
    }
    free_array(kv_pairs);
    free_array(tmp_arr);
    hfree(d);
}

void *dict_get(dict d, char *key){
    int pos = hash_value(d, key);
    array hash_ar = get_dict_array(d);
    while (hash_ar[pos] != NULL && !str_equal(get_key(hash_ar[pos]), key)) {
        pos++;
        if (pos >= get_dict_capacity(d)) pos = 0;
    }
    if (hash_ar[pos] == NULL) return NULL;
    return get_value(hash_ar[pos]);
}

void **dict_get_addr(dict d, char *key){
    int pos = hash_value(d, key);
    array hash_ar = get_dict_array(d);
    while (hash_ar[pos] != NULL && !str_equal(get_key(hash_ar[pos]), key)) {
        pos++;
        if (pos >= get_dict_capacity(d)) pos = 0;
    }
    if (hash_ar[pos] == NULL) return NULL;
    return ((void **)hash_ar[pos] + 1);
}

void dict_remove(dict d, char *key){
    int pos = hash_value(d, key);
    array hash_ar = get_dict_array(d);
    while (hash_ar[pos] != NULL && !str_equal(get_key(hash_ar[pos]), key)) {
        pos++;
        if (pos >= get_dict_capacity(d)) pos = 0;
    }
    if (hash_ar[pos] == NULL) return;
    free_hash_elem_content(hash_ar[pos]);
    *((int *)d + 1) -= 1;
}
