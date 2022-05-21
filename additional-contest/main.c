#include <assert.h>
#include <stdio.h>

void foo (int *arr, int size);

int main ()
{
    int arr[8];

    for ( int i = 0; i < 8; i++ )
    {
        scanf ("%d", arr + i);
    }

    foo (arr, 8);

    for ( int i = 0; i < 8; i++ )
        printf ("%d ", arr[i]);

    return 0;
}

#if 1
void foo (int *arr, int size)
{
    assert (arr);
    int array[4] = {2, 0, 6, 4};
    int third    = arr[2];
    int *ptr     = array;

    do
    {
        arr[*ptr] = arr[ptr[1]];
        ptr += 1;
    } while ( ptr != &array[3] );

    arr[4] = third;

    if ( size > 1 )
    {
        ptr = arr + 1;
        do
        {
            *ptr = *ptr + ptr[-1];
            ptr += 1;
        } while ( ptr != arr + size );
    }
}
#endif
