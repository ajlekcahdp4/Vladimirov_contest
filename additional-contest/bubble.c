void bsort (int *arr, int size)
{
    int *ptr;
    if ( size > 0 )
    {
        do
        {
            if ( size > 0 )
            {
                ptr = arr;
                do
                {
                    if ( ptr[0] > ptr[1] )
                    {
                        int holder = ptr[0];
                        ptr[0]     = ptr[1];
                        ptr[1]     = ptr[0];
                    }
                    ptr += 1;
                } while ( ptr != arr + size );
            }
            size -= 1;
        } while ( size );
    }
    return;
}