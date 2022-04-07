int isprime (int x)
{
    int b = 2;
    if (!(x & 1))
        return 0;
    while (b < x)
    {
        if (x % b == 0)
            return 0;
    }
    return 1;
}
int main ()
{
    int x = 5;

    isprime (x);
    return 0;
}