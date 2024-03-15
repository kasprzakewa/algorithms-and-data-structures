//Ewa Kasprzak 272356

#include "err.h"

void handle_lifo_err(lifo_err_t err[]) 
{
    for (int i = 0; i < LIFO_ERR_COUNT; i++)
    {
        if (err[i] != LIFO_OK)
        {
            switch (i) 
            {
                case 1: 
                    printf("LIFO_INIT_ERR\n");
                    break;
                case 2: 
                    printf("LIFO_PUSH_ERR\n");
                    break;
                case 3: 
                    printf("LIFO_POP_ERR\n");
                    break;
                case 4: 
                    printf("LIFO_EMPTY\n");
                    break;
                case 5: 
                    printf("LIFO_FREE_ERR\n");
                    break;
                default: 
                    printf("UNKNOWN_ERROR = %d\n", err[i]);
                    break;
            }
        }
    }
}

void handle_fifo_err(fifo_err_t err[]) 
{
    for (int i = 0; i < FIFO_ERR_COUNT; i++)
    {
        if (err[i] != FIFO_OK)
        {
            switch (i) 
            {
                case 1: 
                    printf("FIFO_INIT_ERR\n");
                    break;
                case 2: 
                    printf("FIFO_PUSH_ERR\n");
                    break;
                case 3: 
                    printf("FIFO_POP_ERR\n");
                    break;
                case 4: 
                    printf("FIFO_EMPTY\n");
                    break;
                case 5: 
                    printf("FIFO_FREE_ERR\n");
                    break;
                default: 
                    printf("UNKNOWN_ERROR = %d\n", err[i]);
                    break;
            }
        }
    }
}