/**
 * vector
 * CS 341 - Fall 2023
 */
#include "sstring.h"
#include "vector.h"

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <assert.h>
#include <string.h>

struct sstring {
    char* str;
    size_t size;
};

sstring* cstr_to_sstr(const char* input) {
    sstring* sstr = malloc(sizeof(sstring));
    sstr->size = strlen(input);

    sstr->str = malloc(sstr->size+1);
    strcpy(sstr->str, input);
    return sstr;
}

sstring *cstr_to_sstring(const char *input) {
    // your code goes here
    sstring* sstr = malloc(sizeof(sstring));
    sstr->size = strlen(input);

    sstr->str = malloc(sstr->size+1);
    strcpy(sstr->str, input);
    return sstr;
}

char *sstring_to_cstr(sstring *input) {
    // your code goes here
    return strdup(input->str);
}

int sstring_append(sstring *this, sstring *addition) {
    // your code goes here
    size_t new_size = this->size + addition->size + 1;
    char* new_str = malloc(new_size * sizeof(char*));
    strcpy(new_str, this->str);
    strcpy(new_str+this->size, addition->str);
    new_str[new_size-1] = '\0';
    free(this->str);
    this->str = new_str;
    this->size = new_size - 1;
    return new_size;
}

void push_substr_to_vec(vector* vec, char* start, int count) {
    char* str = malloc(sizeof(char)*count + 1);
    strncpy(str, start, count);
    str[count] = '\0';
    vector_push_back(vec, str);
}


vector *sstring_split(sstring *this, char delimiter) {
    // your code goes here
    vector* vec = vector_create(shallow_copy_constructor, shallow_destructor, shallow_default_constructor);
    char* start = this->str;
    int count = 0;
    for(size_t i = 0; i < this->size+1; i++) {
        if (this->str[i] == delimiter || this->str[i] == '\0') {
            push_substr_to_vec(vec, start, count);
            count = 0;
            start = &this->str[i];
            start++;
        } else {
            count++;
        }
    }

    return vec;
}

int sstring_substitute(sstring *this, size_t offset, char *target,
                       char *substitution) {
    // your code goes here
    if(this != NULL) {
        size_t sub_length = strlen(substitution);
        size_t target_length = strlen(target);
        size_t loop_length = this->size;
        for (size_t i = offset; i < loop_length; i++) {
            if(strncmp(this->str+i, target, target_length) == 0) {
                char* new_str = malloc(i+sub_length + strlen(this->str) - i - target_length + 1);
                strncpy(new_str, this->str, i);
                strncpy(new_str+i, substitution, sub_length);
                strcpy(new_str+i+sub_length, this->str + i + target_length);
                *(new_str+i+sub_length + strlen(this->str) - i - target_length+1) = '\0';
                free(this->str);
                this->str = new_str;
                this->size = strlen(new_str);
                return 0;
            }
        }
    }
    return -1;
}
// this null?
// target not found
// Target exists but AFTER the offset
// multiple matching targets
// target is shorter than sub
// target is longer than sub
// target is same length as sub
// sub is empty


char *sstring_slice(sstring *this, int start, int end) {
    if(this!= NULL) {
        char* str = malloc(end - start + 1);
        strncpy(str, this->str + start, end-start);
        str[start-end-1] = '\0';
        return str;
    } else {
        return NULL;
    }
}



void sstring_destroy(sstring *this) {
    // your code goes here
    free(this->str);
    free(this);
}
