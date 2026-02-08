/**
 * vector
 * CS 341 - Fall 2023
 */
#include <string.h>
#include <assert.h>
#include "sstring.h"

struct sstring {
    char* str;
    size_t size;
};


int main(int argc, char *argv[]) {
    // TODO create some tests
    char* test_str = "123";
    char* addition_str = "456";
    sstring* sstr = cstr_to_sstring(test_str);
    sstring* sstr2 = cstr_to_sstring(addition_str);
    sstring_append(sstr, sstr2);
    

    sstring* sstr3 = cstr_to_sstring("1234567890");
    char* test_slice = sstring_slice(sstr3, 2, 5);
    assert(strcmp(test_slice, "345") == 0);


    sstring *replace_me = cstr_to_sstring("This is a {} day, {}!");
    sstring_substitute(replace_me, 18, "{}", "friend");
    assert(strcmp(sstring_to_cstr(replace_me),"This is a {} day, friend!") == 0);
    sstring_substitute(replace_me, 0, "{}", "good");
    assert(strcmp(sstring_to_cstr(replace_me), "This is a good day, friend!") == 0);

    printf("\nDone\n");
    return 0;
}
