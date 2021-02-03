

int y[512] = {0};
int i;

int square(int x){
    return x*x;
}

void main(void){
    for(i = 0; i < 512; i++)
	    y[i] = square(i);

	while(1);
}
