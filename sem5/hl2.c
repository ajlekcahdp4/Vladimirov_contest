#include <stdio.h>
#include <stdlib.h>
#include "list/list.h"

int PowTwo (int N)
{
    int pow = 1;
    while (pow < N)
        pow *= 2;
    if (pow == N)
        return 1;
    return 0;
}
int loop_len(struct node_t* top)
{
    int len = 0;
    int N = 0;
    struct node_t* rab = top;
    struct node_t* tort = top;
    if (top == 0)
        return 0;
    while (rab->next != 0)
    {
        rab = rab->next;
        N += 1;
        len += 1;
        //printf("rab = %p, tort = %p, len = %d, N = %d\n", rab, tort, len, N);
        if (PowTwo(N))
        {
            tort = rab;
            len = 0;
        }
        else if (rab == tort)
            break;
    }
    if (rab->next == 0)
        len = 0;
    return len;
}

int main ()
{
    struct node_t* top = calloc(1, sizeof(struct node_t));
    CreateNode(top, 1);
    CreateNode(top->next, 2);
    CreateNode(top->next->next, 3);
    top->next->next->next = top;
    printf("%d\n", loop_len(top));
    return 0;
}


