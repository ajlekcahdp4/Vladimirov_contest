#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <fenv.h>

int main ()
{
    int a, b, res = 0;
    float x = NAN;
    unsigned int_x_d, int_x_u = 0;
    


    res = scanf ("%d", &a);
    assert(res);

    res = scanf ("%d", &b);
    assert (res); 
    
    

    fesetround (FE_DOWNWARD);
    x = (float)a/(float)b;
    memcpy (&int_x_d, &x, sizeof (unsigned));
    

    
    fesetround (FE_UPWARD);
    if (x > 0)
        x = (float)a/(float)b;
    else if (x < 0)
        x = nextafterf (x, x - 1);
    memcpy (&int_x_u, &x, sizeof (unsigned));


    if (int_x_d == int_x_u)
    {
        printf ("0x%x ", (int_x_d >> 23) & 0xff);
        printf ("0x%x ", int_x_d & 0x7fffff);
    }
    else
    {
        printf ("0x%x ", (int_x_d >> 23) & 0xff);
        printf ("0x%x ", int_x_d & 0x7fffff);

        printf ("0x%x ", (int_x_d >> 23) & 0xff);
        printf ("0x%x ", int_x_u & 0x7fffff);
    }

    return 0;
}