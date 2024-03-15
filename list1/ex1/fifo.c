//Ewa Kasprzak 272356

#include "fifo.h"

fifo_err_t fifo_init(fifo_t *fifo) 
{
    if (fifo == NULL)
    {
        return FIFO_INIT_ERR;
    }
    fifo->head = NULL;
    fifo->tail = NULL;
    return FIFO_OK;
}

fifo_err_t fifo_push(fifo_t *fifo, int value)
{
    if (fifo == NULL)
    {
        return FIFO_PUSH_ERR;
    }

    fifo_node_t *new_node = malloc(sizeof(fifo_node_t));
    if (new_node == NULL)
    {
        return FIFO_PUSH_ERR;
    }

    new_node->value = value;
    new_node->next = NULL;

    if (fifo->head == NULL)
    {
        fifo->head = new_node;
        fifo->tail = new_node;
    }
    else
    {
        fifo->tail->next = new_node;
        fifo->tail = new_node;
    }

    return FIFO_OK;
}

fifo_err_t fifo_pop(fifo_t *fifo)
{
    if (fifo == NULL)
    {
        return FIFO_POP_ERR;
    }

    if (fifo->head == NULL)
    {
        return FIFO_EMPTY;
    }
    
    int value = fifo->head->value;
    printf("Popped value: %d\n", value);
    fifo->head = fifo->head->next;

    return FIFO_OK;
}

fifo_err_t fifo_free(fifo_t *fifo)
{
    if (fifo == NULL)
    {
        return FIFO_FREE_ERR;
    }

    fifo_node_t *current = fifo->head;
    fifo_node_t *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    fifo->head = NULL;
    fifo->tail = NULL;

    return FIFO_OK;
}