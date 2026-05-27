#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node {
    struct Node* next;
    struct Node* prev;
    void* data;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

LinkedList ll_create(void);
void ll_free(LinkedList* linkedlist); // Free all nodes

int ll_push_back(LinkedList* linkedlist, void* item); // Append to tail
int ll_push_front(LinkedList* linkedlist, void* item); // Prepend to head

void* ll_pop_back(LinkedList* linkedlist); // Remove tail
void* ll_pop_front(LinkedList* linkedlist); // Remove head

void* ll_get(LinkedList* linkedlist, int index); // Return node at 0-based index

int ll_insert(LinkedList* linkedlist, int index, void* item); // Insert node at index 
int ll_delete(LinkedList* linkedlist, int index); // Remove node at index

int ll_size(LinkedList* linkedlist); // Return size of linked list

void ll_print(LinkedList* linkedlist, void (*print_fn) (void*)); // Print entire linked list

// Helpers for printing
void print_int(void* data);
void print_double(void* data);
void print_char(void* data);
void print_string(void* data);

void ll_reverse(LinkedList* linkedlist); // Reverse linked list

#endif