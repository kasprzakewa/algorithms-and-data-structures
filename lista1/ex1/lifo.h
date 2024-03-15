//Ewa Kasprzak 272356

#ifndef LIFO_H 
#define LIFO_H

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "err.h"

typedef struct lifo_node_t
{
    int value;
    struct lifo_node_t *next;
    struct lifo_node_t *prev;
} lifo_node_t;

typedef struct lifo_t
{
    lifo_node_t *head;
    lifo_node_t *tail;
} lifo_t;


lifo_err_t lifo_init(lifo_t *lifo);
lifo_err_t lifo_push(lifo_t *lifo, int value);
lifo_err_t lifo_pop(lifo_t *lifo);
lifo_err_t lifo_free(lifo_t *lifo);

#endif