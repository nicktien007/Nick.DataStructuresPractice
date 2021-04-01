#include <iostream>

using namespace std;

const int MAX_TERMS = 100;

typedef struct {
    /**
     * 常數
     */
    float coef;
    /**
     * 指數
     */
    int expon;
} polynomial;

polynomial terms[MAX_TERMS];
int avail = 0;

void testPadd();
void testString();

void attach(float coefficient, int exponent);

void padd(int starta, int finisha,
          int startb, int finishb,
          int startd);

void show(int startd);

#define COMPARE(x, y) ((x < y) ? -1: (x == y)? 0: 1)

void testPadd() {
    terms[0].coef = 2;
    terms[0].expon = 1000;

    terms[1].coef = 1;
    terms[1].expon = 0;

    terms[2].coef = 1;
    terms[2].expon = 4;

    terms[3].coef = 10;
    terms[3].expon = 3;

    terms[4].coef = 3;
    terms[4].expon = 2;

    terms[5].coef = 1;
    terms[5].expon = 0;

    padd(0, 1, 2, 5, 6);
    show(6);
}

/**
 * Polynomial Addition (多項式相加)
 * @param starta
 * @param finisha
 * @param startb
 * @param finishb
 * @param startd
 */
void padd(int starta, int finisha,
          int startb, int finishb,
          int startd) {
    /* add A(x) and B(x) to obtain D(x) */
    float coefficient;
    avail = startd;

    while (starta <= finisha && startb <= finishb) {

        //如果多項式A已經結束時，將多項式B剩下的項目放進D(X)
        if (starta > finisha) {
            for (; startb <= finishb; startb++)
                attach(terms[startb].coef, terms[startb].expon);
            break;
        }

        //如果多項式B已經結束時，將多項式A剩下的項目放進D(X)
        if (startb > finishb) {
            for (; starta <= finisha; starta++)
                attach(terms[starta].coef, terms[starta].expon);
            break;
        }

        switch (COMPARE(terms[starta].expon, terms[startb].expon)) {
            case -1: /* a expon < b expon */
                attach(terms[startb].coef, terms[startb].expon);
                startb++;
                break;
            case 0: /* equal exponents */
                coefficient = terms[starta].coef +
                              terms[startb].coef;
                if (coefficient)
                    attach(coefficient, terms[starta].expon);
                starta++;
                startb++;
                break;
            case 1: /* a expon > b expon */
                attach(terms[starta].coef, terms[starta].expon);
                starta++;
        }
    }
}

void attach(float coefficient, int exponent) {
    /* add a new term to the polynomial */
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "Too many terms in the polynomial\n");
        exit(1);
    }
    terms[avail].coef = coefficient;
    terms[avail].expon = exponent;

    avail++;
}

void show(int startd) {
    for (int i = startd; i < avail; ++i) {
        if (terms[i].expon == 0) {
            printf("%.f", terms[i].coef);
            break;
        }
        printf("%.fx^%d+", terms[i].coef, terms[i].expon);
    }
}

int main() {

    testPadd();

    return 0;
}

