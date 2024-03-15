//Ewa Kasprzak 272356

#ifndef FIFO_H 
#define FIFO_H

#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "err.h"

typedef struct fifo_node_t
{
    int value;
    struct fifo_node_t *next;
} fifo_node_t;

typedef struct fifo_t
{
    fifo_node_t *head;
    fifo_node_t *tail;
} fifo_t;


fifo_err_t fifo_init(fifo_t *fifo);
fifo_err_t fifo_push(fifo_t *fifo, int value);
fifo_err_t fifo_pop(fifo_t *fifo);
fifo_err_t fifo_free(fifo_t *fifo);

#endif