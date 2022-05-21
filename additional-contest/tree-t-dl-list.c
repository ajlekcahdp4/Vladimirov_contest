#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct node_t
{
    struct node_t *left;
    struct node_t *right;
    int data;
};

// you need to implement this function
struct node_t *to_dlist (struct node_t *top);

int main ()
{
    int i, n, res, listn;
    struct node_t *tree;
    struct node_t *dlist;

    res = scanf ("%d", &n);
    assert (res == 1);

    // reading input data and creating a tree
    tree = (struct node_t *)calloc (n, sizeof (struct node_t));
    for ( i = 0; i < n; ++i )
    {
        scanf ("%d", &tree[i].data);
        if ( (i + 1) * 2 - 1 < n )
            tree[i].left = &tree[(i + 1) * 2 - 1];
        if ( (i + 1) * 2 < n )
            tree[i].right = &tree[(i + 1) * 2];
    }

    // calling to_dlist
    dlist = to_dlist (tree);

    // printing dlist and checking node addresses
    listn = 0;
    while ( dlist != NULL )
    {
        struct node_t *right;

        if ( (dlist < tree) || (dlist > tree + n) )
        {
            printf ("Error: new memory allocation is prohibited\n");
            abort ();
        }

        printf ("%d ", dlist->data);

        right = dlist->right;
        if ( right && (right->left != dlist) )
        {
            printf ("Error: resulting dlist is not connected\n");
            abort ();
        }

        dlist = right;
    }

    printf ("\n");
    free (tree);
    return 0;
}

struct node_t *get_head (struct node_t *tail);
void convert_node (struct node_t *node, struct node_t **last_node);   // pointer to poiner because we should change it's
                                                                      // value to current last node of the list

struct node_t *to_dlist (struct node_t *top)
{
    struct node_t *last_node = NULL;
    convert_node (top, &last_node);

    return get_head (last_node);
}

void convert_node (struct node_t *node, struct node_t **last_node)
{
    assert (node);
    assert (last_node);

    struct node_t *cur = node;

    if ( cur->left )
        convert_node (cur->left, last_node);

    cur->left = *last_node;

    if ( *last_node )
    {
        (*last_node)->right = cur;
    }

    *last_node = cur;

    if ( cur->right )
        convert_node (cur->right, last_node);
}

struct node_t *get_head (struct node_t *tail)
{
    if ( !tail )
        return NULL;
    while ( tail->left )
        tail = tail->left;
    return tail;
}