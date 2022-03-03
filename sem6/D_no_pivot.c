#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define EPSILON (float)0.0001
#define NULL_FLOAT (float)0.0

float** MatrixInit   (size_t N);
int     Gauss_Jordan (float **Matrix, size_t N);
void    Elimination  (float** Matrix, size_t N, size_t row, size_t col);
void    DeleteMatrix (float **Matrix, size_t N);
int     FloatCompr   (const float x, const float y, float EPS);
int     DiagonalDet  (float **Matrix, size_t N);
void    PrintMatrix (float **Matrix, size_t N);

int main ()
{
    size_t N = 0;
    int res = 0;
    float **Matrix = 0;

    res = scanf ("%lu", &N);
    assert (res);

    Matrix = MatrixInit (N);
    printf ("%d\n", Gauss_Jordan (Matrix, N));
    //PrintMatrix (Matrix, N);
    
    DeleteMatrix (Matrix, N);
    return 0;
}


int Gauss_Jordan (float** Matrix, size_t N)
{
    int det  = 0;
    size_t row = 0;
    size_t col = 0;
    float *temp_row = 0;
    for (col = 0; col < N; col++)
    {
        //PrintMatrix (Matrix, N);
        row = col;
        while (row < N && FloatCompr(Matrix[row][col], NULL_FLOAT, EPSILON) == 0)
            row += 1;

        if (row == N)
            row -= 1;

        if (FloatCompr (Matrix[row][col], NULL_FLOAT, EPSILON) != 0)
        {
            temp_row = Matrix[col];
            Matrix[col] = Matrix[row];
            Matrix[row] = temp_row;

            for (row = 0; row < N; row++)
                if (row != col)
                    Elimination (Matrix, N, row, col);
        }
    }

    det = DiagonalDet (Matrix, N);

    return det;
}
/*
1 1 1 0
-1 2 1 0
1 4 1 0
0 0 0 3


1 1 1 0


*/
void Elimination (float** Matrix, size_t N, size_t row, size_t col)
{
    float k  = NULL_FLOAT;
    k = Matrix[row][col] / Matrix[col][col];
    for (size_t cur_col = col; cur_col < N; cur_col++)
    {
        Matrix[row][cur_col] -= k * Matrix[col][cur_col];
    }
}

int FloatCompr (const float x, const float y, float EPS) //0 if equal
{
    return fabs(x - y) > EPS;
}

int DiagonalDet  (float **Matrix, size_t N)
{
    float det = 1.0;

    for (size_t i = 0; i < N; i++)
        det *= Matrix[i][i];
    
    return (int)rint(det);
}



void PrintMatrix (float **Matrix, size_t N)
{
    for (size_t row = 0; row < N; row++)
    {
        for (size_t col = 0; col < N; col++)
            printf ("%+.2f ", Matrix[row][col]);
        printf ("\n");
    }
    printf ("\n");
}

float** MatrixInit (size_t N)
{
    int res = 0;
    float** Matrix = 0;
    assert (N);
    Matrix = calloc (N, sizeof (float*));
    assert (Matrix);

    for (size_t i = 0; i < N; i++)
    {
        Matrix[i] = calloc (N, sizeof (float));
        assert (Matrix[i]);
    }

    for (size_t row = 0; row < N; row++)
        for (size_t col = 0; col < N; col++)
        {
            res = scanf ("%f", Matrix[row] + col);
            assert (res);
        }
    return Matrix;
}



void DeleteMatrix (float** Matrix, size_t N)
{
    for (size_t i = 0; i < N; i++)
        free (Matrix[i]);
    free (Matrix);
}

