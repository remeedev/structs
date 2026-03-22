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

char *get_raw_obj(obj object){
    if (object == NULL) return "";
    switch(*((char *)object - 1)){
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
            break;
        default: ;
            print_error("Tried to read object of unknown type!");
            break;
    }
    return "";
}

char *get_plain_obj(obj object){
    if (object == NULL) return "";
    switch(*((char *)object - 1)){
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

void *get_array_addr(obj array_obj){
    return (array *)array_obj;
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

obj create_empty_array_obj(){
    obj out = create_empty_object(LIST_TYPE);
    array to_write = create_array();
    set_object_content(out, to_write);
    return out;
}

/*
    switch(type){
        case STRING_TYPE: ;
            break;
        case INT_TYPE: ;
            break;
        case DOUBLE_TYPE: ;
            break;
        case LIST_TYPE: ;
            break;
        case DICT_TYPE: ;
            break;
        default: ;
            print_error("Tried to create object of unknown type!");
            break;
    }
*/
