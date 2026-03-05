#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

static const int MAX_SIZE = 10;

struct ArrayStack {
    int value[MAX_SIZE];
    int count;
};

// Function Prototypes
void initStack(ArrayStack &stack);
void push(ArrayStack &stack, int value);
int pop(ArrayStack &stack);
int peek(ArrayStack stack);
bool isEmpty(const ArrayStack &stack);
bool isFull(const ArrayStack &stack);
void printValues(const ArrayStack &stack);

#endif