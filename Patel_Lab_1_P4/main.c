#define N 50

int i;

int max = -2147483648;
int second_max = -2147483648;

int D[N] = { 87, 81, 92, 48, 49, 68, 37, 19, 51, 60, 61, 42, 77, 44, 56, 82, 43,
             25, 26, 52, 58, 8, 3, 75, 94, 24, 23, 98, 30, 68, 5, 13, 83, 73,
             37, 12, 28, 84, 11, 42, 65, 38, 73, 28, 75, 40, 44, 88, 95, 82 };

void main(){

    for (i = 0; i < N; i++){
        if (D[i] > max)
            max = D[i];
    }

    for (i = 0; i < N; i++){
        if (D[i] > second_max && D[i] != max)
            second_max = D[i];
    }

    *(D + N) = second_max;

    while (1);
}
