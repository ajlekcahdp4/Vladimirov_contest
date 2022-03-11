#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define EPSILON 1e-5f

struct equation {
    double a;
    double b;
    double c;
};

double Function (struct equation *eq, double x);
int sign (struct equation *eq, double x1, double x2);
double FindRoot (double left_b, double right_b, struct equation *eq);


double Function (struct equation *eq, double x)
{
    return eq->a * x * x * sin (x) + eq->b * x * cos(x) + eq->c;
}

int sign (struct equation *eq, double x1, double x2)
{
    double y1, y2 = 1.0;
    y1 = Function (eq, x1);
    y2 = Function (eq, x2);
    
    if (signbit (y1) != signbit (y2))
        return -1;
    else
        return 0;
}

double FindRoot (double left_b, double right_b, struct equation *eq)
{
    double new_b = (left_b + right_b) / 2;

    

    while (fabs (left_b - right_b) - EPSILON > 0)
    {
        new_b = (left_b + right_b) / 2;

        if (fabs(Function (eq, new_b)) < EPSILON) //нашли корень
        {
            return new_b;
        }

        if (sign (eq, left_b, new_b) < 0)
            right_b = new_b;
        else
            left_b = new_b;
    }

    return new_b;
}

int main ()
{
    double N = NAN;
    int res = 0;
    struct equation *eq = calloc (1, sizeof (struct equation));
    assert (eq);

    res = scanf ("%lf %lf %lf %lf", &eq->a, &eq->b ,&eq->c ,&N);
    assert (res == 4);

    printf ("%.5g\n", FindRoot (-N, N, eq));



    return 0;
}