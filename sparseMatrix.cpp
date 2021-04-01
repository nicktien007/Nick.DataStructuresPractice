#include <iostream>

using namespace std;

#define MAX_TERMS 9

typedef struct Term {
    int col;
    int row;
    int value;
};

Term a[MAX_TERMS];
Term b[MAX_TERMS];

void initA();

void transpose(Term a[], Term b[]);

void showArry(Term arr[]) {
    for (int i = 0; i < MAX_TERMS; ++i) {
        printf("row=%d,col=%d,val=%d \n", arr[i].row, arr[i].col, arr[i].value);
    }
    printf("==========================\n");
}

int main() {

    initA();
    showArry(a);

    transpose(a, b);

    showArry(b);

    return 0;
}

void initA() {
    a[0].row = 6;
    a[0].col = 6;
    a[0].value = 8;

    a[1].row = 0;
    a[1].col = 0;
    a[1].value = 15;

    a[2].row = 0;
    a[2].col = 3;
    a[2].value = 22;

    a[3].row = 0;
    a[3].col = 5;
    a[3].value = -15;

    a[4].row = 1;
    a[4].col = 1;
    a[4].value = 11;

    a[5].row = 1;
    a[5].col = 2;
    a[5].value = 3;

    a[6].row = 2;
    a[6].col = 3;
    a[6].value = -6;

    a[7].row = 4;
    a[7].col = 0;
    a[7].value = 91;

    a[8].row = 5;
    a[8].col = 2;
    a[8].value = 28;
}

/**
 * 矩陣轉置
 * @param a
 * @param b
 */
void transpose(Term a[], Term b[]) {
    int n, i, j, current_b;

    n = a[0].value;
    b[0].row = a[0].row;
    b[0].col = a[0].col;
    b[0].value = n;

    if (n <= 0)
        return;     //非零矩陣

    current_b = 1;
    for (i = 0; i < a[0].col; i++) {
        for (j = 1; j <= n; j++) {

            if (a[j].col == i) {
                //元素在目前col裡，把它加入b中
                b[current_b].row = a[j].col;
                b[current_b].col = a[j].row;
                b[current_b].value = a[j].value;
                current_b++;
            }
        }
    }
}
