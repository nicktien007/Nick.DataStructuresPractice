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

int calcPostfix();

void convertInfixToPostfix();

//char *expr = {"62/3-42*+"};

//後序
char *expr = "a*b+5";
//char *expr = "(1+2)*7";
//char *expr = "a*b/c";
//char *expr = "(a/(b-c+d))*(e-a)*c";
//char *expr = "a/b-c+d*e-a*c";

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
        } else {
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

//堆疊內優先權
int isp[]{0, 19, 12, 12, 13, 13, 13, 0};

//進堆疊優先權
int icp[]{20, 19, 12, 12, 13, 13, 13, 0};

void printToken(Precedence token) {
    if (token == Plus) {
        printf("+");
    }
    if (token == Minus) {
        printf("-");
    }
    if (token == Times) {
        printf("*");
    }
    if (token == Divide) {
        printf("/");
    }
    if (token == Lparen) {
        printf(")");
    }
    if (token ==Lparen) {
        printf("(");
    }
}

/**
 * 中置轉後置
 */
void convertInfixToPostfix() {
    char symbol;
    Precedence token;
    int n = 0;
    int top = 0;

    Precedence stack[20];
    stack[0] = Eos;

    for (token = getToken(&symbol, &n); token != Eos; token = getToken(&symbol, &n)) {
        if (token == Operand) {                 //token 是運算元，直接打印出來
            printf("%c", symbol);
        } else if (token == Rparen) {           //右括號
            while (stack[top] != Lparen) {      //把 stack輸出，直到遇到左括號
                printToken(stack[top--]);
            }
            top--;  //pop stack => 移除 左括號
        } else {                                 // token 是+、-、*、/、mod、(
            while (isp[stack[top]] >= icp[token]) { //如果stack 內的運算子優先度
                printToken(stack[top--]);           //大於等於token運算子優先度，則打印它
            }

            //push stack
            stack[++top] = token;
        }
    }
    while ((token = stack[top--]) != Eos) {
        printToken(token);
    }
    printf("\n");
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

//    printf("%d", calcPostfix());

    convertInfixToPostfix();

}

