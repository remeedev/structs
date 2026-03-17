#include <stdlib.h>
#include "headers/messages.h"

int str_len(char *str){
    int i = 0;
    while (str[i] != '\0') i++;
    return i;
}

int str_equal(char *a, char *b){
    if (a == 0 || b == 0) return 0;
    if (str_len(a) != str_len(b)) return 0;
    int x = str_len(a);
    for (int i = 0; i < x + 1; i++){
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

char *dupstr(char *a){
    int s = str_len(a);
    char *out = (char *)malloc(s + 1);
    if (out == NULL){
        mem_alloc_error(s + 1, "string");
        return NULL;
    }
    for (int i = 0; i < s + 1; i++){
        out[i] = a[i];
    }
    return out;
}

int str2int(char *str){
    int size = 0;
    while (str[size] != '\0') size++;
    int out = 0;
    for (int i = 0; i < size; i++){
        out *= 10;
        out += (int)(str[i] - '0');
    }
    return out;
}
