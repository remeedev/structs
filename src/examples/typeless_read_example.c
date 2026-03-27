#include <stdio.h>

#include "../imported/headers/hmem.h"
#include "../imported/headers/typeless.h"

int main (int argc, char *argv[]){
    char *test_obj_str = "     \"Test string\"";
    obj parsed_str = read_to_obj(test_obj_str);

    char *unparsed_str = get_raw_obj(parsed_str);
    printf("%s\n", unparsed_str);
    hfree(unparsed_str);
    free_obj(parsed_str);

    char *test_obj_list = "    [\"Test string\", 1, 2, 3, \"four\", {\"Hello\":\"Goodbye\"}]";
    obj parsed_list = read_to_obj(test_obj_list);

    char *unparsed_list = get_raw_obj(parsed_list);
    printf("%s\n", unparsed_list);
    hfree(unparsed_list);
    free_obj(parsed_list);

    char *test_obj_dict = "   {\"key\":[\"value\",  \"fifteen\"] }   ";
    obj parsed_dict = read_to_obj(test_obj_dict);

    char *unparsed_dict = get_raw_obj(parsed_dict);
    printf("%s\n", unparsed_dict);
    hfree(unparsed_dict);
    free_obj(parsed_dict);

    // read_from_file(char *file_name) returns the same as reading the file and then passing read obj to read_to_obj
    obj example_read = read_from_file("./src/examples/typeless_test.json");
    char *unparsed_read = get_raw_obj(example_read);
    printf("%s\n", unparsed_read);
    hfree(unparsed_read);

    free_obj(example_read);

    unsigned char tmp[] = {1, 'H', 'e', 'l', 'l', 'o', ' ', 'e', 'l', 'f', 's', 'z', '\0'};
    obj example_bytes = read_bytes_to_obj(tmp, NULL);
    char *byte_read = get_raw_obj(example_bytes);
    printf("%s\n", byte_read);
    hfree(byte_read);
    free_obj(example_bytes);

    return 0;
}
