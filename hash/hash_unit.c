//
// Created by nachinius on 10/28/16.
//
// @File Unit Test for the Hash Dir
//

#include <assert.h>
#include <stdlib.h>
#include <printf.h>
#include "hash.h"

void hash_unit_init_and_free() {
    hash_str *h;

    h = hash_init();
    hash_free(h);
}

void hash_unit_retrieve_the_inserted_element() {
    hash_str *h;
    h = hash_init();

    int key = 1;
    char element[] = "a";

    hash_insert(h, key, element);

    void *p;
    p = hash_get(h, key);
    assert(p==element);
}

void hash_unit_retrieve_the_last_insert_element_with_key() {
    hash_str *h;
    h = hash_init();

    int key = 1;
    char element[] = "a";
    char element2[] = "b";

    hash_insert(h, key, element);
    hash_insert(h, key, element2);

    void *p;
    p = hash_get(h, key);
    assert(p==element2);
}

void hash_unit_get_null_on_unexistent_key() {
    hash_str *h;
    h = hash_init();

    int key = 1;
    char element[] = "a";

    hash_insert(h, key, element);

    void *p;
    p = hash_get(h, 1 + key);
    assert(NULL == p);
}

void hash_unit_delete_return_1_if_found() {
    hash_str *h;
    h = hash_init();

    int key = 1;
    char element[] = "a";

    hash_insert(h, key, element);

    int ret;
    ret = hash_delete(h, 1);
    assert(ret == 1);
}

void hash_unit_delete_return_0_if_not_found() {
    hash_str *h;
    h = hash_init();

    int key = 1;
    char element[] = "a";

    hash_insert(h, key, element);

    int ret;
    ret = hash_delete(h, 2);
    assert(ret == 0);
}



void hash_unit_test() {
    hash_unit_init_and_free();
    hash_unit_retrieve_the_inserted_element();
    hash_unit_retrieve_the_last_insert_element_with_key();
    hash_unit_get_null_on_unexistent_key();
    hash_unit_delete_return_0_if_not_found();
    hash_unit_delete_return_1_if_found();
}

int main(int argc, char **argv) {
    printf("entering unit test hash\n");
    hash_unit_test();
    return 0;
}