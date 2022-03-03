//Выбираем в качестве пивота наибольший элемент в подматрице
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define EPSILON (double)0.000000000001
#define NULL_DOUBLE (double)0.0

struct coordinates {
    size_t row;
    size_t col;
};

double** MatrixInit   (size_t N);
int      Gauss_Jordan (double **Matrix, size_t N);
void     Elimination  (double** Matrix, size_t N, size_t col);
void     DeleteMatrix (double **Matrix, size_t N);
int      DoubleCompr  (const double x, const double y, double EPS);
int      DiagonalDet  (double **Matrix, size_t N);
void     PrintMatrix  (double **Matrix, size_t N);
void     SwitchRows   (double **Matrix, size_t N, size_t row1, size_t row2);
void     SwitchCols   (double **Matrix, size_t N, size_t col1, size_t col2);

struct coordinates *MaxElemInMatrix (double** Matrix, size_t n, size_t N);

int main ()
{
    size_t N = 0;
    int res = 0;
    double **Matrix = 0;

    res = scanf ("%lu", &N);
    assert (res);

    Matrix = MatrixInit (N);
    printf ("%d\n", Gauss_Jordan (Matrix, N));
    
    DeleteMatrix (Matrix, N);
    return 0;
}


int Gauss_Jordan (double** Matrix, size_t N)
{
    int    det  = 1;
    size_t row  = 0;
    size_t col  = 0;
    size_t Prow = 0;
    size_t Pcol = 0;
    while (col < N - 1 && row < N - 1)
    {
        struct coordinates *coord = MaxElemInMatrix (Matrix, col, N);
        Prow = coord->row;
        Pcol = coord->col;
        free (coord);

        if (DoubleCompr (Matrix[Prow][Pcol], NULL_DOUBLE, EPSILON) == 0)
            return 0;
        if (row != Prow)
        {
            SwitchRows (Matrix, N, row, Prow);
            det *= -1;
        }
        if (col != Pcol)
        {
            SwitchCols (Matrix, N, col, Pcol);
            det *= -1;
        }
        Elimination (Matrix, N, col);

        row++;
        col++;
    }
    det *= DiagonalDet (Matrix, N);

    return det;
}


void Elimination (double** Matrix, size_t N, size_t col)
{
    double k  = NULL_DOUBLE;

    for (size_t row = col; row < N; row++)
    {
        if (row != col)
        {
            k = Matrix[row][col] / Matrix [col][col];
            for (size_t cur_col = col; cur_col < N; cur_col++)
            {
                Matrix[row][cur_col] -= k * Matrix[col][cur_col];
            }
        }
    }
}

void SwitchRows (double **Matrix, size_t N, size_t row1, size_t row2)
{
    if (row1 < N && row2 < N)
    {
        double *temp_row = Matrix[row1];
        Matrix[row1] = Matrix[row2];
        Matrix[row2] = temp_row;
    }
}

void SwitchCols (double **Matrix, size_t N, size_t col1, size_t col2)
{
    double temp = NAN;
    if (col1 < N && col2 < N)
    {
        for (size_t row = 0; row < N; row++)
        {
            temp = Matrix[row][col1];
            Matrix[row][col1] = Matrix[row][col2];
            Matrix[row][col2] = temp;
        }
    }
}

struct coordinates *MaxElemInMatrix (double** Matrix, size_t n, size_t N)
{
    double max = NULL_DOUBLE;
    struct coordinates *coord = calloc (1, sizeof (struct coordinates));

    for (size_t row = n; row < N; row++)
        for (size_t col = n; col < N; col++)
        {
            if (DoubleCompr (fabs(Matrix[row][col]), max, EPSILON) > 0)
            {
                max = fabs(Matrix[row][col]);
                coord->col = col;
                coord->row = row;
            }
        }    
    

    return coord;
}

int DoubleCompr (const double x, const double y, double EPS) //0 if equal
{
    if (fabs (x - y) < EPS)
        return 0;
    if (x - y < 0)
        return -1;
    return 1;
}



int DiagonalDet  (double **Matrix, size_t N)
{
    double det = 1.0;

    for (size_t i = 0; i < N; i++)
        det *= Matrix[i][i];
    return (int)rint(det);
}



void PrintMatrix (double **Matrix, size_t N)
{
    for (size_t row = 0; row < N; row++)
    {
        for (size_t col = 0; col < N; col++)
            printf ("%+.2f ", Matrix[row][col]);
        printf ("\n");
    }
    printf ("\n");
}

double** MatrixInit (size_t N)
{
    int res = 0;
    double** Matrix = 0;
    assert (N);
    Matrix = calloc (N, sizeof (double*));
    assert (Matrix);

    for (size_t i = 0; i < N; i++)
    {
        Matrix[i] = calloc (N, sizeof (double));
        assert (Matrix[i]);
    }

    for (size_t row = 0; row < N; row++)
        for (size_t col = 0; col < N; col++)
        {
            res = scanf ("%lf", Matrix[row] + col);
            assert (res);
        }
    return Matrix;
}



void DeleteMatrix (double** Matrix, size_t N)
{
    for (size_t i = 0; i < N; i++)
        free (Matrix[i]);
    free (Matrix);
}

