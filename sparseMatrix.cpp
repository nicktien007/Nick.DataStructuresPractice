#include <iostream>

using namespace std;

//#define MAX_TERMS 9
#define MAX_TERMS 6
#define COMPARE(x, y) ((x < y) ? -1: (x == y)? 0: 1)

typedef struct Term {
    int col;
    int row;
    int value;
};

Term a[MAX_TERMS];
Term b[MAX_TERMS];
Term d[MAX_TERMS];
Term newB[MAX_TERMS];


void initA();

void mmult(Term a[], Term b[], Term d[]);

void transpose(Term a[], Term b[]);

void fastTranspose(Term a[], Term b[]);

void showArry(Term arr[]);


void showArry(Term arr[]) {
    for (int i = 0; i < MAX_TERMS; ++i) {
        printf("row=%d,col=%d,val=%d \n", arr[i].row, arr[i].col, arr[i].value);
    }
    printf("==========================\n");
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

void initAA() {
    a[0].row = 3;
    a[0].col = 3;
    a[0].value = 4;

    a[1].row = 0;
    a[1].col = 0;
    a[1].value = 5;

    a[2].row = 1;
    a[2].col = 1;
    a[2].value = 11;

    a[3].row = 1;
    a[3].col = 2;
    a[3].value = 3;

    a[4].row = 2;
    a[4].col = 2;
    a[4].value = 2;

    a[5].row = 3;
    a[5].col = 0;
    a[5].value = 0;



    b[0].row = 3;
    b[0].col = 3;
    b[0].value = 4;

    b[1].row = 0;
    b[1].col = 0;
    b[1].value = 5;

    b[2].row = 0;
    b[2].col = 2;
    b[2].value = 2;

    b[3].row = 1;
    b[3].col = 1;
    b[3].value = 11;

    b[4].row = 2;
    b[4].col = 1;
    b[4].value = 3;
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

    //非零矩陣
    if (n <= 0)
        return;

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

/**
 * 矩陣轉置(快速版)
 * @param a
 * @param b
 */
void fastTranspose(Term a[], Term b[]) {
    int maxCol = 5;
    int rowTerms[maxCol];
    int b_StartingPos[maxCol];

    int i, bIdx;
    int numCols = a[0].col;
    int numTerms = a[0].value;

    b[0].row = numCols;
    b[0].col = a[0].row;
    b[0].value = numTerms;


    if (numTerms <= 0)
        return;

    //init rowTerms
    for (i = 0; i < numCols; i++) {
        rowTerms[i] = 0;
    }

    //計算a每個 col出現次數，存入 rowTerms
    //稍候拿來給b_StartingPos 計算每col 配發幾個位置
    for (i = 1; i <= numTerms; i++) {
        rowTerms[a[i].col]++;
    }

    //保存a[i].col的值位於b的idx 位置
    b_StartingPos[0] = 1;
    for (i = 1; i < numCols; i++) {
        b_StartingPos[i] = b_StartingPos[i - 1] + rowTerms[i - 1];
    }

    //先取得a[i].col位於b_StartingPos的 b的index 位置
    //將對應值塞入
    for (i = 1; i <= numTerms; i++) {
        bIdx = b_StartingPos[a[i].col]++;

        b[bIdx].row = a[i].col;
        b[bIdx].col = a[i].row;
        b[bIdx].value = a[i].value;
    }
}

void storeSum(Term d[], int *totalD, int row, int column, int *sum) {
    if (*sum) {
        if (*totalD < MAX_TERMS) {
            d[++*totalD].row = row;
            d[*totalD].col = column;
            d[*totalD].value = *sum;
            *sum = 0;

            return;
        }
    }
    else{
        fprintf(stderr, "Numbers of terms in product exceeds %d\n", MAX_TERMS);
//        exit(EXIT_FAILURE);

        return;
    }
    exit(EXIT_FAILURE);
}

void mmult(Term a[], Term b[], Term d[]) {
    int i, j, column, totalB = b[0].value;
    int totalD = 0;
    int rowsA = a[0].row, colsA = a[0].col;
    int totalA = a[0].value, colsB = b[0].col;
    int rowBegin = 1, row = a[1].row, sum = 0;
    Term newB[MAX_TERMS];

    if (colsA != b[0].row) {
        fprintf(stderr, "Incompatible matrices\n");
        exit(EXIT_FAILURE);
    }

    fastTranspose(b, newB);
    newB[MAX_TERMS-1].row = 3;
    newB[MAX_TERMS-1].col = 0;
    newB[MAX_TERMS-1].value = 0;

    showArry(newB);

    a[totalA + 1].row = rowsA;
    newB[totalB + 1].row = colsB;
    newB[totalB + 1].col = 0;

    for (i = 1; i <= totalA;) {
        column = newB[1].row;

        for (j = 1; j <= totalB + 1;) {
            if (a[i].row != row) {
                storeSum(d, &totalD, row, column, &sum);
                i = rowBegin;
                for (; newB[j].row == column; j++);
                column = newB[j].row;
            } else if (newB[j].row != column) {
                storeSum(d, &totalD, row, column, &sum);
                i = rowBegin;
                column = newB[j].row;
            } else
                switch (COMPARE(a[i].col, newB[j].col)) {
                    case -1:
                        i++;
                        break;
                    case 0:
                        sum += (a[i++].value * newB[j++].value);
                        break;
                    case 1:
                        j++;
                }
        }

        //~~~~
        for (; a[i].row == row; i++);
        rowBegin = i,row=a[i].row;
    }

    d[0].row = rowsA;
    d[0].col = colsB;
    d[0].value = totalD;
}

int main() {

//    initA();
    initAA();
    showArry(a);

//    transpose(a, b);
//    fastTranspose(a, b);
    mmult(a,b,d);

    showArry(d);

    return 0;
}