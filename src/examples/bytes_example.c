#include "../imported/headers/bytes.h"

int main(){
    byte_seq *new_bytes = create_empty_byte_sequence();
    unsigned char data[] = {'t', 'e', 's', 't', 's'};
    concat_to_byte_seq(new_bytes, data, 5);
    print_byte_seq(NULL, new_bytes);
    unsigned char more_data[] = {' ', 'p', 'l', 'a', 'c', 'e', 's'};
    concat_to_byte_seq(new_bytes, more_data, 7);
    print_byte_seq(NULL, new_bytes);
    free_byte_seq(new_bytes);
    return 0;
}
