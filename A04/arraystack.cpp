#include <iostream>
#include "arraystack.h"

using namespace std;

void initStack(ArrayStack &stack) {
    stack.count = -1;
}

void push(ArrayStack &stack, int value) {
        // Check if stack is full
        if (!isFull(stack)) {
            // Make sure current index is being set
            if (isEmpty(stack)) {
                stack.count++;
            }
            stack.value[stack.count] = value;
            stack.count++;
        }
        else {
            cout << "Error: Stack is full!" << endl;
        }
        
    }

int pop(ArrayStack &stack) {
    // Check if array is empty
    if (!isEmpty(stack)) {
        // Get first value
        int value = stack.value[stack.count - 1];

        stack.value[stack.count - 1] = 0;

        stack.count--;
        return value;

    }
    else {
        cout << "Error: Stack is empty!" << endl;
        return -1;
    }
}

int peek(ArrayStack stack) {
    if (!isEmpty(stack)) {
        return stack.value[stack.count - 1];
    }
    else {
        cout << "Error: Stack is empty!" << endl;
        return -1;
    }
}

bool isEmpty(const ArrayStack &stack) {
    return stack.count == -1;
}

bool isFull(const ArrayStack &stack) {
    return stack.count == MAX_SIZE;
}

void printValues(const ArrayStack &stack) {
    for (int i = 0; i < MAX_SIZE; ++i) {
        cout << "Value at index " << i << ": " << stack.value[i] << endl;
    }
}