#ifndef easy_string
#define easy_string

#define string char *

string create_empty_string();
int get_string_size(string str);
void concat_to_str(string *str, char *text);
void concat_char_to_str(string *str, char a);
void free_string(string str);

#endif
