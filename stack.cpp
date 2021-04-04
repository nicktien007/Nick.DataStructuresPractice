#include <iostream>

using namespace std;

struct Stack {
    int capability;
    int sp;
    int *data;
};
typedef struct Stack *slink;

slink createStack(int capability) {
    slink stack = static_cast<slink>(malloc(sizeof(struct Stack)));
    if (!stack)
        return stack;
    stack->capability = capability;
    stack->sp = -1;
    stack->data = static_cast<int *>(malloc(sizeof(int) * capability));
    return stack;
}

int empty(slink stack) {
    return stack->sp == -1;
}

int full(slink stack) {
    return stack->sp == stack->capability - 1;
}

void push(slink stack, int item) {
    stack->data[++stack->sp] = item;
}

int pop(slink stack) {
    if (empty(stack))
        return -1;
    return stack->data[stack->sp--];
}


char *expr= {"62/3-42*+"};

typedef enum Precedence {
    Lparen,
    Rparen,
    Plus,
    Minus,
    Times,
    Divide,
    Mod,
    Eos,
    Operand
};

Precedence getToken(char *symbol, int *n) {

    *symbol = expr[(*n)++];

    switch (*symbol) {
        case '(':
            return Lparen;
        case ')':
            return Rparen;
        case '+':
            return Plus;
        case '-':
            return Minus;
        case '/':
            return Divide;
        case '*':
            return Times;
        case '%':
            return Mod;
        case '\0':
            return Eos;
        default:
            return Operand;

    }
}


/**
 * 計算後置運算式 expr
 * @return
 */
int calcPostfix() {
    Precedence token;
    char symbol;
    int op1, op2;
    int n = 0;
    token = getToken(&symbol, &n);
    slink stack = createStack(5);

    while (token != Eos) {
        if (token == Operand) {
            push(stack, symbol - '0');
        }
        else{
            op2 = pop(stack);
            op1 = pop(stack);

            switch (token) {
                case Plus:
                    push(stack, op1 + op2);
                    break;
                case Minus:
                    push(stack, op1 - op2);
                    break;
                case Times:
                    push(stack, op1 * op2);
                    break;
                case Divide:
                    push(stack, op1 / op2);
                    break;
                case Mod:
                    push(stack, op1 % op2);
            }
        }
        token = getToken(&symbol, &n);
    }

    return pop(stack);
}


int main() {
//    slink stack = createStack(5);
//    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
//    int i = 0;
//    while (!full(stack))
//        push(stack, data[i++]);
//    while (!empty(stack))
//        printf("%d\n", pop(stack));
//    while (i < 9 && !full(stack))
//        push(stack, data[i++]);
//    while (!empty(stack))
//        printf("%d\n", pop(stack));

    printf("%d", calcPostfix());
}

