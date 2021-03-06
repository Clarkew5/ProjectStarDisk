#include "heap.h"

Heap* create_heap(){
    //creates the heap
    Heap *h = malloc(sizeof(Heap));
    if (h == NULL) exit(-1);
    
    //creates the head of the heap
    h->head = malloc(sizeof(Heap_Level));
    if (h->head == NULL) exit(-1);
    h->head->level = 1;
    h->head->data_array = calloc(1, sizeof(struct node));
    if (h->head->data_array == NULL) exit(-1);
    h->head->next_level = NULL;
    
    //sets heap data
    h->insert_level = h->head;
    h->insert_level->prev_level = NULL;
    h->insert_index = 0;   

    return h;
}

int delete_heap(Heap *h){
    Heap_Level *p = h->head->next_level;
    int sizeof_data_array = pow(2, h->head->level-1);
    for(int i = 0; i < sizeof_data_array; i++){
        free(h->head->data_array[i]->state);
        free(h->head->data_array[i]);
    }
    free(h->head->data_array);
    free(h->head);
    while (p->next_level != NULL){
        sizeof_data_array = pow(2, p->level-1);
        for(int i = 0; i < sizeof_data_array; i++){
            free(p->data_array[i]->state);
            free(p->data_array[i]);
        }
        free(p->data_array);
        p = p->next_level;
        free(p->prev_level);
    }
    sizeof_data_array = pow(2, p->level-1);
    for(int i = 0; i < sizeof_data_array; i++){
        if (!p->data_array[i]) break;
        free(p->data_array[i]->state);
        free(p->data_array[i]);
    }
    free(p->data_array);
    free(p);
    free(h);
    return 0;
}

int add(Heap *h, struct node *data){
    h->insert_level->data_array[h->insert_index] = data;
    up_heap(h);

    int sizeof_array = (int)pow(2, h->insert_level->level-1);
    if ( h->insert_index + 1 < sizeof_array){
        h->insert_index++;
    } else {
        h->insert_level->next_level = malloc(sizeof(Heap_Level));
        if (h->insert_level->next_level == NULL) exit(-1);
        h->insert_level->next_level->level = h->insert_level->level+1;
        h->insert_level->next_level->prev_level = h->insert_level;
        h->insert_level = h->insert_level->next_level; 
        int sizeof_array = (int)pow(2, h->insert_level->level-1);       
        h->insert_level->data_array = calloc(sizeof_array, sizeof(struct node));
        h->insert_level->next_level = NULL;
        h->insert_index = 0;
    }
    return 0;
}

struct node* pop(Heap *h){
    struct node *head_data = h->head->data_array[0];


    if (h->insert_index-1 >= 0){    
        h->insert_index--;
    }
    else{
        h->insert_level = h->insert_level->prev_level;
        free(h->insert_level->next_level->data_array);
        free(h->insert_level->next_level);
        h->insert_level->next_level = NULL;

        h->insert_index = (int)(pow(2, h->insert_level->level-1)-1);       
    }

    h->head->data_array[0] = h->insert_level->data_array[h->insert_index];
    h->insert_level->data_array[h->insert_index] = NULL;
    down_heap(h);

    return head_data;
}

int up_heap(Heap *h){
    Heap_Level *c_l = h->insert_level; //child level
    int c_i = h->insert_index; //child index
    Heap_Level *p_l = h->insert_level->prev_level; //parent level
    int p_i = c_i/2; //parent index
    while (p_l != NULL){
        if (c_l->data_array[c_i]->f <= p_l->data_array[p_i]->f){
            swap_nodes(c_l, c_i, p_l, p_i);
            c_l = p_l;
            c_i = p_i;            
            p_l = p_l->prev_level;
            p_i = c_i/2;
        }
        else break;
    }
    return 0;
}

int down_heap(Heap *h){
    Heap_Level *p_l = h->head; //parent level
    int p_i = 0; //parent index
    Heap_Level *c_l = h->head->next_level; //child level
    int lc_i = p_i*2; //left child index
    int rc_i = lc_i+1; //right child index
    
    while (c_l != NULL
        && c_l->data_array[lc_i] != NULL && c_l->data_array[rc_i] != NULL){

        if (p_l->data_array[p_i]->f >= c_l->data_array[lc_i]->f
         && c_l->data_array[rc_i]->f >= c_l->data_array[lc_i]->f){
            
            swap_nodes(p_l, p_i, c_l, lc_i);
            p_i = lc_i;
        }
        else if (p_l->data_array[p_i]->f >= c_l->data_array[rc_i]->f 
              && c_l->data_array[lc_i]->f >= c_l->data_array[rc_i]->f){

            swap_nodes(p_l, p_i, c_l, rc_i);
            p_i = rc_i;
        }
        p_l = c_l;
        c_l = c_l->next_level;
        lc_i = p_i*2;
        rc_i = lc_i+1;
    
    }
    return 0;
}

int swap_nodes(Heap_Level *al, int ai, Heap_Level *bl, int bi){
    struct node *temp = al->data_array[ai];
    al->data_array[ai] = bl->data_array[bi];
    bl->data_array[bi] = temp;
    return 0;
}

int print_heap(Heap *h){
    Heap_Level *p = h->head;   
    while(p != NULL){
        printf("level: %d\n", p->level);        
        int sizeof_data_array = pow(2, p->level-1);
        for(int i = 0; i < sizeof_data_array; i++){
            printf("%d ", (p->data_array[i] ? p->data_array[i]->f : 0));
        }
        printf("\n");
        p = p->next_level;
    }
    return 0;
}

