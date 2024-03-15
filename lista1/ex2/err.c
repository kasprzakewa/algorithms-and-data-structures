//Ewa Kasprzak 272356

#include "err.h"

void handle_list_err(list_err_t* err)
{
    int count = 0;

    for (int i = 0; i < LIST_ERR_COUNT; i++)
    {
        if (err[i] != LIST_OK)
        {
            switch (err[i])
            {
                case 1:
                    printf("List initialization error\n");
                    break;
                case 2:
                    printf("Memory allocation error\n");
                    break;
                case 3:
                    printf("List insertion error\n");
                    break;
                case 4:
                    printf("List merge error\n");
                    break;
                case 5:
                    printf("List free error\n");
                    break;
                default:
                    printf("Unknown error = %d\n", err[i]);
                    break;
            } 
            count++;
        }
    }

    if (count == 0)
    {
        printf("List OK\n");
    }
}

void handle_file_err(file_err_t* err)
{
    int count = 0;

    for (int i = 0; i < LIST_ERR_COUNT; i++)
    {
        if (err[i] != FILE_OK)
        {
            switch (err[i])
            {
                case 1:
                    printf("File error\n");
                    break;
                default:
                    printf("Unknown error = %d\n", err[i]);
                    break;
            }
            count++;
        }
    }

    if (count == 0)
    {
        printf("File OK\n");
    }
}

void handle_tuple_err(err_tuple_t* err)
{
    handle_list_err(&err->list_err);
    handle_file_err(&err->file_err);
}

void handle_list_tuple_err(err_list_tuple_t* err)
{
    handle_list_err(&err->list1_err);
    handle_list_err(&err->list2_err);
}