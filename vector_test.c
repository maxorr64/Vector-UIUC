/**
 * vector
 * CS 341 - Fall 2023
 */
#include "vector.h"
#include "sstring.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define INITIAL_CAPACITY 8
#define GROWTH_FACTOR 2


void* test_fn_default() {
    return NULL;
}

void * test_fn_copy_constructor(void* s) {
    char* copy = malloc(strlen(s) + 1);
    strcpy(copy, s);
    return copy;
}

void test_fn_destructor(void* s) {
    if(s != NULL)
        free(s);
}

vector* test_setup_callbacks() {
    return vector_create(test_fn_copy_constructor, test_fn_destructor, test_fn_default);
}

void test_callback_push_back() {
    vector* vec = test_setup_callbacks();
    vector_push_back(vec, "test0");
    assert(strcmp(vector_get(vec, 0),"test0") == 0);
    vector_destroy(vec);
}


vector* test_setup_callbacks_3() {
    vector* vec = test_setup_callbacks();
    vector_push_back(vec, "test0");
    vector_push_back(vec, "test1");
    vector_push_back(vec, "test2");
    return vec;
}

vector* test_setup_8() {
    vector* vec = vector_create(NULL, NULL, NULL);
    for (size_t i = 0; i < 8; i++) {
        vector_push_back(vec, "test");
    }
    return vec;
}

vector* test_setup() {
    return vector_create(NULL, NULL, NULL);
}

vector* test_setup_3() {
    vector* vec = test_setup();
    vector_push_back(vec, "test1");
    vector_push_back(vec, "test2");
    vector_push_back(vec, "test3");
    return vec;
}

int compare_str(char* s1, char*s2)
{
    if(s1 == NULL && s2 == NULL)
        return 0;
    if(s1 == NULL || s2 == NULL)
        return 1;
    return strcmp(s1, s2);
}
void assert_string_vector0(vector* vec, size_t count)
{
    assert(vector_size(vec) == count);
}

void assert_string_vector1(vector* vec, size_t count, char* s0)
{
    assert(vector_size(vec) == count);
    assert(count == 0 || compare_str(vector_get(vec, 0), s0) == 0);
}

void assert_string_vector2(vector* vec, size_t count, char* s0, char* s1)
{
    assert(vector_size(vec) == count);
    assert(count == 0 || compare_str(vector_get(vec, 0), s0) == 0);
    assert(count < 1 || compare_str(vector_get(vec, 1), s1) == 0);
}

void assert_string_vector3(vector* vec, size_t count, char* s0, char* s1, char* s2)
{
    assert(vector_size(vec) == count);
    assert(count == 0 || compare_str(vector_get(vec, 0), s0) == 0);
    assert(count < 1 || compare_str(vector_get(vec, 1), s1) == 0);
    assert(count < 2 || compare_str(vector_get(vec, 2), s2) == 0);
}

void assert_string_vector4(vector* vec, size_t count, char* s0, char* s1, char* s2, char*s3)
{
    assert(vector_size(vec) == count);
    assert(count == 0 || compare_str(vector_get(vec, 0), s0) == 0);
    assert(count < 1 || compare_str(vector_get(vec, 1), s1) == 0);
    assert(count < 2 || compare_str(vector_get(vec, 2), s2) == 0);
    assert(count < 3 || compare_str(vector_get(vec, 3), s3) == 0);
}

void assert_string_vector5(vector* vec, size_t count, char* s0, char* s1, char* s2, char*s3, char*s4)
{
    assert(vector_size(vec) == count);
    assert(count == 0 || compare_str(vector_get(vec, 0), s0) == 0);
    assert(count < 1 || compare_str(vector_get(vec, 1), s1) == 0);
    assert(count < 2 || compare_str(vector_get(vec, 2), s2) == 0);
    assert(count < 3 || compare_str(vector_get(vec, 3), s3) == 0);
    assert(count < 4 || compare_str(vector_get(vec, 4), s4) == 0);
}

void assert_string_vector6(vector* vec, size_t count, char* s0, char* s1, char* s2, char*s3, char*s4, char*s5)
{
    assert(vector_size(vec) == count);
    assert(count == 0 || compare_str(vector_get(vec, 0), s0) == 0);
    assert(count < 1 || compare_str(vector_get(vec, 1), s1) == 0);
    assert(count < 2 || compare_str(vector_get(vec, 2), s2) == 0);
    assert(count < 3 || compare_str(vector_get(vec, 3), s3) == 0);
    assert(count < 4 || compare_str(vector_get(vec, 4), s4) == 0);
    assert(count < 5 || compare_str(vector_get(vec, 5), s5) == 0);
}

void test_create_normal() {    
    vector* vec = test_setup();
    assert_string_vector0(vec, 0);
    assert(vector_capacity(vec) == INITIAL_CAPACITY);
    /*
    assert(vec->copy_constructor == shallow_copy_constructor);
    assert(vec->default_constructor == shallow_default_constructor);
    assert(vec->destructor == shallow_destructor);
    */
    vector_destroy(vec);
}

void test_push_back() {
    //setup_3 calls pushback 3 times.
    vector* vec = test_setup_3();
    assert_string_vector3(vec, 3, "test1", "test2", "test3");
    vector_destroy(vec);
}

void test_begin() {
    vector* vec = test_setup_3();
    void* begin = vector_begin(vec);
    void* start = vector_at(vec, 0);
    assert(start == begin);
    vector_destroy(vec);
}

void test_begin_callback() {
    vector* vec = test_setup_callbacks_3();
    void* begin = vector_begin(vec);
    void* start = vector_at(vec, 0);
    assert(start == begin);
    vector_destroy(vec);
}

void test_empty() {
    vector* vec = test_setup_3();
    assert(vector_size(vec) == 3);
    assert(!vector_empty(vec));
    vec = test_setup();
    assert(vector_size(vec) == 0);
    assert(vector_empty(vec));
    vector_destroy(vec);
}

void test_empty_callback() {
    vector* vec = test_setup_callbacks_3();
    assert(vector_size(vec) == 3);
    assert(!vector_empty(vec));
    vec = test_setup_callbacks();
    assert(vector_size(vec) == 0);
    assert(vector_empty(vec));
    vector_destroy(vec);
}

void test_resize() {
    vector* vec = test_setup_3();
    vector_resize(vec, 4);
    assert_string_vector4(vec, 4, "test1", "test2", "test3", NULL);
    vector_resize(vec, 2);
    assert_string_vector2(vec, 2, "test1", "test2");
    vector_resize(vec, 2);
    assert_string_vector2(vec, 2, "test1", "test2");
    vector_destroy(vec);
}

void test_resize_callback() {
    vector* vec = test_setup_callbacks_3();
    vector_resize(vec, 4);
    assert_string_vector4(vec, 4, "test0", "test1", "test2", NULL);
    vector_resize(vec, 2);
    assert_string_vector2(vec, 2, "test0", "test1");
    vector_resize(vec,2);
    assert_string_vector2(vec, 2, "test0", "test1");
    vector_destroy(vec);
}

void test_end() {
    vector* vec = test_setup_3();
    void* end = vector_end(vec);   
    void* last = vector_at(vec, 3);
    assert(end == last);
    vector_destroy(vec);
}

void test_end_callback() {
    vector* vec = test_setup_callbacks_3();
    void* end = vector_end(vec);
    void* last = vector_at(vec, 3);
    assert(end == last);
    vector_destroy(vec);
}

void test_clear() {
    vector* vec = test_setup_3();
    vector_clear(vec);
    assert(vector_size(vec) == 0);
    vector_destroy(vec);
}

void test_clear_callbacks() {
    vector* vec = test_setup_callbacks_3();
    vector_clear(vec);
    assert(vector_size(vec) == 0);
    vector_destroy(vec);
}

void test_insert() {
    vector* vec = test_setup_3();
    vector_insert(vec, 1, "inserted value");
    char* val = vector_get(vec, 1);
    assert(strcmp("inserted value", val) == 0);
    vector_destroy(vec);
}

void test_insert_callback() {
    vector* vec = test_setup_callbacks_3();
    vector_insert(vec, 1, "inserted value");
    char* val = vector_get(vec, 1);
    assert(strcmp("inserted value", val) == 0);
    vector_destroy(vec);
}

void test_back() {
    vector* vec = test_setup_3();
    assert(vector_back(vec) == vector_at(vec, 3));
    vector_destroy(vec);
}

void test_back_callback(){
    vector* vec = test_setup_callbacks_3();
    assert(vector_back(vec) == vector_at(vec, 3));
    vector_destroy(vec);
}

void test_pop_back() {
    vector* vec = test_setup_3();
    vector_pop_back(vec);
    assert(vector_size(vec) == 2);
    void** back = vector_back(vec);
    assert(back == vector_at(vec,2));
    vector_destroy(vec);
}

void test_pop_back_callback() {
    vector* vec = test_setup_callbacks_3();
    vector_pop_back(vec);
    assert(vector_size(vec) == 2);
    void** back = vector_back(vec);
    assert(back == vector_at(vec, 2));
    vector_destroy(vec);
}

void test_set() {
    vector* vec = test_setup_3();
    vector_set(vec, 1, "set string");
    assert(strcmp(vector_get(vec, 1), "set string") == 0);
    vector_destroy(vec);
}

void test_set_callback() {
    vector* vec = test_setup_callbacks_3();
    vector_set(vec, 1, "set string");
    assert(strcmp(vector_get(vec, 1), "set string") == 0);
    vector_destroy(vec);
}

void test_capacity() {
    vector* vec = test_setup_3();
    assert(vector_capacity(vec) == INITIAL_CAPACITY);
    vec = test_setup();
    assert(vector_capacity(vec) == INITIAL_CAPACITY);
    vector_destroy(vec);
}

void test_capacity_callback() {
    vector* vec = test_setup_3();
    assert(vector_capacity(vec) == INITIAL_CAPACITY);
    vec = test_setup();
    assert(vector_capacity(vec) == INITIAL_CAPACITY);
    vector_destroy(vec);
}

void test_reserve() {
    vector* vec = test_setup_3();
    vector_reserve(vec, 3);
    assert(vector_capacity(vec) == INITIAL_CAPACITY);
    vector_reserve(vec, INITIAL_CAPACITY);
    assert(vector_capacity(vec) == INITIAL_CAPACITY);
    vector_reserve(vec, 100);
    assert(vector_capacity(vec) == 100);
    vector_destroy(vec);
}

void test_reserve_callback() {
    vector* vec = test_setup_callbacks_3();
    vector_reserve(vec, 3);
    assert(vector_capacity(vec) == INITIAL_CAPACITY);
    vector_reserve(vec, INITIAL_CAPACITY);
    assert(vector_capacity(vec) == INITIAL_CAPACITY);
    vector_reserve(vec, 100);
    assert(vector_capacity(vec) == 100);
    vector_destroy(vec);
}


void test_callback_create() {
    vector* vec = test_setup_callbacks();
    char* test = "Do not copy me";
    vector_push_back(vec, test);
    char* storedValue = vector_get(vec, vector_size(vec)-1);
    assert(storedValue != test);
    assert(strcmp(storedValue, test) == 0);
    vector_destroy(vec);
}


void test_vec_empty() {
    vector* vec = test_setup();
    assert(vector_empty(vec) == true);
    vector_destroy(vec);
}

void test_vec_at_greater_size() {
    vector* vec = test_setup_3();
    assert(vector_at(vec, 4) == NULL);
    vector_destroy(vec);
}

void test_vec_set_greater_size() {
    vector* vec = test_setup_3();
    vector_set(vec, 9, "test9");
    assert(vector_size(vec) == 3);
    vector_destroy(vec);
}

void test_vec_get_greater_size() {
    vector* vec = test_setup_3();
    assert(vector_get(vec, 9) == NULL);
    vector_destroy(vec);
}

void test_vec_push_back_capacity() {
    vector* vec = test_setup_8();
    vector_push_back(vec, "test9");
    assert(vector_capacity(vec) == INITIAL_CAPACITY*GROWTH_FACTOR);
    vector_destroy(vec);
}

void test_vec_pop_back_0() {
    vector* vec = test_setup();
    vector_pop_back(vec);
    assert(vector_size(vec) == 0);
    vector_destroy(vec);
}

void test_vec_erase() {
    vector* vec = test_setup_callbacks_3();
    vector_erase(vec, 0);
    assert_string_vector2(vec, 2, "test1", "test2");
    vector_erase(vec, 80);
    assert(vector_size(vec) == 2);
    vector_destroy(vec);
}

void test_vec_front() {
    vector* vec = test_setup_3();
    void** front = vector_front(vec);
    void** start = vector_at(vec,0);
    assert(front == start);
}


int main() {
    test_callback_push_back();
    test_setup();
    test_create_normal();
    test_push_back();
    test_begin();
    test_end();
    test_clear();
    test_insert();
    test_back();
    test_pop_back();
    test_set();   
    test_capacity();
    test_reserve();
    test_resize();
    test_callback_create();
    test_vec_empty();
    test_vec_get_greater_size();
    test_vec_set_greater_size();
    test_vec_at_greater_size();
    test_vec_push_back_capacity();
    test_vec_pop_back_0();
    test_vec_empty();
    test_vec_erase();
    test_vec_front();
    test_begin_callback();
    test_empty_callback();
    test_resize_callback();
    test_end_callback();
    test_clear_callbacks();    
    test_insert_callback();
    test_back_callback();
    test_pop_back_callback();
    test_set_callback();
    test_capacity_callback();
    test_reserve_callback();
    printf("\n\nDone\n\n");
    return 0;
}

