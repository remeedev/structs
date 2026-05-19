#include "headers/hmem.h"
#include "headers/messages.h"
#include "headers/strs.h"

typedef char * string;

string create_empty_string(){
    void *out = hmalloc(sizeof(int) + 1);
    *(int *)out = 0;
    *(char *)((int *)out + 1) = '\0';
    return (char *)((int *)out + 1);
}

int get_string_size(string str){
    return *((int *)str - 1);
}

void concat_to_str(string *str, char *text){
    int og_size = get_string_size(*str);
    int new_size = og_size + str_len(text);
    
    void *tmp = hrealloc((int *)(*str) - 1, sizeof(int) + new_size + 1);
    if (tmp == NULL){
        mem_alloc_error(sizeof(int) + new_size + 1, "string reallocation");
        return;
    }
    *str = (string)((int *)tmp + 1);
    *((int *)(*str) - 1) = new_size;
    int i = 0;
    while (og_size < new_size) (*str)[og_size++] = text[i++];
    (*str)[og_size] = '\0';
}

void concat_char_to_str(string *str, char a){
    char to_add[2] = {a, '\0'};
    concat_to_str(str, to_add);
}

void free_string(string str){
    hfree((int *)str - 1);
}

char *strip_multiline_str(char *str){
    int i = 0;
    int just_read_line = 0;
    string tmp_out = create_empty_string();
    while (str[i] != 0){
        if (just_read_line && !(str[i] == ' ' || str[i] == '\n' || str[i] == '\t')) just_read_line = 0;
        if (!just_read_line) concat_char_to_str(&tmp_out, str[i]);
        if (str[i] == '\n') just_read_line = 1;
        i++;
    }
    char *out = dupstr(tmp_out);
    free_string(tmp_out);
    return out;
}
