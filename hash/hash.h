//
// Created by nachinius on 10/25/16.
//

#ifndef ALGC_HASH_H
#define ALGC_HASH_H

typedef struct slist {
    void *e;
    struct slist *next;
    struct slist *back;
    int key;
} list;

typedef struct {
    list **rows;

    int p; // prime to use for hash
    int m; // size of table
    int a; // 'a' of universal H_{a,b}
    int b; // 'b' of universal H_{a,b}
    int k; // keys stored
} hash_str;

hash_str * hash_init();

void hash_insert(hash_str *h, int key, void *element);

void hash_delete(hash_str *h, int key);

void * hash_get(hash_str *h, int key);

void hash_free(hash_str *h);

void hash_print(hash_str *h);

int hash_key(hash_str *h, int key);

#endif //ALGC_HASH_H
