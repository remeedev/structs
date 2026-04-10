#include <stdio.h>

#define RED "\033[31m"

#define END "\033[0m"

void mem_alloc_error(int bytes, char *name){
    char a = name[0];
    int n = a == 'a' || a=='e' || a=='i' || a=='o' || a=='u';
    printf("There has been an error allocating %d bytes for a%c %s\n", bytes, n?'n':' ', name);
}

void value_should_be(int value, char *arg_name, char* should_be){
    printf("%sValue %s, which is %d, should be %s%s\n", RED, arg_name, value, should_be, END);
}

void print_error(char *error_text){
    printf("%s%s%s\n", RED, error_text, END);
}
