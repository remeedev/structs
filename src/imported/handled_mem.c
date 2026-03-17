#include <stdlib.h>
#include "headers/messages.h"

void *int_to_ptr(int a){
    int *out = (int *)malloc(sizeof(int));
    if (out == NULL){
        mem_alloc_error(sizeof(int), "int");
    }
    *out = a;
    return out;
}

void *double_to_ptr(double a){
    double *out = (double *)malloc(sizeof(double));
    if (out == NULL){
        mem_alloc_error(sizeof(double), "int");
    }
    *out = a;
    return out;
}

void *float_to_ptr(float a){
    float *out = (float *)malloc(sizeof(float));
    if (out == NULL){
        mem_alloc_error(sizeof(float), "int");
    }
    *out = a;
    return out;
}
