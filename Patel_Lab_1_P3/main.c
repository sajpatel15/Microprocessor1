int x = 2147483640;
int y = 17;
int z;
int n;
int i;
int result;

int factorial(int f)
{
    result = 1;

    for (i = 1; i <= f; i++)
    {
        if (f > 0 && result < 0)
        {
            result = -1;
            return -1;
        }
        else
        {
            result = result * i;
        }
    }

    return result;
}

void main(void)
{

    z = factorial(y);
    n = factorial(x);

    while (1);
}
