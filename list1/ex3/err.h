//Ewa Kasprzak 272356

#ifndef ERR_H
#define ERR_H

#include <stdio.h>

typedef enum list_err_t
{
    LIST_OK,
    LIST_INIT_ERR,
    LIST_ERR_MALLOC,
    LIST_INSERT_ERR,
    LIST_MERGE_ERR,
    LIST_FREE_ERR,
    LIST_FILE_ERR,
    LIST_ERR_COUNT
} list_err_t;

typedef enum file_err_t
{
    FILE_OK,
    FILE_ERR,
    FILE_ERR_COUNT
} file_err_t;

typedef struct err_tuple_t
{
    list_err_t list_err;
    file_err_t file_err;
} err_tuple_t;

typedef struct err_list_tuple_t
{
    list_err_t list1_err;
    list_err_t list2_err;
} err_list_tuple_t;

void handle_file_err(file_err_t* file_err);
void handle_list_err(list_err_t* list_err);
void handle_tuple_err(err_tuple_t* tuple_err);
void handle_list_tuple_err(err_list_tuple_t* err);

#endif 