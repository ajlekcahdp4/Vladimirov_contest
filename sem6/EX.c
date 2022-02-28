#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

void ShowBin (float x)
{
    int *x_int = 0;
    float *x_float = calloc (1, sizeof (float));
    int *mask  = calloc (1, sizeof (int));
    assert (x_float);
    assert (mask);

    *x_float = x;
    x_int = (int*)x_float;

    for (int i = 31; i >= 0; i--)
    {
        *mask = 1 << i;
        if (*x_int & *mask)
            printf ("1 ");
        else
            printf ("0 ");
        if (i == 31 || i == 23)
            printf ("| ");
    }

    putchar('\n');

    free (mask);
    free (x_float);
}


float ReversOddB (float x)
{
    float res = 0;
    int* x_inv_int = 0;
    float *x_inv = calloc (1, sizeof (float));
    int *mask  = calloc (1, sizeof (int));
    assert (x_inv);
    assert (mask);
    
    *x_inv = x;
    x_inv_int = (int*)x_inv;

    for (int i = 0; i < 23; i++)
    {
        if (i % 2)
        {
            *mask = 1 << i;
            if (*x_inv_int & *mask)
                *x_inv_int = *x_inv_int & ~(*mask);
            else
                *x_inv_int = *x_inv_int | *mask;
        }
    }
    x_inv = (float*)x_inv_int;
    res = *x_inv;

    free (mask);
    free (x_inv);

    return res;
}

int main ()
{
    float numb = NAN;
    scanf ("%f", &numb);
    printf ("%.5f\n", ReversOddB (numb));

    return 0;
}