//Ewa Kasprzak 272356

#ifndef LIST_H
#define LIST_H

#pragma once

#include <stdlib.h>
#include <stdint.h>
#include "err.h"

typedef struct list_node_t
{
    int value;
    struct list_node_t *next;
    struct list_node_t *prev;
} list_node_t;

typedef struct list_t
{
    list_node_t *head;
    size_t size;
}list_t;

list_err_t list_init(list_t *list);
list_err_t list_free(list_t *list1);
list_node_t* create_node(int value);
list_err_t insert(list_t *list, int value);
list_err_t merge(list_t *list1, list_t *list2);
void print_list(list_t *list);
size_t forward_list_search(list_t *list, int value);
size_t backwards_list_search(list_t *list, int value);
float check_list_search(list_t *list, int array[]);
float check_out_of_list_search(list_t *list, int I);

#endif