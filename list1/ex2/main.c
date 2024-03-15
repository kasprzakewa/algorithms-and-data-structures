//Ewa Kasprzak 272356

#include "main.h"

int main(void)
{
    err_list_tuple_t list_err[LIST_ERR_COUNT];
    handle_list_tuple_err(list_test(list_err));
    
    printf("\n");
    printf("--------------------------\n");
    printf("\n");

    err_tuple_t search_err[LIST_ERR_COUNT];
    handle_tuple_err(search(search_err));

    return 0;
}

err_list_tuple_t* list_test(err_list_tuple_t err[])
{
    list_t list1;
    list_t list2;
    size_t size;
    
    for(int i = 0; i < LIST_ERR_COUNT; i++)
    {
        err[i].list1_err = LIST_OK;
        err[i].list2_err = LIST_OK;
    }

    err[LIST_INIT_ERR].list1_err |= list_init(&list1);
    err[LIST_INIT_ERR].list1_err |= list_init(&list2);

    for (int i = 10; i < 20; i++)
    {
        err[LIST_INSERT_ERR].list1_err |= insert(&list1, i);
    }

    print_list(&list1);
    size = list1.size;
    printf("list1 size: %ld\n", size);
    printf("\n");

    for (int i = 20; i < 30; i++)
    {
        err[LIST_INSERT_ERR].list2_err |= insert(&list2, i);
    }

    print_list(&list2);
    size = list2.size;
    printf("list2 size: %ld\n", size);
    printf("\n");

    err[LIST_MERGE_ERR].list1_err |= merge(&list1, &list2);
    err[LIST_MERGE_ERR].list2_err |= err[LIST_MERGE_ERR].list1_err;
    print_list(&list1);
    size = list1.size;
    printf("list size after merge: %ld\n", size);
    
    err[LIST_FREE_ERR].list1_err |= list_free(&list1);
    err[LIST_FREE_ERR].list2_err |= err[LIST_FREE_ERR].list1_err;
    print_list(&list1);
    size = list1.size;
    printf("list size after free: %ld\n", size);
    printf("\n");

    return err;
}

err_tuple_t* search(err_tuple_t err[])
{
    list_t list;
    int array[100000];
   

    for (int i = 0; i < LIST_ERR_COUNT; i++)
    {
        err[i].list_err = LIST_OK;
        err[i].file_err = FILE_OK;
    }

    err[LIST_INIT_ERR].list_err |= list_init(&list);

    srand(time(0));
    for (int i = 0; i < 100000; i++)
    {
        int j = rand() % 100001;
        array[i] = j;
    }

    for (int i = 0; i < 10000; i++)
    {
        err[LIST_INSERT_ERR].list_err |= insert(&list, array[i]);
    }
    

    FILE *list_search_file = fopen("list_search.csv", "w");
    FILE *out_of_list_file = fopen("out_of_list.csv", "w");

    if (list_search_file == NULL || out_of_list_file == NULL) 
    {
        printf("Error opening file!\n");
        err[LIST_FILE_ERR].file_err |= FILE_ERR;
        return err;
    }

    printf("counting list_search for:\n");
    for (int k = 0; k < 50; k++)
    {
        printf("k = %d:           ", k);
        double list_search_result = check_list_search(&list, array);
        printf("%f\n", list_search_result);
        fprintf(list_search_file, "%f\n", list_search_result);
    }
    printf("\n");

    printf("counting out_of_list_search for:\n");
    for (int k = 0; k < 50; k++)
    {
        printf("k = %d:           ", k);
        float out_of_list_search_result = check_out_of_list_search(&list, 100000);
        printf("%f\n", out_of_list_search_result);
        fprintf(out_of_list_file, "%f\n", out_of_list_search_result);
    }
    printf("\n");

    fclose(list_search_file);
    fclose(out_of_list_file);

    err[LIST_FREE_ERR].list_err |= list_free(&list);

    return err;
}  