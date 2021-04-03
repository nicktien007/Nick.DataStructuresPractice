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

int main() {
    slink stack = createStack(5);
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int i = 0;
    while (!full(stack))
        push(stack, data[i++]);
    while (!empty(stack))
        printf("%d\n", pop(stack));
    while (i < 9 && !full(stack))
        push(stack, data[i++]);
    while (!empty(stack))
        printf("%d\n", pop(stack));
}

