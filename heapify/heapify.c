//
// Created by nachinius on 10/20/16.
//

#include <stdlib.h>
#include <memory.h>
#include <printf.h>
#include <math.h>

typedef struct {
    int *h;
    int sizeOfHeap;
    int sizeOfArray;
} heap_str;

heap_str * heap_init(size_t size) {
    heap_str *h;
    h = malloc(sizeof(heap_str *));
    h->h = malloc(sizeof(int) * (1+size));
    h->sizeOfArray = (int) size;
    h->sizeOfHeap = 0;
    return h;
}

void heap_free(heap_str *h) {
    free(h->h);
    free(h);
}

void swap(heap_str *h, int i, int j) {
    int x;
    x = h->h[j];
    h->h[j] = h->h[i];
    h->h[i] = x;
}
#define LEFT(i) (2*i)
#define RIGHT(i) (LEFT(i)+1)
void heap_maxify(heap_str *h, int i) {
    int a,b;
    int largest = i;
    a = LEFT(i);
    b = a + 1;

    if(a <= h->sizeOfHeap && h->h[a] > h->h[i]) {
        largest = a;
    }
    if(b <= h->sizeOfHeap && h->h[b] > h->h[largest]) {
        largest = b;
    }
    if(largest != i) {
        swap(h,i, largest);
        heap_maxify(h, largest);
    }
}
void heap_build_max(heap_str *h) {

    for(int i=h->sizeOfHeap/2; i>0;i--) {
        heap_maxify(h,i);
    }
}

heap_str * heap_build(int *a, int size) {
    heap_str *h;
    h = heap_init(size);

    memcpy((h->h)+1, a, sizeof(int) * size);
    h->sizeOfHeap = size;
    h->sizeOfArray = size;

    heap_build_max(h);
    return h;
}


void heap_print_array(heap_str *h) {
    for(int i=1; i<=h->sizeOfHeap; i++) {
       printf("%d, ",h->h[i]);
    }
    printf("\n");
}

/**
 * Sort an array of int of size 'size'
 * @param a initial allocated pointer to array
 * @param size
 */
heap_str * heap_sort(int *a, int size) {
    heap_str *h;

    h = malloc(sizeof(heap_str));
    h->h = a-1; // in purpose we'll always access at idx '1'
    h->sizeOfHeap = size;
    h->sizeOfArray = size;

    heap_build_max(h);

    for(int i=size; i>=2; i--) {
        swap(h,i,1); // remove top
        h->sizeOfHeap = h->sizeOfHeap - 1;
        heap_maxify(h,1); // maxify rest of heap
    }
    return h;
}

#undef LEFT
#undef RIGHT

