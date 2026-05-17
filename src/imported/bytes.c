#include <stdio.h>

#include "./headers/hmem.h"
#include "./headers/messages.h"

typedef unsigned char * byte_seq;

byte_seq *create_empty_byte_sequence(){
    void* out = hmalloc(sizeof(int) + sizeof(void *));
    if (out == NULL){
        mem_alloc_error(sizeof(int) + sizeof(void *), "Byte sequence");
        print_error("Mallocing a byte sequence!");
        return NULL;
    }
    *(int *)(out) = 0;
    *(void **)((int *)out + 1) = NULL;
    return (byte_seq *)((int *)out + 1);
}

int byte_seq_size(byte_seq *seq){
    return *((int *)(void *)seq - 1);
}

void concat_to_byte_seq(byte_seq *seq, unsigned char * bytes, int byte_len){
    int new_size = (byte_seq_size(seq) + byte_len)*sizeof(unsigned char);
    void *og_blob = *(void **)seq;
    void *blob_out;
    if (og_blob){
        blob_out = hrealloc(og_blob, new_size);
    }else{
        blob_out = hmalloc(new_size);
    }
    if (blob_out == NULL){
        mem_alloc_error(new_size, "Reallocing/Mallocating byte sequence");
        return;
    }
    *(void **)seq = blob_out;
    unsigned char *blob = *(void **)seq;
    int curr_pos = byte_seq_size(seq);
    int i = 0;
    while (i < byte_len){
        blob[curr_pos++] = bytes[i++];
    }
    *((int *)seq - 1) = curr_pos;
}

void concat_char_to_byte_seq(byte_seq *seq, unsigned char a){
    unsigned char to_add[1] = {a};
    concat_to_byte_seq(seq, to_add, 1);
}

void free_byte_seq(byte_seq* seq){
    if (*(void **)seq) hfree(*(void **)seq);
    hfree((int *)seq - 1);
}

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
        if (((char *)byte_addr)[i] > 32){
            printf("%c ", ((char *)byte_addr)[i]);
        }else{
            printf("%-3u ", ((unsigned char *)byte_addr)[i]);
        }
        if ((i + 1) % 8 == 0)printf("\n");
    }
    printf("\n");
    for (int i = 0; i < 31; i++) printf("=");
    printf("\n");
}

void print_byte_seq(char *byte_name, byte_seq* seq){
    print_bytes(byte_name, *seq, byte_seq_size(seq));
}
