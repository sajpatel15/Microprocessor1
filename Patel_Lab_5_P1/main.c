#include <math.h>

#define bitsize 12
float Vref = 3.6;
float Vin = 2.75;

float thresh;
float quantized = 0;

int count;
int bitval;

int bits[bitsize];
void main()
{
    Vref /= 2;
    thresh = Vref;
    for (count = 0; count < bitsize; count++)
    {
        Vref /= 2;
        if (Vin >= thresh)
        {
            bitval = 1;
            thresh += Vref;
        }
        else
        {
            bitval = 0;
            thresh -= Vref;
        }
        bits[count] = bitval;
        quantized += 2 * Vref * bitval;
    }
    int i, final;
    for (i = 0; i < 12; i++)
    {
        final += bits[(i)] * (pow(2, (11 - i)));
    }
    while (1);
}
