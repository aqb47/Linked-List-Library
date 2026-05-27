#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

// Internal helpers
Node* node_at(LinkedList* linkedlist, int index);

LinkedList ll_create(void) {
    LinkedList linkedlist;

    linkedlist.size = 0;
    linkedlist.head = NULL;
    linkedlist.tail = NULL;

    return linkedlist;
}

void ll_free(LinkedList* linkedlist) {
    Node* current_node = linkedlist->head;

    // Traverse through linked list starting from head
    while(current_node != NULL) {
        // Keep track of current node
        Node* temp_node = current_node;

        // Move to next node
        current_node = current_node->next;

        // Free temporary node
        free(temp_node);
    }

    // Reset values
    linkedlist->size = 0;
    linkedlist->head = NULL;
    linkedlist->tail = NULL;
}

int ll_push_back(LinkedList* linkedlist, void* item) {
    // Get tail
    Node* prev_tail = linkedlist->tail;
    
    // Make new node and initialize data
    Node* new_node = (Node*) malloc(sizeof(Node));
    
    // If something goes wrong
    if (new_node == NULL) {
        return 1;
    }

    new_node->data = item;

    new_node->prev = prev_tail;

    if (prev_tail != NULL) {
        prev_tail->next = new_node;
    }

    new_node->next = NULL;

    // Append to tail
    linkedlist->tail = new_node;

    // In case of an empty linked list
    if (prev_tail == NULL) {
        linkedlist->head = new_node;
    }

    // Increment size
    linkedlist->size += 1;

    return 0;
}

int ll_push_front(LinkedList* linkedlist, void* item) {
    // Get head
    Node* prev_head = linkedlist->head;

    // Make new node and initialize data
    Node* new_node = (Node*) malloc(sizeof(Node));

    // If something goes weong
    if (new_node == NULL) {
        return 1;
    }

    new_node->data = item;

    new_node->next = prev_head;

    if (prev_head != NULL) {
        prev_head->prev = new_node;
    }

    new_node->prev = NULL;

    // Prepend to head
    linkedlist->head = new_node;

    // In case of an empty linked list
    if (prev_head == NULL) {
        linkedlist->tail = new_node;
    }

    // Increment size
    linkedlist->size += 1;

    return 0;
}

void* ll_pop_back(LinkedList* linkedlist) {
    // Nothing to pop if linked list was empty
    if (linkedlist->size == 0) {
        return NULL;
    }

    Node* prev_tail = linkedlist->tail;
    void* prev_tail_item = prev_tail->data;

    // Set current tail of linked list as previous node to previous tail
    if (linkedlist->size == 1) {
        linkedlist->head = NULL;
        linkedlist->tail = NULL;
    }
    else {
        linkedlist->tail = prev_tail->prev;
        linkedlist->tail->next = NULL;
    }

    // Free previous tail since it isn't part of the linked list anymore
    free(prev_tail);

    // Decrement size of linked list
    linkedlist->size -= 1;

    return prev_tail_item;
}

void* ll_pop_front(LinkedList* linkedlist) {
    // Nothing to pop if linked list is empty
    if (linkedlist->size == 0) {
        return NULL;
    }

    Node* prev_head = linkedlist->head;
    void* prev_head_item = prev_head->data;

    // Set current head of linked list as next node of previous head
    if (linkedlist->size == 1) {
        linkedlist->head = NULL;
        linkedlist->tail = NULL;
    }
    else {
        linkedlist->head = prev_head->next;
        linkedlist->head->prev = NULL;
    }

    // Free previous head since it isn't part of the linked list anymore
    free(prev_head);

    // Decrement size of linked list
    linkedlist->size -= 1;

    return prev_head_item;
}

void* ll_get(LinkedList* linkedlist, int index) {
    // Check for valid usage
    if (index >= linkedlist->size || index < 0) {
        return NULL;
    }

    // Get node at that index
    Node* node_at_index = node_at(linkedlist, index);

    // Return data of node
    return node_at_index->data;
}

int ll_insert(LinkedList* linkedlist, int index, void* item) {
    // Check for valid usage (> instead of >= as item can be inserted at end of list)
    if (index > linkedlist->size || index < 0) {
        return 1;
    }

    // Initialize new node
    Node* new_node = (Node*) malloc(sizeof(Node));
    
    // In case something goes wrong
    if (new_node == NULL) {
        return 1;
    }

    new_node->data = item;

    // Get node at index to be inserted
    Node* node_at_insert = node_at(linkedlist, index);

    // For an empty list and insertion into first index
    if (index == 0 && linkedlist->size == 0) {
        new_node->prev = NULL;
        new_node->next = NULL;

        linkedlist->head = new_node;
        linkedlist->tail = new_node;
    }
    // In case of insertion at end of non-empty list
    else if (index == linkedlist->size ) {
        new_node->prev = linkedlist->tail;
        new_node->next = NULL;

        linkedlist->tail->next = new_node;
        linkedlist->tail = new_node;
    }
    // In case of insertion at beginning of non-empty list
    else if (index == 0) {
        new_node->prev = NULL;
        new_node->next = linkedlist->head;

        linkedlist->head->prev = new_node;
        linkedlist->head = new_node;
    }
    // Normal case
    else {
        new_node->prev = node_at_insert->prev;
        new_node->next = node_at_insert;
        
        node_at_insert->prev->next = new_node;
        node_at_insert->prev = new_node;
    }

    // Increment size
    linkedlist->size += 1;

    return 0;
}

int ll_delete(LinkedList* linkedlist, int index) {
    // Check for valid usage
    if (index >= linkedlist->size || index < 0) {
        return 1;
    }

    // Get node at index to be deleted
    Node* node_to_delete = node_at(linkedlist, index);

    // Change previous and next pointers of next and previous nodes of node to be deleted
    if (node_to_delete->prev != NULL) {
        node_to_delete->prev->next = node_to_delete->next;
    }

    if (node_to_delete->next != NULL) {
        node_to_delete->next->prev = node_to_delete->prev;
    }

    // In case index is at beginning of list or end of list then head or tail of list has to be changed
    if (index == 0) {
        linkedlist->head = node_to_delete->next; 
    }
    
    if (index == linkedlist->size - 1) {
        linkedlist->tail = node_to_delete->prev;
    }

    // Free deleted node since it won't be used
    free(node_to_delete);

    // Decrement size
    linkedlist->size -= 1;

    return 0;
}

int ll_size(LinkedList* linkedlist) {
    return linkedlist->size;
}

void ll_print(LinkedList* linkedlist, void (*print_fn) (void*)) {
    Node* ptr = linkedlist->head;

    while(ptr != NULL) {
        print_fn(ptr->data);

        printf(" -> ");

        ptr = ptr->next;
    }
    printf("NULL\n");
}

void print_int(void* data) {
    printf("%i ", *(int*)data);
}

void print_double(void* data) {
    printf("%lf ", *(double*)data);
}

void print_char(void* data) {
    printf("%c ", *(char *)data);
}

void print_string(void* data) {
    printf("%s ", (char *)data);
}

void ll_reverse(LinkedList* linkedlist) {
    // In case of an empty list
    if (linkedlist->size == 0) {
        return;
    }

    // Swaps
    int count = 0;

    // We'll have one node pointer traverse from head to tail while the other goes tail to head
    Node* front_to_back = linkedlist->head;
    Node* back_to_front = linkedlist->tail;

    while (count < linkedlist->size / 2) {
        // Swap front to back and back to front data
        void* ftb_temp = front_to_back->data;

        front_to_back->data = back_to_front->data;
        back_to_front->data = ftb_temp;

        // Continue traversal
        front_to_back = front_to_back->next;
        back_to_front = back_to_front->prev;

        // Increment swaps
        count += 1;
    }
}

Node* node_at(LinkedList* linkedlist, int index) {
    Node* current_node = linkedlist->head;

    for (int i = 0; i < index; i++) {
        current_node = current_node->next;

        if (current_node == NULL) {
            break;
        }
    }

    return current_node;
}