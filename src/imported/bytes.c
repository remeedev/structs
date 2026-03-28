#include <stdio.h>

#include "./headers/hmem.h"
#include "./headers/messages.h"

unsigned char * int2bytes(int a){
    unsigned char *out = hmalloc(sizeof(int));
    if (out == NULL){
        mem_alloc_error(sizeof(int), "int as bytes");
        return NULL;
    }
    for (int i = 0; i < sizeof(int); i++){
        out[i] = ((unsigned char *)&a)[i];
    }
    return out;
}

unsigned char * float2bytes(double a){
    unsigned char *out = hmalloc(sizeof(double));
    if (out == NULL){
        mem_alloc_error(sizeof(double), "float as bytes");
        return NULL;
    }
    for (int i = 0; i < sizeof(double); i++){
        out[i] = ((unsigned char *)&a)[i];
    }
    return out;
}

void print_bytes(char *byte_name, void *byte_addr, size_t size){
    if (size < 0) return;
    printf("Bytes contained in ");
    if (byte_name){
        printf("%s:\n", byte_name);
    }else{
        printf("%p:\n", byte_addr);
    }
    for (int i = 0; i < 31; i++) printf("=");
    printf("\n");
    for (int i = 0; i < size; i++){
        printf("%-3u ", ((unsigned char *)byte_addr)[i]);
        if ((i + 1) % 8 == 0)printf("\n");
    }
    printf("\n");
    for (int i = 0; i < 31; i++) printf("=");
    printf("\n");
}
