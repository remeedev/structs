#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "headers/messages.h"
#include "headers/hmem.h"

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
    char *out = (char *)hmalloc(s + 1);
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
    for (int i = str[0] == '-' ? 1 : 0; i < size; i++){
        out *= 10;
        out += (int)(str[i] - '0');
    }
    return out * (str[0] == '-' ? -1 : 1);
}

char *int2str(int num){
    int tmp = num;
    int len = num < 0 ? 1 : 0;
    while (tmp != 0){
        tmp /= 10;
        len++;
    }
    char *out = (char *)hmalloc(len + 1);
    for (int i = len - 1; i >= 0; i--){
        out[i] = '0' + (num % 10);
        num /= 10;
    }
    out[len] = '\0';
    return out;
}

float str2float(char *str){
    float out = 0;
    int decimal_pos = str_len(str) - 2;
    while (decimal_pos >= 0 && str[decimal_pos] != '.') decimal_pos--;
    if (decimal_pos < 0) decimal_pos = str_len(str) - 1;
    int size = 0;
    while (str[size] != '\0'){
        if (str[size] >= '0' && str[size] <= '9'){
            out*=10;
            out+=str[size] - '0';
        }
        size++;
    }
    out /= pow(10.0, str_len(str) - decimal_pos - 1);
    if (str[0] == '-') out *= -1;
    return out;
}

char *float2str(float num){
    float tmp = num;
    int len = num < 0 ? 1 : 0;
    tmp = tmp * (num < 0 ? -1 : 1);
    int decimal_pos = 0;
    while (tmp > 1.0) {
        tmp/=10;
        decimal_pos++;
    }
    while (fmod(tmp, 1.0) > 0){
        tmp*=10;
        len++;
    }
    while (tmp > 1.0) tmp /= 10;
    if (decimal_pos < len - 1) len++;
    if (num < 0) decimal_pos++;
    char *out = (char *)hmalloc(len + 1);
    for (int i = 0; i < len; i++){
        if (i == 0 && num < 0) {
            out[i] = '-';
            continue;
        }else if (i == decimal_pos){
            out[i] = '.';
            continue;
        }
        tmp *= 10;
        out[i] = '0' + ((int)tmp)%10;
    }
    out[len] = '\0';
    return out;
}
