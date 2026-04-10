#include "headers/bytes.h"
#include "headers/ezstr.h"
#include "headers/hmem.h"
#include "headers/array.h"
#include "headers/hash-table.h"
#include "headers/messages.h"
#include "headers/strs.h"
#include "headers/handled_mem.h"
#include "headers/files.h"
#include <stdio.h>

// Objs will be stored like: type, content

#define obj void *

#define STRING_TYPE 1
#define INT_TYPE 2
#define DOUBLE_TYPE 3
#define LIST_TYPE 4
#define DICT_TYPE 5
#define LIST_TERMINATOR 6
#define DICT_TERMINATOR 7

void free_obj(obj);

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

unsigned char *get_bytes_dict(obj dict_obj, size_t *size);
unsigned char *get_bytes_array(obj array_obj, size_t *size);

unsigned char *get_byte_obj(obj object, size_t* size){
    size_t jic;
    if (size == NULL) size = &jic;
    *size = 0; // default val
    unsigned char *out;
    unsigned char *tmp;
    switch (get_type(object)){
        case STRING_TYPE: ;
            *size = get_string_size(*(string *)object) + 2;
            out = hmalloc(*size);
            if (out == NULL){
                mem_alloc_error(*size, "string byte obj");
                *size = -1;
                return NULL;
            }
            out[0] = STRING_TYPE;
            out[get_string_size(*(string *)object) + 1] = '\0';
            for (int i = 0; i < get_string_size(*(string *)object); i++){
                out[i + 1] = (unsigned char)((*(string *)object)[i]);
            }
            return out;
            break;
        case INT_TYPE: ;
            *size = sizeof(char) + sizeof(int);
            out = hmalloc(*size);
            if (out == NULL){
                mem_alloc_error(*size, "int byte obj");
                *size = -1;
                return NULL;
            }
            out[0] = INT_TYPE;
            tmp = int2bytes(**(int **)object);
            for (int i = 0; i < sizeof(int); i++){
                out[i + 1] = tmp[i];
            }
            hfree(tmp);
            return out;
            break;
        case DOUBLE_TYPE: ;
            *size = sizeof(char) + sizeof(double);
            out = hmalloc(*size);
            if (out == NULL){
                mem_alloc_error(*size, "double byte obj");
                *size=-1;
                return NULL;
            }
            out[0] = DOUBLE_TYPE;
            tmp = float2bytes(**(double **)object);
            for (int i = 0; i < sizeof(double); i++){
                out[i + 1] = tmp[i];
            }
            hfree(tmp);
            return out;
            break;
        case DICT_TYPE: ;
            return get_bytes_dict(object, size);
            break;
        case LIST_TYPE: ;
            return get_bytes_array(object, size);
            break;
        default: ;
            print_error("Tried reading object of unknown type!");
            break;
    }
    return NULL;
}

obj create_string_obj(char *content){
    obj out = create_empty_object(STRING_TYPE);
    string contnt = create_empty_string();
    concat_to_str(&contnt, content);
    set_object_content(out, contnt);
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
        if (str_len(get_key(elems[i])) == 0){
            continue;
        }
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

unsigned char *get_bytes_dict(obj dict_obj, size_t *size){
    dict d = get_dict_from_obj(dict_obj);
    array elems = get_key_values(d);
    int len = 1; // type
    for (int i = 0; i < get_array_size(elems); i++){
        len += str_len(get_key(elems[i])) + 2; // 1%s\0:
        size_t tmp_size;
        unsigned char *tmp = get_byte_obj(get_value(elems[i]), &tmp_size);
        len += tmp_size; // obj
        hfree(tmp);
    }
    unsigned char *out = (unsigned char *)hmalloc(len + 1);
    if (out == NULL){
        mem_alloc_error(len, "byte dictionary");
        return NULL;
    }
    *size = len + 1;
    out[0] = DICT_TYPE;
    int pos = 1;
    int i = 0;
    while (pos < len){
        hash_elem elem = elems[i];
        out[pos++] = STRING_TYPE;
        char *key = get_key(elem);
        int key_len = str_len(key);
        for (int j = 0; j < key_len + 1; j++){
            out[pos++] = key[j];
        }
        size_t val_len;
        unsigned char *tmp = get_byte_obj(get_value(elem), &val_len);
        for (int j = 0; j < val_len; j++){
            out[pos++] = tmp[j];
        }
        hfree(tmp);
        i++;
    }
    out[pos] = DICT_TERMINATOR;
    free((int *)elems - 1);
    return out;
}

unsigned char *get_bytes_array(obj array_obj, size_t *size){
    array interpreted = get_array_from_obj(array_obj);
    int len = 1; // type
    for (int i = 0; i < get_array_size(interpreted); i++){
        size_t tmp = 1;
        unsigned char *to_free = get_byte_obj(interpreted[i], &tmp);
        if (tmp == 0) continue;
        len += tmp;
        hfree(to_free);
    }
    unsigned char *out = (unsigned char *)hmalloc(len + 1);
    if (out == NULL){
        mem_alloc_error(len + 1, "raw array");
        return NULL;
    }
    *size = len + 1;
    out[0] = LIST_TYPE;
    int pos = 1;
    int i = 0;
    while (pos < len - 1){
        size_t tmp = 1;
        unsigned char *to_free = get_byte_obj(interpreted[i++], &tmp);
        if (tmp == 0) continue;   

        for (int j = 0; j < tmp; j++){
            out[pos++] = to_free[j];
        }
        hfree(to_free);
    }
    out[pos] = LIST_TERMINATOR;
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
        if (arr[i]) free_obj(arr[i]);
        arr[i] = NULL;
    }
    free_array(arr);
    hfree((char *)array_obj - 1);
}

void free_dict_obj(obj dict_obj){
    array kv_pairs = get_key_values(get_dict_from_obj(dict_obj));
    for (int i = 0; i < get_array_size(kv_pairs); i++){
        void *val = get_value(kv_pairs[i]);
        free_obj(val);
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

void free_simple_obj(obj object){
    free(*(void **)object);
    free((char *)object - 1);
}

void free_obj(obj object){
    switch(get_type(object)){
        case STRING_TYPE: ;
            free_string(*(string *)object);
            free((char *)object - 1);
            break;
        case INT_TYPE: ;
            free_simple_obj(object);
            return;
        case DOUBLE_TYPE: ;
            free_simple_obj(object);
            return;
        case DICT_TYPE: ;
            free_dict_obj(object);
            return;
        case LIST_TYPE: ;
            free_array_obj(object);
            return;
    }
}

obj create_empty_dict_obj(){
    obj out = create_empty_object(DICT_TYPE);
    set_object_content(out, create_dict(11));
    return out;
}

int get_to_next_obj(char *a, int i){
    while (a[i] != '\0' && (a[i] == ' ' || a[i] == '\n' || a[i] == ',' || a[i] == ':')) i++;
    return i;
}

int try_read_obj_char(string *out, char *str, int *pos, char a){
    if (str[*pos] == a){
        concat_char_to_str(out, a);
        char b;
        switch(a){
            case '"': ;
                b = a;
                break;
            case '[': ;
                b = ']';
                break;
            case '{': ;
                b = '}';
                break;
            default:
                b = '\0';
        }
        (*pos)++;
        while (str[*pos] != '\0' && str[*pos] != b){
            concat_char_to_str(out, str[*pos]);
            (*pos)++;
        }
        concat_char_to_str(out, b);
        (*pos)++;
        return 1;
    }
    return 0;
}

string read_next_obj(char *str, int* pos){
    string out = create_empty_string();

    if (try_read_obj_char(&out, str, pos, '"') ||\
            try_read_obj_char(&out, str, pos, '[') ||\
            try_read_obj_char(&out, str, pos, '{')){
        return out;
    } 
    while ((str[*pos] >= '0' && str[*pos] <= '9') || str[*pos] == '-' || str[*pos] == '.') {
        concat_char_to_str(&out, str[*pos]);
        (*pos)++;
    }

    if (get_string_size(out) == 0){
        free_string(out);
        return NULL;
    }

    return out;
}

obj read_to_obj(char *str){
    if (str == NULL) return NULL;
    int strlen = str_len(str);
    int pos = get_to_next_obj(str, 0);

    if (str[pos] == '"'){
        string read_obj = read_next_obj(str, &pos);
        read_obj[get_string_size(read_obj) - 1] = '\0';
        obj out = create_string_obj(read_obj + 1);
        free_string(read_obj);
        return out;
    }else if (str[pos] == '['){
        pos++;
        pos = get_to_next_obj(str, pos);
        obj out = create_empty_array_obj();
        array *addr = obj_get_array_addr(out);
        array arr = *addr;
        while (str[pos] != '\0' && str[pos] != ']'){
            string tmp_obj = read_next_obj(str, &pos);
            if (tmp_obj) {
                array_append_pointer(addr, read_to_obj(tmp_obj));
                free_string(tmp_obj);
            }
            pos = get_to_next_obj(str, pos);
        }
        return out;
    }else if (str[pos] == '{'){
        pos++;
        pos = get_to_next_obj(str, pos);
        obj out = create_empty_dict_obj();
        dict *addr = obj_get_dict_addr(out);
        dict d = *addr;
        while (str[pos] != '\0' && str[pos] != '}'){
            // Read key
            string key_obj = read_next_obj(str, &pos);
            pos = get_to_next_obj(str, pos);
            string value_obj = read_next_obj(str, &pos);
            obj parsed_value = read_to_obj(value_obj);
            obj parsed_key = read_to_obj(key_obj);
            char *raw_key = get_raw_obj(parsed_key);
            dict_add_pointer(addr, raw_key, parsed_value);
            free_obj(parsed_key);
            hfree(raw_key);
            free_string(key_obj);
            free_string(value_obj);
            pos = get_to_next_obj(str, pos);
        }
        return out;
    }else{
        string full_obj = read_next_obj(str, &pos);
        obj out = NULL;
        if (is_int(full_obj)){
            out = create_int_obj(str2int(full_obj));
        }else if (is_float(full_obj)){
            out = create_decimal_obj(str2float(full_obj));
        }
        free_string(full_obj);
        return out;
    }
    return NULL;
}
obj read_bytes_to_obj(unsigned char *bytes, int *pos){
    if (bytes == NULL) return NULL;
    int jic = 0;
    if (pos == NULL) pos = &jic;
    char type = (char)bytes[(*pos)++];
    switch(type){
        case STRING_TYPE: ;
            obj out = create_string_obj("");
            string* tmp = (string *)out;
            while ((unsigned char)(bytes[*pos]) != '\0') concat_char_to_str(tmp, (char)bytes[(*pos)++]);
            (*pos)++;
            return out;
        case INT_TYPE: ;
            int val;
            for (int i = 0; i < sizeof(int); i++) ((unsigned char *)&val)[i] = bytes[(*pos)++];
            return create_int_obj(val);
        case DOUBLE_TYPE: ;
            double dec;
            for (int i = 0; i < sizeof(double); i++) ((unsigned char *)&dec)[i] = bytes[(*pos)++];
            return create_decimal_obj(dec);
        case LIST_TYPE: ;
            obj list_out = create_empty_array_obj();
            array *arr_addr = obj_get_array_addr(list_out);
            while (bytes[*pos] != LIST_TERMINATOR){
                array_append_pointer(arr_addr, read_bytes_to_obj(bytes, pos));
            }
            return list_out;
        case DICT_TYPE: ;
            obj dict_out = create_empty_dict_obj();
            dict *dict_addr = obj_get_dict_addr(dict_out);
            while (bytes[*pos] != DICT_TERMINATOR){
                obj key_obj = read_bytes_to_obj(bytes, pos);
                obj value_obj = read_bytes_to_obj(bytes, pos);
                dict_add_pointer(dict_addr, *(char **)key_obj, value_obj);
                free_obj(key_obj);
            }
            return dict_out;
        default: ;
            print_error("Tried to read object of unknown type!");
            break;
    }
    return NULL;
}

obj read_from_plain_file(char *file_name){
    string file_content = read_file(file_name);
    obj out = read_to_obj(file_content);
    if (file_content) free_string(file_content);
    return out;
}

obj read_from_bytes_file(char *file_name){
    size_t size;
    unsigned char *file_content = read_file_bytes(file_name, &size);
    if (size < 0){
        print_error("There has been an error reading the file!\n");
        return NULL;
    }
    obj out = read_bytes_to_obj(file_content, NULL);
    free(file_content);
    return out;
}

obj read_from_file(char *file_name){
    if (is_file_bytes(file_name)){
        return read_from_bytes_file(file_name);
    }else{
        return read_from_plain_file(file_name);
    }
}

void write_obj_to_file(int as_bytes, obj elem, char *file_name){
    if (as_bytes){
        size_t size;
        unsigned char *bytes = get_byte_obj(elem, &size);
        write_bytes_to_file(file_name, bytes, size);
        hfree(bytes);
    }else{
        char *raw = get_plain_obj(elem);
        write_to_file(file_name, raw);
        hfree(raw);
    }
}
