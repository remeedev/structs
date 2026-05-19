#include <stdio.h>

#include "../imported/headers/typeless.h"
#include "../imported/headers/hmem.h"

void print_obj_raw(obj a){
    if (!a){
        printf("Is an empty object!\n");
        return;
    }
    char *obj_raw = get_plain_obj(a);
    if (obj_raw){
        printf("%s\n", obj_raw);
        hfree(obj_raw);
    }
}

int main(){
    obj test_obj = read_to_obj("{\"test\":[1, 2, 3], \"big_num\":71231546487546, \"depth\":{\"hi\":[{\"wow\":15}]}}");
    print_obj_raw(test_obj);
    obj list = obj_index(test_obj, ".test");
    print_obj_raw(list);
    obj big_num = obj_index(test_obj, ".big_num");
    print_obj_raw(big_num);
    obj two = obj_index(test_obj, ".test[1]");
    print_obj_raw(two);
    obj depth = obj_index(test_obj, ".depth.hi[0].wow");
    print_obj_raw(depth);
    free_obj(test_obj);
    return 0;
}
