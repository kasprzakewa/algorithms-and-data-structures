//Ewa Kasprzak 272356

#ifndef ERR_H
#define ERR_H

#include <stdio.h>


typedef enum
{
    LIFO_OK = 0,
    LIFO_INIT_ERR,
    LIFO_PUSH_ERR,
    LIFO_POP_ERR,
    LIFO_EMPTY,
    LIFO_FREE_ERR,
    LIFO_ERR_COUNT
} lifo_err_t;

typedef enum
{
    FIFO_OK = 0,
    FIFO_INIT_ERR,
    FIFO_PUSH_ERR,
    FIFO_POP_ERR,
    FIFO_EMPTY,
    FIFO_FREE_ERR,
    FIFO_ERR_COUNT
} fifo_err_t;

void handle_lifo_err(lifo_err_t err[]);
void handle_fifo_err(fifo_err_t err[]);

#endif