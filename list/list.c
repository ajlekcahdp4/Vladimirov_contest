#include <stdio.h>
#include <stdlib.h>
#include "list.h"
struct node_t* CreateNode (struct node_t* last, int data)
{
    last->next = calloc (1, sizeof(struct node_t));
    last->next->data = data;
}

void DeleteList (struct node_t* top)
{
    struct node_t* cur_node = top;
    struct node_t* next_node = top;
    while (cur_node->next != 0)
    {
        next_node = cur_node->next;
        free(cur_node);
        cur_node = next_node;
    }
    free(cur_node);
}