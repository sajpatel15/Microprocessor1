
unsigned int a;
unsigned short *p;

unsigned short int temp1;
unsigned short int temp2;

void main(void){

    a =0xF12A0CB5;
    p=&a;

    temp1 = *p;
    temp2 = *(p+1);

    *p = temp2;
    *(p+1) = temp1;




    while(1);
}
