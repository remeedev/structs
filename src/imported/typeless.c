#include "headers/typeless.h"
#include "headers/hmem.h"
#include "headers/array.h"
#include "headers/hash-table.h"
#include "headers/messages.h"
#include "headers/strs.h"
#include "headers/handled_mem.h"
#include <stdio.h>

// Objs will be stored like: type, content

#define obj void *

#define STRING_TYPE 1
#define INT_TYPE 2
#define DOUBLE_TYPE 3
#define LIST_TYPE 4
#define DICT_TYPE 5

obj create_empty_object(char type){
    obj out = (obj)hmalloc(sizeof(char) + sizeof(void *));
    if (out == NULL){
        mem_alloc_error(sizeof(void *) + 1, "typeless object");
        return out;
    }
    *(char *)out = type;
    return (obj)((char *)out + 1);
}

void set_object_content(obj object, void *content){
    *(void **)object = content;
}

char *get_raw_array(obj array_obj);
char *get_raw_dict(obj dict_obj);

char get_type(obj object){
    return *((char *)object - 1);
}

char *get_raw_obj(obj object){
    if (object == NULL) return "";
    switch(get_type(object)){
        case STRING_TYPE: ;
            return dupstr(*(char **)object);
            break;
        case INT_TYPE: ;
            return int2str(**(int **)object);
            break;
        case DOUBLE_TYPE: ;
            return float2str(**(double **)object);
            break;
        case LIST_TYPE: ;
            return get_raw_array(object);
            break;
        case DICT_TYPE: ;
            return get_raw_dict(object);
            break;
        default: ;
            print_error("Tried to read object of unknown type!");
            break;
    }
    return "";
}

char *get_plain_obj(obj object){
    if (object == NULL) return ""; // I thought raw and plain would differ, I thought wrong
    switch(get_type(object)){
        case STRING_TYPE: ;
            char *out = (char *)hmalloc(str_len(*(char **)object) + 3);
            sprintf(out, "\"%s\"", *(char **)object);
            return out;
            break;
        case INT_TYPE: ;
            return get_raw_obj(object);
            break;
        case DOUBLE_TYPE: ;
            return get_raw_obj(object);
            break;
        case LIST_TYPE: ;
            return get_raw_obj(object);
            break;
        case DICT_TYPE: ;
            return get_raw_obj(object);
            break;
        default: ;
            print_error("Tried to read object of unknown type!");
            break;
    }
    return "";
}

obj create_string_obj(char *content){
    obj out = create_empty_object(STRING_TYPE);
    set_object_content(out, dupstr(content));
    return out;
}

obj create_int_obj(int content){
    obj out = create_empty_object(INT_TYPE);
    set_object_content(out, int_to_ptr(content));
    return out;
}

obj create_decimal_obj(double content){
    obj out = create_empty_object(DOUBLE_TYPE);
    set_object_content(out, double_to_ptr(content));
    return out;
}

array get_array_from_obj(obj array_obj){
    return *(array *)array_obj;
}

void *obj_get_array_addr(obj array_obj){
    return (array *)array_obj;
}

dict get_dict_from_obj(obj dict_obj){
    return *(dict *)dict_obj;
}

void *obj_get_dict_addr(obj dict_obj){
    return (dict *)dict_obj;
}

char *get_raw_array(obj array_obj){
    array interpreted = get_array_from_obj(array_obj);
    int len = 2; // Opening and closing bracket
    for (int i = 0; i < get_array_size(interpreted); i++){
        char *to_free = get_plain_obj(interpreted[i]);
        if (str_len(to_free) == 0) continue;
        len += str_len(to_free);
        if (i < get_array_size(interpreted) - 1){
            len += 2;
        }
        hfree(to_free);
    }
    char *out = (char *)hmalloc(len + 1);
    if (out == NULL){
        mem_alloc_error(len + 1, "raw array");
        return NULL;
    }
    out[0] = '[';
    out[len-1] = ']';
    out[len] = '\0';
    int pos = 1;
    int i = 0;
    while (pos < len - 1){
        char *to_free = get_plain_obj(interpreted[i++]);
        if (str_len(to_free) == 0) continue;   

        int ll = str_len(to_free);
        for (int j = 0; j < ll; j++){
            out[pos++] = to_free[j];
        }
        if (pos < len - 1){
            out[pos++] = ',';
            out[pos++] = ' ';
        }

        hfree(to_free);
    }
    return out;
}

char *get_raw_dict(obj dict_obj){
    dict d = get_dict_from_obj(dict_obj);
    array elems = get_key_values(d);
    int len = 2; // Opening and closing bracket
    for (int i = 0; i < get_array_size(elems); i++){
        len += str_len(get_key(elems[i])) + 3; // "%s":
        char *tmp = get_plain_obj(get_value(elems[i]));
        len += str_len(tmp); // obj
        if (i < get_array_size(elems) - 1){
            len += 2; // ', '
        }
        hfree(tmp);
    }
    char *out = (char *)hmalloc(len + 1);
    if (out == NULL){
        mem_alloc_error(len + 1, "raw dictionary");
        return NULL;
    }
    out[0] = '{';
    out[len] = '\0';
    out[len - 1] = '}';
    int pos = 1;
    int i = 0;
    while (pos < len - 1){
        hash_elem elem = elems[i];
        out[pos++] = '"';
        char *key = get_key(elem);
        int key_len = str_len(key);
        for (int j = 0; j < key_len; j++){
            out[pos++] = key[j];
        }
        out[pos++] = '"';
        out[pos++] = ':';
        char *tmp = get_plain_obj(get_value(elem));
        int val_len = str_len(tmp);
        for (int j = 0; j < val_len; j++){
            out[pos++] = tmp[j];
        }
        hfree(tmp);
        if (i < get_array_size(elems) - 1){
            out[pos++] = ',';
            out[pos++] = ' ';
        }
        i++;
    }
    free((int *)elems - 1);
    return out;
}

obj create_empty_array_obj(){
    obj out = create_empty_object(LIST_TYPE);
    array to_write = create_array();
    set_object_content(out, to_write);
    return out;
}

void free_regular_obj(obj object){
    hfree(*(void **)object);
    hfree((char *)object - 1);
}

void free_dict_obj(obj dict_obj);

void free_array_obj(obj array_obj){
    array *addr = obj_get_array_addr(array_obj);
    array arr = *addr;
    for (int i = 0; i < get_array_size(arr); i++){
        if (get_type(arr[i]) == LIST_TYPE){
            free_array_obj(arr[i]);
            goto clear;
        }else if (get_type(arr[i]) == DICT_TYPE){
            free_dict_obj(arr[i]);
            goto clear;
        }
        free_regular_obj(arr[i]);
clear:
        arr[i] = NULL;
    }
    free_array(arr);
    hfree((char *)array_obj - 1);
}

void free_dict_obj(obj dict_obj){
    array kv_pairs = get_key_values(get_dict_from_obj(dict_obj));
    for (int i = 0; i < get_array_size(kv_pairs); i++){
        void *val = get_value(kv_pairs[i]);
        if (get_type(val) == LIST_TYPE){
            free_array_obj(val);
            goto clear;
        }else if (get_type(val) == DICT_TYPE){
            free_dict_obj(val);
            goto clear;
        }
        free_regular_obj(val);
clear:
        dict_put_pointer_no_free(obj_get_dict_addr(dict_obj), get_key(kv_pairs[i]), NULL);
        kv_pairs[i] = NULL;
    }
    free_array(kv_pairs);
    free_dict(get_dict_from_obj(dict_obj));
    hfree((char *)dict_obj - 1);
}

void free_contained_array(obj array_obj){
    array arr = get_array_from_obj(array_obj);
    free(get_array_mallocd_ptr(arr)); // Arrays are unhandled mem
}

obj create_empty_dict_obj(){
    obj out = create_empty_object(DICT_TYPE);
    set_object_content(out, create_dict(11));
    return out;
}
