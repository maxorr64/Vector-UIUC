#include "vector.h"
#include "callbacks.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct vector {
    copy_constructor_type copy_constructor;
    destructor_type destructor;
    default_constructor_type default_constructor;
    size_t capacity;
    size_t size;
    void** data;
};
#define INITIAL_CAPACITY 8
#define GROWTH_FACTOR 2


vector *vector_create(copy_constructor_type copy_constructor,
                      destructor_type destructor,
                      default_constructor_type default_constructor) {
                        vector* vec = malloc(sizeof(vector));
                        if(!copy_constructor) {
                          vec->copy_constructor = shallow_copy_constructor;
                        } else {
                          vec->copy_constructor = copy_constructor;
                        }
                        if(!default_constructor) {
                          vec->default_constructor = shallow_default_constructor;
                        } else{
                          vec->default_constructor = default_constructor;
                        }
                        if(!destructor) {
                          vec->destructor = shallow_destructor;
                        } else {
                          vec->destructor = destructor;
                        }
                        vec->size = 0;
                        vec->capacity = INITIAL_CAPACITY;
                        vec->data = malloc(vec->capacity * sizeof(void*));
                        return vec;
                      }

void vector_destroy(vector *this) {
  vector_clear(this);
  free(this->data);
  free(this);
}

void **vector_begin(vector *this) {
  return &this->data[0];
}

void **vector_end(vector *this) {
  return &this->data[this->size];
}

size_t vector_size(vector *this) {
  return this->size;
}

void vector_resize(vector *this, size_t n) {
  if (n < this->size) {
    for (size_t i = n; i < this->size; i++) {
      this->destructor(vector_get(this, i));
    }
    this->size = n;
  } else if (this->size == n){
    return;
  } else {
    this->capacity = n;
    size_t old_size = this->size;
    void** old_data = this->data;
    this->data = malloc(this->capacity * sizeof(void*));
    memcpy(this->data, old_data, this->size*sizeof(void*));
    free(old_data);
    void** start = &this->data[old_size];
    void** end = &this->data[n];
    this->size = n;
    while(start < end) {
      *start = this->default_constructor();
      start++;
    }
  }
}

size_t vector_capacity(vector *this) {
  return this->capacity;
}

bool vector_empty(vector *this) {
  return this->size == 0;
}

void vector_reserve(vector *this, size_t n) {
  if (this->capacity > n) {
    return;
  } else if (this->capacity == n) {
    return;
  } else {
    this->capacity = n;
    //void** old_data = this->data;
    this->data = realloc(this->data, this->capacity*sizeof(void*));
    return;
  }
}

void **vector_at(vector *this, size_t n) {
  if(n > this->size) {
    return NULL;
  }
  return &this->data[n];
}

void vector_set(vector *this, size_t n, void *element) {
  if(n > this->size) {
    return;
  }
  if (n < 0) {
    return;
  }
  this->destructor(this->data[n]);
  this->data[n] = this->copy_constructor(element);
}

void *vector_get(vector *this, size_t n) {
  if (n >= this->size) { 
    return NULL;
  };
  return this->data[n];
}

void **vector_front(vector *this) {
  return &(this->data[0]);
}

void **vector_back(vector *this) {
  return &(this->data[this->size]);
}

void vector_push_back(vector *this, void *element) {
  if (this->size == this->capacity) {
    vector_reserve(this, this->capacity*GROWTH_FACTOR);
  }
  this->size++;
  this->data[this->size-1] = this->default_constructor();
  vector_set(this, this->size-1, element);
}

void vector_pop_back(vector *this) {
  if(this->size == 0)
    return;
  this->destructor(this->data[this->size-1]);
  this->size--;
}

void vector_insert(vector *this, size_t position, void *element) {
  if(this->size+1 >= this->capacity) {
    vector_reserve(this, this->size+1);
  }
  memmove(&this->data[position+1], &this->data[position], (this->size-position)*sizeof(void*));
  this->data[position] = this->copy_constructor(element);
  this->size++;
}

void vector_erase(vector *this, size_t position) {
  if (position >= this->size) {
    return;
  }
  this->destructor(this->data[position]);
  memmove(&this->data[position], &this->data[position+1], (this->size-position-1)*sizeof(void*));  
  this->size--;
}

void vector_clear(vector *this) {
  for(size_t i = 0; i < this->size; i++) {
    this->destructor(this->data[i]);
  }
  this->size = 0;
}
