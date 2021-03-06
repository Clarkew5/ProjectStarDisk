#ifndef HEAP
#define HEAP
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>


struct node {
    int8_t heuristic;
    int8_t cost;
    int8_t f;  // heuristic + cost
    struct node *parent;
    int8_t *state;
    int8_t index0;
};

typedef struct Heap_Level{
    int level;    
    struct node **data_array;
    struct Heap_Level *next_level;
    struct Heap_Level *prev_level;
} Heap_Level;

typedef struct Heap{
    struct Heap_Level *head;
    struct Heap_Level *insert_level;
    int insert_index;
} Heap;

Heap* create_heap();
int delete_heap(Heap *h);
int add(Heap *h, struct node *data);
struct node* pop(Heap *h);
int up_heap(Heap *h);
int down_heap(Heap *h);
int swap_nodes(Heap_Level *al, int ai, Heap_Level *bl, int bi);
int print_heap(Heap *h);

#endif
