#include "headers/messages.h"
#include "headers/hmem.h"

void *int_to_ptr(int a){
    int *out = (int *)hmalloc(sizeof(int));
    if (out == NULL){
        mem_alloc_error(sizeof(int), "int");
    }
    *out = a;
    return out;
}

void *double_to_ptr(double a){
    double *out = (double *)hmalloc(sizeof(double));
    if (out == NULL){
        mem_alloc_error(sizeof(double), "double");
    }
    *out = a;
    return out;
}

void *float_to_ptr(float a){
    float *out = (float *)hmalloc(sizeof(float));
    if (out == NULL){
        mem_alloc_error(sizeof(float), "float");
    }
    *out = a;
    return out;
}
