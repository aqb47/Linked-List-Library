#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct {
    Node* next;
    Node* prev;
    
    void* data;
} Node;

typedef struct {
    Node* head;
    Node* tail;

    int size;
} LinkedList;

LinkedList ll_create(void);
void ll_free(LinkedList* linkedlist);

int ll_push_back(LinkedList* linkedlist, void* item);
int ll_push_front(LinkedList* linkedlist, void* item);

void* ll_pop_back(LinkedList* linkedlist);
void* ll_pop_front(LinkedList* linkedlist);

void* ll_get(LinkedList* linkedlist, int index);

int ll_insert(LinkedList* linkedlist, int index, void* data);
int ll_delete(LinkedList* linkedlist, int index);

int ll_size(LinkedList* linkedlist);

void ll_print(LinkedList* linkedlist, void (*print_fn) (void*));

void print_int(void* data);
void print_double(void* data);
void print_char(void* data);
void print_string(void* data);

void ll_reverse(LinkedList* linkedlist);

#endif