#include <Math.h>

double y[361] = {0};
int i;


void main(void){
    for(i = 0; i < 361; i++)
        y[i] = cos(i);

    while(1);
}
