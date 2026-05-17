#include "../imported/headers/typeless.h"
#include "../imported/headers/bytes.h"
#include "../imported/headers/hmem.h"

#include <stdio.h>

int main(){
    unsigned char test[] = {'t', 'e', 's', 't'};
    obj byte_obj = create_byte_seq_obj(test, 4);
    print_byte_seq(NULL, obj_get_byte_seq_addr(byte_obj));
    size_t size;
    unsigned char *byte_byte_obj = get_byte_obj(byte_obj, &size);
    if (size > 0) {
        print_bytes(NULL, byte_byte_obj, size);
        hfree(byte_byte_obj);
    }
    printf("The following is an error caused by trying to turn bytes into plain text:\n");
    char *raw = get_raw_obj(byte_obj);
    printf("result: %s\n", raw);
    printf("Will get parsed as a string when read!\n");
    hfree(raw);
    free_obj(byte_obj);
}
