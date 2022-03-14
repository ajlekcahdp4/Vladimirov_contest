#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define EPSILON 1e-5

struct equation {
    double a;
    double b;
    double c;
};
double Function (struct equation *eq, double x)
{
    return eq->a * x * x * sin (x) + eq->b * x * cos(x) + eq->c;
}

double DifFunction (struct equation *eq, double x)
{
    return (eq->a * x * x + eq->b) * cos(x) + x * (2 * eq->a - eq->b) * sin (x);
}

int DoubleCmp (double x, double y)
{
    if (fabs (x - y) > EPSILON)
        return 1;
    return 0;
}

double Newton (struct equation *eq, double x)
{
    double f  = NAN;
    double df = NAN;
    double b  = NAN;
    double xi = x;
    f = Function (eq, xi);

    while (DoubleCmp (f, 0) != 0)
    {
        f = Function (eq, xi);
        df = DifFunction (eq, xi);    
        if (DoubleCmp (df, 0) == 0)
            return 0.0;
        b  = f - df * xi;

        xi = (-b) / (df);
    }
    return xi;
}


int main ()
{
    struct equation *eq = calloc (1, sizeof (struct equation));
    int res = 0;
    double x = NAN;

    res = scanf ("%lf %lf %lf", &eq->a, &eq->b, &eq->c);
    assert (res == 3);

    res = scanf ("%lf", &x);
    assert(res);

    printf ("%.5lf\n", Newton (eq, x));
    return 0;
}