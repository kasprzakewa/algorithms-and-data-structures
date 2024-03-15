//Ewa Kasprzak 272356

#include "list.h"

float check_out_of_list_search(list_t *list, int I)
{
    float cost = 0;
    for (int i = 0; i < 1000; i++)
    {
        int value = rand() % I + 1;
        cost += list_search(list, value);
    }

    return cost / 1000;
}

double check_list_search(list_t *list, int arr[])
{
    double cost = 0;
    for (int i = 0; i < 1000; i++)
    {
        int value = rand() % list->size;
        cost += list_search(list, arr[value]);
    }

    return cost / 1000;
}

size_t list_search(list_t *list, int value)
{
    list_node_t *tmp = list->head;
    size_t index = 0;

    if (list->size == 0)
    {
        return SIZE_MAX;
    }

    for (size_t i = 0; i < list->size; i++)
    {
        if (tmp->value == value)
        {
            return index;
        }
        else
        {
            tmp = tmp->next;
            index++;
        }
    }

    return index;
}

list_err_t list_init(list_t *list) 
{
    if (list == NULL)
    {
        return LIST_INIT_ERR;
    }

    list->head = NULL;
    list->size = 0;

    return LIST_OK;
}

list_node_t* create_node(int value) 
{
    list_node_t* new = (list_node_t*)malloc(sizeof(list_node_t));

    if (!new) 
    {
        printf("Lack of memory, cannot create new node.\n");
        return NULL;
    }

    new->value = value;
    new->next = new;
    return new;
}

list_err_t insert(list_t *list, int value)
{
    list_node_t* new = create_node(value);

    if (new == NULL) 
    {
        return LIST_INSERT_ERR;
    }

    if (list->head == NULL) 
    {
        list->head = new;
    } 
    else 
    {
        list_node_t* tmp = list->head;

        for (size_t i = 0; i < list->size - 1; i++) 
        {
            tmp = tmp->next;
        }

        tmp->next = new;
        new->next = list->head;
    }
    list->size++;

    return LIST_OK;
}

list_err_t merge(list_t *list1, list_t *list2) 
{
    if (list1->head == NULL) 
    {
        list1->head = list2->head;
    } 
    else if (list2->head != NULL) 
    {
        list_node_t* tmp1 = list1->head;
        while (tmp1->next != list1->head) 
        {
            tmp1 = tmp1->next;
        }

        list_node_t* tmp2 = list2->head;
        while (tmp2->next != list2->head) 
        {
            tmp2 = tmp2->next;
        }

        tmp1->next = list2->head;
        tmp2->next = list1->head;
    }

    list1->size += list2->size;

    list2->head = NULL;
    list2->size = 0;

    return LIST_OK;
}

list_err_t list_free(list_t *list1) 
{
    if (list1 == NULL || list1->head == NULL) 
    {
        return LIST_FREE_ERR;
    }
    
    list_node_t *tmp = list1->head;
    list_node_t *next = NULL;

    do 
    {
        next = tmp->next;
        free(tmp);
        tmp = next;
    } while (tmp != list1->head);

    list1->size = 0;

    return LIST_OK;
}

void print_list(list_t *list) 
{
    list_node_t* tmp = list->head;
    if (list->head == NULL) {
        printf("Lista jest pusta.\n");
        return;
    }

    for (size_t i = 0; i < list->size; i++) 
    {
        printf("%d ", tmp->value);
        tmp = tmp->next;
    }
    printf("\n");
}