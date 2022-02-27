#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void ShowBin (float x)
{
    int *x_float = calloc (1, sizeof (int));
    int *mask  = calloc (1, sizeof (int));
    assert (x_float);
    assert (mask);

    *x_float = x;
    int *x_int = (int*)x_float;


    for (int i = 0; i < 32; i++)
    {
        *mask = 1 << i;
        printf ("%d ", *x_int & *mask);
    }

    putchar('\n');
    
    free (mask);
    free (x_float);

}


float ReversOddB (float x)
{
    float *x_inv = calloc (1, sizeof (float));
    int *mask  = calloc (1, sizeof (int));
    assert (x_inv);
    assert (mask);
    
    *x_inv = x;
    int* x_inv_int = (int*)x_inv;

    for (int i = 0; i < 23; i++)
    {//                           0F000000 -> 
        if (i % 2 == 0)
        {
            *mask = 1 << i;
            if (*x_inv_int & *mask)
                *x_inv_int = *x_inv_int & ~(*mask);
            else
                *x_inv_int = *x_inv_int | *mask;
        }
    }
    x_inv = (float*)x_inv_int;

    free (mask);
    free (x_inv);

    return *x_inv;
}

int main ()
{

    printf ("%.5f\n", ReversOddB (1.0));
    ShowBin (1.0);
    return 0;
}