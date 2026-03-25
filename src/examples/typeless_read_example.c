#include <stdio.h>

#include "../imported/headers/hmem.h"
#include "../imported/headers/typeless.h"

int main (int argc, char *argv[]){
    char *test_obj_str = "     \"Test string\"";
    obj parsed_str = read_to_obj(test_obj_str);

    char *unparsed_str = get_raw_obj(parsed_str);
    printf("%s\n", unparsed_str);
    hfree(unparsed_str);
    free_simple_obj(parsed_str);

    char *test_obj_list = "    [\"Test string\", 1, 2, 3, \"four\", {\"Hello\":\"Goodbye\"}]";
    obj parsed_list = read_to_obj(test_obj_list);

    char *unparsed_list = get_raw_obj(parsed_list);
    printf("%s\n", unparsed_list);
    hfree(unparsed_list);
    free_array_obj(parsed_list);

    char *test_obj_dict = "   {\"key\":[\"value\",  \"fifteen\"] }   ";
    obj parsed_dict = read_to_obj(test_obj_dict);

    char *unparsed_dict = get_raw_obj(parsed_dict);
    printf("%s\n", unparsed_dict);
    hfree(unparsed_dict);
    free_dict_obj(parsed_dict);

    // read_from_file(char *file_name) returns the same as reading the file and then passing read obj to read_to_obj
    obj example_read = read_from_file("./src/examples/typeless_test.json");
    char *unparsed_read = get_raw_obj(example_read);
    printf("%s\n", unparsed_read);
    hfree(unparsed_read);

    free_dict_obj(example_read);

    return 0;
}
