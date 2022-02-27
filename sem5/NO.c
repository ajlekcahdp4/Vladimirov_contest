#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Node_t {
    struct Node_t* l;
    struct Node_t* r;
    int data;
}Node_t;


Node_t *LeftInsert (Node_t* cur, int data)
{
    Node_t* prev_l = 0;
    assert(cur);
    prev_l = cur->l;

    cur->l = calloc (1, sizeof (Node_t));
    cur->l->data = data; 
    cur->l->l = prev_l;
    return cur->l;
}

Node_t *RightInsert (Node_t* cur, int data)
{
    Node_t* prev_r = 0;
    assert(cur);
    prev_r = cur->r;

    cur->r = calloc (1, sizeof (Node_t));
    cur->r->data = data; 
    cur->r->r = prev_r;
    return cur->r;
}

Node_t* TreeInit (int data)
{
    Node_t* node = calloc (1, sizeof(Node_t));
    assert (node);
    node->data = data;
    return node;
}

int *Input (int N)
{
    int *inserts = calloc (N, sizeof(int));

    for (int i = 0; i < N; i++)
        scanf ("%d", inserts + i);
    return inserts;
}

Node_t *FillTree (int N, int *inserts, Node_t *top, int *ip)
{
    //printf("ip = %d\n", *ip);
    Node_t *cur = top;
    if (cur == 0)
    {
        cur = TreeInit (inserts[0]);
        top = cur;
        *ip = 1;
    }
    else if (*ip < N)
    {
        //printf("inserts[*ip] = %d\n", inserts[*ip]);
        while ((inserts [*ip] < cur->data && cur->l) || (inserts [*ip] > cur->data && cur->r))
        {
            while (inserts[*ip] < cur->data && cur->l != 0)
                cur = cur->l;
            while (inserts[*ip] > cur->data && cur->r != 0)
                cur = cur->r;
        }
        //printf("cur->data = %d\n", cur->data);
        if (inserts[*ip] < cur->data)
        {
            //printf("insert left to %d\n", cur->data);
            cur->l = TreeInit (inserts[*ip]);
        }
        else
        {
            //printf ("insert right to %d\n", cur->data);
            cur->r = TreeInit (inserts[*ip]);
        }
        *ip += 1;
        //printf("\n\n");
    }
    if (*ip < N)
        FillTree (N, inserts, top, ip);
    return top;
}

void NormTreePrint (Node_t* top, int N, int* cnt)
{
    assert(top);
    printf("1 ");
    *cnt += 1;
    if (top->l != 0)
    {
        NormTreePrint (top->l, N, cnt);
    }
    else
    {
        printf("0 ");
        *cnt += 1;
    }

    if(top->r != 0)
    {
        NormTreePrint(top->r, N, cnt);
    }
    else
    {
        if (*cnt < 2*N)
        {
            *cnt += 1;
            printf("0 ");
        }
    }
}


void DeleteTree (Node_t* top)
{
    assert(top);
    if (top->l != 0)
        DeleteTree (top->l);
    if (top->r != 0)
        DeleteTree (top->r);
    free (top);
}

void PreorderPrint (Node_t* top)
{
    Node_t* cur = 0;
    assert(top);

    cur = top;
    printf("%d ", cur->data);

    if (cur->l != 0)
    {
        PreorderPrint (cur->l);
    }
    if (cur->r != 0)
    {
        PreorderPrint (cur->r);
    }
}


void TreePrint (int size, Node_t* top, char* str)
{
    char* str_n = 0;
    Node_t* cur = 0;

    assert(top);
    assert (str);
    
    cur = top;
    printf("%s\n", str);

    if (cur->l != 0)
    {
        str_n = calloc (size*2, sizeof(char));
        assert(str_n);
        memcpy (str_n, str, strlen (str));
        strcat (str_n, ".1");
        TreePrint (size, cur->l, str_n);
        free(str_n);
    }
    if (cur->r != 0)
    {
        str_n = calloc (size*2, sizeof(char));
        assert (str_n);
        memcpy (str_n, str, strlen (str));
        strcat (str_n, ".2");
        TreePrint (size, cur->r, str_n);
        free(str_n);
    }
}

int main ()
{
    int N = 0;
    int cnt = 0;
    int ip = 0;
    int *inserts = 0;
    Node_t *top = 0;

    assert(scanf ("%d", &N));
    inserts = Input (N);

    top = FillTree  (N, inserts, top, &ip);

    printf("%d ", N);
    NormTreePrint (top, N, &cnt);
    PreorderPrint (top);
    putchar ('\n');


    DeleteTree (top);
    free (inserts);
    return 0;
}