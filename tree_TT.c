#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

typedef struct Node_t {
    struct Node_t* l;
    struct Node_t* r;
    int data;
}Node_t;

Node_t * LeftInsert (Node_t* cur, int data)
{
    Node_t* prev_l = 0;
    assert(cur);
    prev_l = cur->l;

    cur->l = calloc (1, sizeof (Node_t));
    cur->l->data = data; 
    cur->l->l = prev_l;
    return cur->l;
}

Node_t * RightInsert (Node_t* cur, int data)
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
    node->data = data;
    return node;
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

void DeleteList (Node_t* top)
{
    assert(top);
    if (top->l != 0)
        DeleteList (top->l);
    if (top->r != 0)
        DeleteList (top->r);
    free (top);
}

int PosInInorder (int* inorder, int val)
{
    int pos = 0;
    while (inorder[pos] != val)
        pos++;
    return pos;
}

Node_t* FillTree (Node_t* node, int N, int* inorder, int* preorder, int* ip, int left_bord, int right_bord) 
//!Можно хранить граничные значения, между которыми в инордере мы находимся
{
    Node_t* cur = node;
    int cur_pos = 0;
    int next_pos = 0;
    if (cur == 0)
        cur = TreeInit(preorder[*ip]);

    cur_pos = PosInInorder (inorder, preorder[*ip]);
    
    if (*ip < N - 1)
        *ip += 1;

    next_pos = PosInInorder (inorder , preorder[*ip]);
    if (next_pos >= left_bord && next_pos < cur_pos)
    {
        cur->l = FillTree (cur->l, N, inorder, preorder, ip, left_bord, cur_pos);
    }
    if (*ip < N)
        next_pos = PosInInorder (inorder , preorder[*ip]);

    if (next_pos > cur_pos && next_pos <= right_bord)
    {
        cur->r = FillTree (cur->r, N, inorder, preorder, ip, cur_pos, right_bord);
    }
    /*В ином случае просто выходим из этой итерации рекурсии*/



    return cur;
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


int main ()
{
    
    //input=start=========================================
    int tree_size = 0;
    int* inorder = 0;
    int* preorder = 0;
    Node_t* top = 0;
    int ip = 0;
    int cnt = 0;

    scanf ("%d", &tree_size);

    inorder = calloc (tree_size, sizeof(int));
    preorder = calloc (tree_size, sizeof(int));
    
    for (int i = 0; i < tree_size; i++)
        scanf ("%d", preorder + i);
    for (int i = 0; i < tree_size; i++)
        scanf ("%d", inorder + i);
    //input=end===========================================
    
    
    top = FillTree (top, tree_size, inorder, preorder, &ip, 0, tree_size - 1);
    //TreePrint (tree_size, top, "1");
    
    printf("%d\n", tree_size);

    NormTreePrint (top, tree_size, &cnt);

    putchar('\n');
    for (int i = 0; i < tree_size; i++)
        printf("%d ", preorder[i]);
    putchar('\n');

    DeleteList (top);
    free (inorder);
    free (preorder);
    return 0;
}