//Ewa Kasprzak 272356

#include "lifo.h"

lifo_err_t lifo_init(lifo_t *lifo)
{
    if (lifo == NULL)
    {
        return LIFO_INIT_ERR;
    }

    lifo->head = NULL;
    lifo->tail = NULL;

    return LIFO_OK;
}

lifo_err_t lifo_push(lifo_t *lifo, int value)
{
    if (lifo == NULL)
    {
        return LIFO_PUSH_ERR;
    }

    lifo_node_t *new_node = malloc(sizeof(lifo_node_t));
    if (new_node == NULL)
    {
        return LIFO_PUSH_ERR;
    }

    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = lifo->tail;

    if (lifo->head == NULL)
    {
        lifo->head = new_node;
        lifo->tail = new_node;
    }
    else
    {
        lifo->tail->next = new_node;
        lifo->tail = new_node;
    }

    return LIFO_OK;
}

lifo_err_t lifo_pop(lifo_t *lifo)
{
    if (lifo == NULL)
    {
        return LIFO_POP_ERR;
    }

    if (lifo->head == NULL)
    {
        return LIFO_EMPTY;
    }
    
    int value = lifo->tail->value;
    printf("Popped value: %d\n", value);
    lifo->tail = lifo->tail->prev;

    return LIFO_OK;
}

lifo_err_t lifo_free(lifo_t *lifo)
{
    if (lifo == NULL)
    {
        return LIFO_FREE_ERR;
    }

    lifo_node_t *current = lifo->head;
    lifo_node_t *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    lifo->head = NULL;
    lifo->tail = NULL;
    
    return LIFO_OK;
}