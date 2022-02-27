#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"
struct node_t* CreateNode (struct node_t* last, int data)
{
    last->next = calloc (1, sizeof(struct node_t));
    last->next->data = data;
    last->next->next = 0;
    return last->next;
}

void DeleteList (struct node_t* top)
{
    assert(top);
    struct node_t* cur_node = top;
    struct node_t* next_node = 0;
    while (cur_node->next != 0)
    {
        next_node = cur_node->next;
        cur_node = next_node;
    }
}