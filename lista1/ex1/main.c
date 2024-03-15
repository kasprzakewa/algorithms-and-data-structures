//Ewa Kasprzak 272356

#include "main.h"

int main(void)
{
    lifo_err_t lifo_err[LIFO_ERR_COUNT];
    printf("LIFO:\n");
    handle_lifo_err(lifo_test(lifo_err));

    printf("\n");
    printf("--------------------------\n");
    printf("\n");

    fifo_err_t fifo_err[FIFO_ERR_COUNT];
    printf("FIFO:\n");
    handle_fifo_err(fifo_test(fifo_err));

    return 0;
}

lifo_err_t* lifo_test(lifo_err_t err[])
{
    lifo_t lifo;

    for (int i = 0; i < LIFO_ERR_COUNT; i++)
    {
        err[i] = LIFO_OK;
    }

    err[LIFO_INIT_ERR] |= lifo_init(&lifo);

    for (int i = 0; i < 10; i++)
    {
        err[LIFO_PUSH_ERR] |= lifo_push(&lifo, i);
        printf("Pushed value: %d\n", i);
    }

    for (int i = 0; i < 10; i++)
    {
        err[LIFO_POP_ERR] |= lifo_pop(&lifo);
    }

    err[LIFO_FREE_ERR] |= lifo_free(&lifo);

    return err;
}

fifo_err_t* fifo_test(fifo_err_t err[])
{
    fifo_t fifo;

    for (int i = 0; i < FIFO_ERR_COUNT; i++)
    {
        err[i] = FIFO_OK;
    }

    err[FIFO_INIT_ERR] |= fifo_init(&fifo);

    for (int i = 0; i < 10; i++)
    {
        err[FIFO_PUSH_ERR] |= fifo_push(&fifo, i);
        printf("Pushed value: %d\n", i);
    }

    for (int i = 0; i < 10; i++)
    {
        err[FIFO_POP_ERR] |= fifo_pop(&fifo);
    }

    err[FIFO_FREE_ERR] |= fifo_free(&fifo);

    return err;
}

