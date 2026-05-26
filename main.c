// Test harness
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/* ---------- section header helpers ---------- */

void section(const char* title) {
    printf("\n==== %s ====\n", title);
}

void expect(const char* label) {
    printf("  [%-30s] ", label);
}

/* =================================================================
 * EXPECTED OUTPUT:
 *
 * ==== INT LIST: push_back / push_front ====
 *   [push_back 10,20,30      ] 10 -> 20 -> 30 -> NULL
 *   [push_front 5            ] 5 -> 10 -> 20 -> 30 -> NULL
 *   [size                    ] 4
 *
 * ==== INT LIST: get ====
 *   [get index 0             ] 5
 *   [get index 2             ] 20
 *   [get out of bounds       ] NULL
 *
 * ==== INT LIST: insert ====
 *   [insert 99 at index 2    ] 5 -> 10 -> 99 -> 20 -> 30 -> NULL
 *   [insert 1 at head (0)    ] 1 -> 5 -> 10 -> 99 -> 20 -> 30 -> NULL
 *   [insert 100 at tail (6)  ] 1 -> 5 -> 10 -> 99 -> 20 -> 30 -> 100 -> NULL
 *
 * ==== INT LIST: delete ====
 *   [delete index 3 (99)     ] 1 -> 5 -> 10 -> 20 -> 30 -> 100 -> NULL
 *   [delete head (index 0)   ] 5 -> 10 -> 20 -> 30 -> 100 -> NULL
 *   [delete tail (index 4)   ] 5 -> 10 -> 20 -> 30 -> NULL
 *
 * ==== INT LIST: pop_back / pop_front ====
 *   [pop_back returns        ] 30
 *   [list after pop_back     ] 5 -> 10 -> 20 -> NULL
 *   [pop_front returns       ] 5
 *   [list after pop_front    ] 10 -> 20 -> NULL
 *
 * ==== INT LIST: reverse ====
 *   [before reverse          ] 10 -> 20 -> NULL
 *   [after reverse           ] 20 -> 10 -> NULL
 *
 * ==== DOUBLE LIST ====
 *   [push_back 3 doubles     ] 3.14 -> 2.72 -> 1.41 -> NULL
 *   [pop_back returns        ] 1.41
 *   [after pop_back          ] 3.14 -> 2.72 -> NULL
 *
 * ==== CHAR LIST ====
 *   [push_back h,e,l,l,o     ] 'h' -> 'e' -> 'l' -> 'l' -> 'o' -> NULL
 *   [insert '!' at tail      ] 'h' -> 'e' -> 'l' -> 'l' -> 'o' -> '!' -> NULL
 *   [delete index 2          ] 'h' -> 'e' -> 'l' -> 'o' -> '!' -> NULL
 *   [reverse                 ] '!' -> 'o' -> 'l' -> 'e' -> 'h' -> NULL
 *
 * ==== STRING LIST ====
 *   [push_back 3 strings     ] "hello" -> "world" -> "foo" -> NULL
 *   [push_front "start"      ] "start" -> "hello" -> "world" -> "foo" -> NULL
 *   [delete index 2          ] "start" -> "hello" -> "foo" -> NULL
 *   [pop_front returns       ] "start"
 *   [after pop_front         ] "hello" -> "foo" -> NULL
 *
 * ==== EDGE CASES ====
 *   [pop from empty list     ] NULL
 *   [delete from empty list  ] 1 (error code)
 *   [single node pop_back    ] 42
 *   [list empty after pop    ] NULL (empty)
 *   [insert out of bounds    ] 1 (error code)
 *
 * ================================================================= */

int main(void) {

    /* ---- INT LIST ---- */
    section("INT LIST: push_back / push_front");

    LinkedList int_list = ll_create();

    int a = 10, b = 20, c = 30;
    ll_push_back(&int_list, &a);
    ll_push_back(&int_list, &b);
    ll_push_back(&int_list, &c);
    expect("push_back 10,20,30");
    ll_print(&int_list, print_int);

    int d = 5;
    ll_push_front(&int_list, &d);
    expect("push_front 5");
    ll_print(&int_list, print_int);

    expect("size");
    printf("%d\n", ll_size(&int_list));


    section("INT LIST: get");

    expect("get index 0");
    void* got = ll_get(&int_list, 0);
    if (got) printf("%d\n", *(int*)got); else printf("NULL\n");

    expect("get index 2");
    got = ll_get(&int_list, 2);
    if (got) printf("%d\n", *(int*)got); else printf("NULL\n");

    expect("get out of bounds");
    got = ll_get(&int_list, 99);
    if (got) printf("%d\n", *(int*)got); else printf("NULL\n");


    section("INT LIST: insert");

    int e = 99;
    ll_insert(&int_list, 2, &e);
    expect("insert 99 at index 2");
    ll_print(&int_list, print_int);

    int f = 1;
    ll_insert(&int_list, 0, &f);
    expect("insert 1 at head (0)");
    ll_print(&int_list, print_int);

    int g = 100;
    ll_insert(&int_list, ll_size(&int_list), &g);
    expect("insert 100 at tail (6)");
    ll_print(&int_list, print_int);


    section("INT LIST: delete");

    ll_delete(&int_list, 3);
    expect("delete index 3 (99)");
    ll_print(&int_list, print_int);

    ll_delete(&int_list, 0);
    expect("delete head (index 0)");
    ll_print(&int_list, print_int);

    ll_delete(&int_list, ll_size(&int_list) - 1);
    expect("delete tail (index 4)");
    ll_print(&int_list, print_int);


    section("INT LIST: pop_back / pop_front");

    void* popped = ll_pop_back(&int_list);
    expect("pop_back returns");
    if (popped) printf("%d\n", *(int*)popped); else printf("NULL\n");

    expect("list after pop_back");
    ll_print(&int_list, print_int);

    popped = ll_pop_front(&int_list);
    expect("pop_front returns");
    if (popped) printf("%d\n", *(int*)popped); else printf("NULL\n");

    expect("list after pop_front");
    ll_print(&int_list, print_int);


    section("INT LIST: reverse");

    expect("before reverse");
    ll_print(&int_list, print_int);

    ll_reverse(&int_list);
    expect("after reverse");
    ll_print(&int_list, print_int);

    ll_free(&int_list);


    /* ---- DOUBLE LIST ---- */
    section("DOUBLE LIST");

    LinkedList double_list = ll_create();

    double p = 3.14, q = 2.72, r = 1.41;
    ll_push_back(&double_list, &p);
    ll_push_back(&double_list, &q);
    ll_push_back(&double_list, &r);
    expect("push_back 3 doubles");
    ll_print(&double_list, print_double);

    popped = ll_pop_back(&double_list);
    expect("pop_back returns");
    if (popped) printf("%.2f\n", *(double*)popped); else printf("NULL\n");

    expect("after pop_back");
    ll_print(&double_list, print_double);

    ll_free(&double_list);


    /* ---- CHAR LIST ---- */
    section("CHAR LIST");

    LinkedList char_list = ll_create();

    char ch[] = {'h', 'e', 'l', 'l', 'o'};
    for (int i = 0; i < 5; i++) ll_push_back(&char_list, &ch[i]);
    expect("push_back h,e,l,l,o");
    ll_print(&char_list, print_char);

    char excl = '!';
    ll_insert(&char_list, ll_size(&char_list), &excl);
    expect("insert '!' at tail");
    ll_print(&char_list, print_char);

    ll_delete(&char_list, 2);
    expect("delete index 2");
    ll_print(&char_list, print_char);

    ll_reverse(&char_list);
    expect("reverse");
    ll_print(&char_list, print_char);

    ll_free(&char_list);


    /* ---- STRING LIST ---- */
    section("STRING LIST");

    LinkedList str_list = ll_create();

    // strings are already pointers so push directly, no & needed
    ll_push_back(&str_list, "hello");
    ll_push_back(&str_list, "world");
    ll_push_back(&str_list, "foo");
    expect("push_back 3 strings");
    ll_print(&str_list, print_string);

    ll_push_front(&str_list, "start");
    expect("push_front \"start\"");
    ll_print(&str_list, print_string);

    ll_delete(&str_list, 2);
    expect("delete index 2");
    ll_print(&str_list, print_string);

    popped = ll_pop_front(&str_list);
    expect("pop_front returns");
    if (popped) printf("\"%s\"\n", (char*)popped); else printf("NULL\n");

    expect("after pop_front");
    ll_print(&str_list, print_string);

    ll_free(&str_list);


    /* ---- EDGE CASES ---- */
    section("EDGE CASES");

    LinkedList empty = ll_create();

    expect("pop from empty list");
    popped = ll_pop_back(&empty);
    if (popped) printf("%d\n", *(int*)popped); else printf("NULL\n");

    expect("delete from empty list");
    printf("%d (error code)\n", ll_delete(&empty, 0));

    // single node then pop
    int solo = 42;
    ll_push_back(&empty, &solo);
    popped = ll_pop_back(&empty);
    expect("single node pop_back");
    if (popped) printf("%d\n", *(int*)popped); else printf("NULL\n");

    expect("list empty after pop");
    if (ll_size(&empty) == 0) printf("NULL (empty)\n"); else ll_print(&empty, print_int);

    // out of bounds insert
    int x = 7;
    expect("insert out of bounds");
    printf("%d (error code)\n", ll_insert(&empty, 99, &x));

    ll_free(&empty);

    return 0;
}