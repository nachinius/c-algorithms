//
// Created by nachinius on 10/25/16.
//

#include "hash.h"
#include <stdlib.h>
#include <printf.h>

// http://planetmath.org/goodhashtableprimes
int primes_p[] = {53,97,193,389,769,1543,3079,6151,12289,24593,49157};

hash_str * hash_init() {
    hash_str *h;
    h = malloc(sizeof(hash_str));

    h->rows = calloc(32, sizeof(list *));
    h->m = 32;
    h->p = 53;
    h->k = 0;

    h->a = 1;
    h->b = 1;

    return h;
}

void hash_free(hash_str *h) {
    list *r,*p = NULL;
    list **a = NULL;
    for(int i=0; i<h->m; i++) {

        a = h->rows + i;
        r = *a;
        p = *a;

        // get the last
        while(NULL != p) {
            r = p;
            p = p->next;
        }

        // free memory from last to front
        while(NULL != r) {
            p = r->back;
            free(r);
            r = p;
        }
    }
}

int hash(int key, int p, int m, int a, int b) {
    int a1,a2,a3,a4;

    a1 = a*key;
    a2 = a*key +b;
    a3 = a2 % p;
    a4 = a3 % m;
    return a4;
}
int hash_key(hash_str *h, int key) {
    return hash(key, h->p, h->m, h->a, h->b);
}

void hash_insert(hash_str *h, int key, void *element) {

    int hk;
    hk = hash_key(h, key);

    list *p,*r = NULL;
    list **a = NULL;
    a = h->rows + hk;

    p = *a;

    // try to find if the key already exists
    while( NULL != p && p->key != key) {
        p = p->next;
    }

    // key not found
    if(NULL == p) {
        p = malloc(sizeof(list));
        p->e = element;
        p->key = key;
        p->back = NULL;
        p->next = *a;
        if(*a != NULL) (*a)->back = p;
        *a = p;
    } else { // overwrite key element
        p->e = element;
    }
    h->k += 1;

}

void * hash_get(hash_str *h, int key) {
    list *p,*r;
    list **a = NULL;

    int hk;
    hk = hash_key(h, key);

    a = h->rows + hk;

    p = *a;

    while (NULL != p && p->key != key) {
        r = p;
        p = p->next;
    }

    return (NULL == p) ? NULL : p->e;
}

void hash_print(hash_str *h) {
    list **a;
    list *r, *p = NULL;
    int j;
    for(int i=0; i<h->m; i++) {

        a = h->rows + i;

        p = *a;
        j=0;

        while(NULL != p) {
            if(p->e != NULL) {
//                printf("\tkey=%d\tvalue=%d\n", p->key, *(int *) p->e);
                j++;
            }
            p = p->next;
        }
        printf("%d, %d\n",i,j);
    }
}

int hash_delete(hash_str *h, int key) {
    list *p,*r;
    list **a = NULL;

    int hk;
    hk = hash_key(h, key);

    a = h->rows + hk;

    r = NULL;
    p = *a;

    while( NULL != p && p->key != key) {
        r = p;
        p = p->next;
    }

    if(NULL == p) return 0; // not found
    else {
        if (NULL == r) { // first
            *a = NULL;
            free(p);
        } else {
            r->next = p->next;
            if(NULL != p->next) { // fix the back of the next
                p->back = r;
            }
            free(p);
        }
        return 1;
    }
}